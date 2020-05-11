#include "overview.h"
#include "ui_overview.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "datamanager.h"
#include "encryption.h"
#include <QClipboard>

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
    MainWindow *main_window = new MainWindow(this);
    main_window->show();
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
                QMessageBox::critical(this, "Delete", "Critical error");
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

void Overview::on_pushButton_clicked()
{
    QString pass = crypt::gen_salt();
    QMessageBox mb(QMessageBox::NoIcon, "Generate",
                   pass, QMessageBox::Ok, this);
    mb.setTextInteractionFlags(Qt::TextSelectableByMouse);
    QAbstractButton* pButtonCopy = mb.addButton(tr("Copy"), QMessageBox::YesRole);
    pButtonCopy->disconnect();
    connect(pButtonCopy, &QAbstractButton::clicked, this, [=]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(pass);
        QMessageBox::information(this, "Copy to clipboard", "Successfully copied password to clipboard");
    });
    mb.exec();
}

void Overview::on_pushButton_copy_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.length() == 1) {
        QString data = items[0]->data(Qt::UserRole).toString();
        QStringList splitted = data.split(semiclon);
        QString pass = splitted[2];
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(pass);
        QMessageBox::information(this, "Copy to clipboard", "Successfully copied password to clipboard");
    }
    else {
         QMessageBox::warning(this, "Delete", "Please select item");
    }
}
