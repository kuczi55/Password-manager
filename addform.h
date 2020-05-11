#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class AddForm;
}

class AddForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr, QString password = "", QString user = "",
                     QListWidget* list = NULL, bool edit = false, QListWidgetItem* line = NULL);
    ~AddForm();

private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_cancel_clicked();
    bool check_conditions(QString title, QString username, QString file_name,
                          QString pass, QString repeat, QString url);
    void fill_data();

private:
    Ui::AddForm *ui;
    QString password;
    QString user;
    QListWidget* list;
    bool edit;
    QListWidgetItem* line;
};

#endif // ADDFORM_H
