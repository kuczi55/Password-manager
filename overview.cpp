#include "overview.h"
#include "ui_overview.h"
#include <QMessageBox>

Overview::Overview(QWidget *parent, QString password, QString user) :
    QDialog(parent),
    ui(new Ui::Overview),
    password(password),
    user(user)
{
    ui->setupUi(this);
    load_from_file(ui->listWidget, user, password);
}

Overview::~Overview()
{
    delete ui;
}


void Overview::on_pushButton_logout_clicked()
{
    close();
    parentWidget()->show();
}

void Overview::on_pushButton_add_clicked()
{
    addForm = new AddForm(this, password, user, ui->listWidget);
    addForm->exec();
}

void Overview::on_pushButton_show_edit_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.length() == 1) {
        addForm = new AddForm(this, password, user, ui->listWidget, true, items[0]);
        addForm->exec();
    }
    else {
         QMessageBox::warning(this, "Show/Edit", "Please select item");
    }
}

void Overview::on_pushButton_delete_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.length() == 1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete", "Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes) {
            if(!edit_file(user, password, items[0]->data(Qt::UserRole).toString(), "", true)) {
                QMessageBox::warning(this, "Delete", "Critical error");
                exit(EXIT_FAILURE);
            }
            qDeleteAll(ui->listWidget->selectedItems());
            QMessageBox::information(this, "Delete", "Successfully removed data");
        }
    }
    else {
         QMessageBox::warning(this, "Delete", "Please select item");
    }
}
