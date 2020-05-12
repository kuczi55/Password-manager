#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "encryption.h"
#include "datamanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear_all_fields() {
    ui->lineEdit_password_login->clear();
    ui->lineEdit_username_login->clear();
    ui->lineEdit_username_register->clear();
    ui->lineEdit_password_register->clear();
    ui->lineEdit_repeat_password->clear();
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username_login->text();
    QString password = ui->lineEdit_password_login->text();
    QString user_data = return_line(data_dir + userdata, username);
    if(username == "" || password == "" || user_data == NULL) {
        QMessageBox::warning(this, "Login", "Invalid username or password");
    }
    else {
        QStringList pieces = user_data.split(semiclon);
        if(pieces.size() < 3) {
            QMessageBox::critical(this, "Login", "Critical error");
            exit(EXIT_FAILURE);
        }
        QString correct_pass = pieces.value(1);
        QString salt = pieces.value(2);
        QString hashed_password = crypt::sha256(salt+password);
        if(hashed_password != correct_pass) {
            QMessageBox::warning(this, "Login", "Invalid username or password");
        }
        else {
            close();
            view = new Overview(nullptr, crypt::md5(password), username);
            view->show();
        }
    }
    clear_all_fields();
}

bool MainWindow::check_conditions(QString username, QString password, QString repeated_password) {
    if(username.isEmpty() || password.isEmpty() || repeated_password.isEmpty()) {
        QMessageBox::warning(this, "Registration", "Please fill all fileds");
        return false;
    }
    else if(password != repeated_password) {
        QMessageBox::warning(this, "Registration", "Passwords don't match");
        return false;
    }
    else if(password.length() < 8) {
        QMessageBox::warning(this, "Registration", "Password must contain at least 8 characters");
        return false;
    }
    else if(username.contains(semiclon) || password.contains(semiclon)) {
        QMessageBox::warning(this, "Registration", QString("Username or password cannot contain ").append(semiclon));
        return false;
    }
    else if(check_if_exist(data_dir + userdata, username) || userdata == username + extension) {
        QMessageBox::warning(this, "Registration", "User with such username already exists");
        return false;
    }
    return true;
}

void MainWindow::on_pushButton_signUp_clicked()
{
    QString username = ui->lineEdit_username_register->text();
    QString password = ui->lineEdit_password_register->text();
    QString repeated_password = ui->lineEdit_repeat_password->text();

    if(check_conditions(username, password, repeated_password)) {
        QFile data(data_dir + userdata);
        if(data.open(QIODevice::ReadWrite | QIODevice::Append)) {
            QTextStream stream(&data);
            QString salt = crypt::gen_salt();
            stream << username << semiclon << crypt::sha256(salt+password) << semiclon << salt << endl;
            stream.flush();
            data.flush();
            data.close();
            QMessageBox::information(this, "Registration", "Successfully created new user");
            clear_all_fields();
        }
        else {
            QMessageBox::warning(this, "Registration", "Cannot open file");
        }
    }
}
