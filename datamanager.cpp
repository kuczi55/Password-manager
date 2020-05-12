#include "datamanager.h"
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFileInfo>
#include "encryption.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>

QString return_line(QString datas, QString name) {
    name.append(semiclon);
    QFile data(datas);
    if(data.open(QIODevice::ReadWrite)) {
        QTextStream in (&data);
        QString line;
        do {
            line = in.readLine();
            if(line.contains(name, Qt::CaseSensitive)) {
                data.close();
                return line;
            }
        } while(!line.isNull());
    }
    data.close();
    return NULL;
}

bool check_if_exist(QString datas, QString name) {
    if(return_line(datas, name) != NULL) return true;
    return false;
}

bool add_to_file(QString file, QString line) {
    QFile data(file);
    if(data.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&data);
        stream << line << endl;
        stream.flush();
        data.flush();
        data.close();
        return true;
    }
    else {
        return false;
    }
}

void load_from_file(QString user, QString pass, QTableWidget *table) {
    QFile user_data(data_dir + user + extension);
    QStringList encrypted_data;
    if (user_data.open(QFile::ReadOnly))
    {
        QTextStream in (&user_data);
        QString data = in.readAll();
        encrypted_data = data.split("\n");
        user_data.close();
        for(int i = 0; i < encrypted_data.size()-1; i++) {
            QString decrypted = crypt::decrypt(encrypted_data[i], pass);
            QStringList splitted = decrypted.split(semiclon);
            if(splitted.size() < 4) {
                QMessageBox::critical(table, "Parse data", "Critical error");
                exit(EXIT_FAILURE);
            }
            table->insertRow(table->rowCount());
            QTableWidgetItem* data_item = new QTableWidgetItem();
            data_item->setText(splitted[0]);
            data_item->setData(Qt::UserRole, decrypted);
            table->setItem(table->rowCount()-1, 0, data_item);
            table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(splitted[1]));
            table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(splitted[3]));
        }
    }
}

bool edit_file(QString user, QString pass, QString original,
               QString replace, bool remove) {
    QFile original_file(data_dir + user + extension);
    QFile temp_file(data_dir + user + extension + ".temp");
    original_file.open(QIODevice::ReadOnly | QIODevice::Text);
    temp_file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(original_file.isOpen() && temp_file.isOpen()) {
        QTextStream org(&original_file);
        QTextStream tmp(&temp_file);
        while(!org.atEnd()) {
            QString actual_line = org.readLine();
            if(crypt::decrypt(actual_line, pass) == original) {
                if(!remove) {
                    tmp << crypt::encrypt(replace, pass) << endl;
                }
            }
            else {
                tmp << actual_line << endl;
            }
        }
        original_file.close();
        temp_file.close();
        original_file.remove();
        temp_file.rename(data_dir + user + extension);
        return true;
    }
    return false;
}
