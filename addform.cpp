#include "addform.h"
#include "ui_addform.h"
#include "datamanager.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "encryption.h"
#include <QListWidget>

AddForm::AddForm(QWidget *parent, QString password, QString user,
                 QListWidget* list, bool edit, QListWidgetItem* line) :
    QDialog(parent),
    ui(new Ui::AddForm),
    password(password),
    user(user),
    list(list),
    edit(edit),
    line(line)
{
    ui->setupUi(this);
    if(edit && line != NULL) {
        QString data = line->data(Qt::UserRole).toString();
        QStringList splitted = data.split(semiclon);
        if(splitted.size() < 4) {
            QMessageBox::warning(this, "Edit data", "Critical error");
            exit(EXIT_FAILURE);
        }
        ui->lineEdit_title->setText(splitted[0]);
        ui->lineEdit_username->setText(splitted[1]);
        ui->lineEdit_password->setText(splitted[2]);
        ui->lineEdit_repeat->setText(splitted[2]);
        ui->lineEdit_url->setText(splitted[3]);
    }
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::on_checkBox_stateChanged(int arg1)
{
    ui->lineEdit_password->setEchoMode(arg1 == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEdit_repeat->setEchoMode(arg1 == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password);
}

void AddForm::on_pushButton_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString username = ui->lineEdit_username->text();
    QString pass = ui->lineEdit_password->text();
    QString repeat = ui->lineEdit_repeat->text();
    QString url = ui->lineEdit_url->text();
    QString file_name = user+".mps";
    if(check_if_exist(file_name, title)) {
        QMessageBox::warning(this, "Add", "Title already exists");
    }
    else if(pass != repeat) {
        QMessageBox::warning(this, "Add", "Passwords don't match");
    }
    else if(username.contains(semiclon) || pass.contains(semiclon) || title.contains(semiclon)) {
        QMessageBox::warning(this, "Add", QString("Username, password or title cannot contain ").append(semiclon));
    }
    else if(username.isEmpty() || pass.isEmpty() || repeat.isEmpty() || title.isEmpty() || url.isEmpty()) {
        QMessageBox::warning(this, "Add", "Please fill all fileds");
    }
    else {
        QString info = title + semiclon + username + semiclon + pass + semiclon + url;
        if(list != NULL) {
            QList<QListWidgetItem *> exist = list->findItems(title, Qt::MatchExactly);
            if(!edit && exist.length() == 0) {
                if(add_to_file(file_name, Encrypt(info, password))) {
                    QListWidgetItem* item = new QListWidgetItem();
                    item->setText(title);
                    item->setData(Qt::UserRole, info);
                    list->addItem(item);
                    QMessageBox::information(this, "Add", "Successfully added new data");
                    close();
                }
                else {
                    QMessageBox::warning(this, "Add", "Cannot open file");
                }
            }
            else if(edit && (exist.length() == 0 || exist[0]->text() == line->text())){
                QString original = line->data(Qt::UserRole).toString();
                if(!edit_file(user, password, original, info)) {
                    QMessageBox::warning(this, "Add", "Critical error");
                    exit(EXIT_FAILURE);
                }
                line->setText(title);
                line->setData(Qt::UserRole, info);
                QMessageBox::information(this, "Add", "Successfully edited data");
                close();
            }
            else {
                QMessageBox::warning(this, "Add", "Data with such title already exist!");
            }
        }
        else {
            QMessageBox::warning(this, "Add", "Critical error");
            exit(EXIT_FAILURE);
        }
    }
}

void AddForm::on_pushButton_cancel_clicked()
{
    close();
}
