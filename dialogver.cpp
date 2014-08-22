#include "dialogver.h"
#include "ui_dialogver.h"
#include "campo.h"
#include "dialogagregar.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include <vector>
using std::vector;

DialogVer::DialogVer(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVer)
{
    ui->setupUi(this);
    this->path = path;
    header = new Header(path);
    llenarTabla(path);
}

DialogVer::~DialogVer()
{
    if(header)
        delete header;
    delete ui;
}

void DialogVer::llenarTabla(QString path)
{
    QTableWidget* table = ui->tableWidget;
    while(table->rowCount() > 0)
        table->removeRow(0);
    vector<Campo*> campos = header->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre().c_str());
        encabezados.append(str);
    }
    table->setColumnCount(campos.size());
    table->setHorizontalHeaderLabels(encabezados);
    //leer registros del archivo y agregarlos a la tabla
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&archivo);
    in.seek(header->getDatos_offset());
    int longitud_registro = header->getLongitud_registro();
    int fila = 0;
    int rrn = 0;
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
            rrn_tabla.append(rrn);
            table->insertRow(fila);
            for (unsigned int i = 0; i < campos.size(); ++i) {
                int incremento = campos.at(i)->getLongitud();
                QString substring = registro.mid(offset,incremento);
                table->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
                offset += incremento;
            }
            fila++;
        }else{
            offset += longitud_registro;
        }
        rrn++;
    }
    if (archivo.isOpen()) {
        archivo.close();
    }
}

bool DialogVer::borrarRegistro(int fila)
{
    int longitud_registro = header->getLongitud_registro();
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream out(&archivo);
    //leer cabeza del availlist
    out.seek(header->getList_offset());
    int availlist = out.readLine().toInt();
    int rrn = rrn_tabla.at(fila);
    qDebug()<<"cabeza de availlist: "<<availlist;
    qDebug()<<"registro a eliminar: "<<rrn;
    //reescribir cabeza del availlist
    out.seek(header->getList_offset());
    QString str = QString::number(rrn);
    if (str.size() < 4) {
        while (str.size() < 4) {
            str.append(' ');
        }
    }
    out<<str;
    //marcar registro como borrado
    out.seek(header->getDatos_offset() + rrn * longitud_registro);
    str = "*" + QString::number(availlist);
    if (str.size() < 5) {
        while (str.size() < 5) {
            str.append(' ');
        }
    }
    qDebug()<<"offset del registro a eliminar: "<<out.pos();
    out<<str;
    rrn_tabla.removeAt(fila);
    archivo.close();
    llenarTabla(path);
    return true;
}

void DialogVer::on_pushButton_clicked()
{
    QTableWidget* table = ui->tableWidget;
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();
    int fila;
    foreach (QModelIndex index, indexList) {
        fila = index.row();
        qDebug()<<"row: "<<fila;
        if (fila < rrn_tabla.size()) {
            borrarRegistro(fila);
        }
    }
}


void DialogVer::on_le_agregar_clicked()
{
    DialogAgregar dialog(path,this);
    dialog.exec();
}
