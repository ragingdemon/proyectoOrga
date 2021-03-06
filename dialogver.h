#ifndef DIALOGVER_H
#define DIALOGVER_H

#include <QDialog>
#include <QMap>
#include "header.h"
#include "indicel.h"
namespace Ui {
class DialogVer;
}

class DialogVer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVer(QString path, QWidget *parent = 0);
    Header *header;    

    ~DialogVer();

private slots:
    void on_pushButton_clicked();

    void on_le_agregar_clicked();

    void on_pb_buscar_clicked();

private:
    QString path;
    Ui::DialogVer *ui;
    void llenarTabla();    
};

#endif // DIALOGVER_H
