#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QDialog>
#include "addform.h"
#include "datamanager.h"

namespace Ui {
class Overview;
}

class Overview : public QDialog
{
    Q_OBJECT

public:
    explicit Overview(QWidget *parent = nullptr, QString password = "", QString user = "");
    ~Overview();

private slots:

    void on_pushButton_logout_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_show_edit_clicked();

    void on_pushButton_delete_clicked();
<<<<<<< Updated upstream

    void on_pushButton_clicked();
=======
    void on_pushButton_clicked();
    void on_pushButton_copy_clicked();
>>>>>>> Stashed changes

private:
    Ui::Overview *ui;
    AddForm *addForm;
    QString password;
    QString user;
};

#endif // OVERVIEW_H
