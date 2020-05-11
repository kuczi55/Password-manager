#include "addform.h"
#include "ui_addform.h"
#include "datamanager.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "encryption.h"
#include <QListWidget>

void AddForm::fill_data(){
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
}

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
        fill_data();
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

bool AddForm::check_conditions(QString title, QString username, QString file_name,
                      QString pass, QString repeat, QString url) {
    if(check_if_exist(file_name, title)) {
        QMessageBox::warning(this, "Add", "Title already exists");
        return false;
    }
    else if(pass != repeat) {
        QMessageBox::warning(this, "Add", "Passwords don't match");
        return false;
    }
    else if(username.contains(semiclon) || pass.contains(semiclon) || title.contains(semiclon)) {
        QMessageBox::warning(this, "Add", QString("Username, password or title cannot contain ").append(semiclon));
        return false;
    }
    else if(username.isEmpty() || pass.isEmpty() || repeat.isEmpty() || title.isEmpty() || url.isEmpty()) {
        QMessageBox::warning(this, "Add", "Please fill all fileds");
        return false;
    }
    return true;
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
        if(list != NULL) {
            QList<QListWidgetItem *> exist = list->findItems("Title: " + title + " Username: " + username + " Url: " + url, Qt::MatchExactly);
            if(!edit && exist.length() == 0) {
                if(add_to_file(file_name, crypt::encrypt(info, password))) {
                    QListWidgetItem* item = new QListWidgetItem();
                    item->setText("Title: " + title + " Username: " + username + " Url: " + url);
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
                    QMessageBox::critical(this, "Add", "Critical error");
                    exit(EXIT_FAILURE);
                }
                line->setText("Title: " + title + " Username: " + username + " Url: " + url);
                line->setData(Qt::UserRole, info);
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
