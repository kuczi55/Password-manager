#include "addform.h"
#include "ui_addform.h"
#include "datamanager.h"
#include <QMessageBox>
#include <iostream>
#include "mainwindow.h"
#include "encryption.h"
#include <QListWidget>

<<<<<<< Updated upstream
=======
void AddForm::fill_data(){
    QString data = line[0]->data(Qt::UserRole).toString();
    QStringList splitted = data.split(semiclon);
    if(splitted.size() < 4) {
        QMessageBox::critical(this, "Edit data", "Critical error");
        exit(EXIT_FAILURE);
    }
    ui->lineEdit_title->setText(splitted[0]);
    ui->lineEdit_username->setText(splitted[1]);
    ui->lineEdit_password->setText(splitted[2]);
    ui->lineEdit_repeat->setText(splitted[2]);
    ui->lineEdit_url->setText(splitted[3]);
}

>>>>>>> Stashed changes
AddForm::AddForm(QWidget *parent, QString password, QString user,
                 QTableWidget* table, bool edit, QList<QTableWidgetItem*> line) :
    QDialog(parent),
    ui(new Ui::AddForm),
    password(password),
    user(user),
    table(table),
    edit(edit),
    line(line)
{
    ui->setupUi(this);
<<<<<<< Updated upstream
    if(edit && line != NULL) {
        QString data = line->data(Qt::UserRole).toString();
        QStringList splitted = data.split(semiclon);
        if(splitted.size() < 4) {
            QMessageBox::critical(this, "Edit data", "Critical error");
            exit(EXIT_FAILURE);
        }
        ui->lineEdit_title->setText(splitted[0]);
        ui->lineEdit_username->setText(splitted[1]);
        ui->lineEdit_password->setText(splitted[2]);
        ui->lineEdit_repeat->setText(splitted[2]);
        ui->lineEdit_url->setText(splitted[3]);
=======

    if(edit && line.size() != 0) {
        fill_data();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    else {
        QString info = title + semiclon + username + semiclon + pass + semiclon + url;
        if(list != NULL) {
            QList<QListWidgetItem *> exist = list->findItems(title, Qt::MatchExactly);
            if(!edit && exist.length() == 0) {
                if(add_to_file(file_name, encrypt(info, password))) {
                    QListWidgetItem* item = new QListWidgetItem();
                    item->setText(title);
                    item->setData(Qt::UserRole, info);
                    list->addItem(item);
=======
    return true;
}

QTableWidgetItem *AddForm::check_exist(QString check) {
    int rows = table->rowCount();
    for(int i = 0; i < rows; i++)
    {
        QTableWidgetItem *item = table->item(i, 0);
        if( item->text()== check)
        {
            return item;
        }
    }
    return NULL;
}

void AddForm::on_pushButton_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString username = ui->lineEdit_username->text();
    QString pass = ui->lineEdit_password->text();
    QString repeat = ui->lineEdit_repeat->text();
    QString url = ui->lineEdit_url->text();
    QString file_name = data_dir + user + extension;

    if(check_conditions(title, username, file_name, pass, repeat, url)) {
        QString info = title + semiclon + username + semiclon + pass + semiclon + url;
        if(table != NULL) {
            QTableWidgetItem* exist = check_exist(title);
            if(!edit && exist == NULL) {
                if(add_to_file(file_name, crypt::encrypt(info, password))) {
                    QTableWidgetItem * data_item = new QTableWidgetItem();
                    data_item->setText(title);
                    data_item->setData(Qt::UserRole, info);
                    table->insertRow(table->rowCount());
                    table->setItem(table->rowCount()-1, 0, data_item);
                    table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(username));
                    table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(url));
>>>>>>> Stashed changes
                    QMessageBox::information(this, "Add", "Successfully added new data");
                    close();
                }
                else {
                    QMessageBox::warning(this, "Add", "Cannot open file");
                }
            }
            else if(edit && (exist == NULL || exist->text() == line[0]->text())){
                QString original = line[0]->data(Qt::UserRole).toString();
                if(!edit_file(user, password, original, info)) {
                    QMessageBox::critical(this, "Add", "Critical error");
                    exit(EXIT_FAILURE);
                }
<<<<<<< Updated upstream
                line->setText(title);
                line->setData(Qt::UserRole, info);
=======
                line[0]->setText(title);
                line[0]->setData(Qt::UserRole, info);
                line[1]->setText(username);
                line[2]->setText(url);
>>>>>>> Stashed changes
                QMessageBox::information(this, "Add", "Successfully edited data");
                close();
            }
            else {
                QMessageBox::warning(this, "Add", "Data with such title already exist!");
            }
        }
        else {
            QMessageBox::critical(this, "Add", "Critical error");
            exit(EXIT_FAILURE);
        }
    }
}

void AddForm::on_pushButton_cancel_clicked()
{
    close();
}
