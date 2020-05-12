#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QTextStream>
#include <QApplication>
#include "encryption.h"
#include <QListWidget>
#include <QMessageBox>
#include <QFileInfo>
#include <QTableWidget>

QString return_line(QString datas, QString name);
bool check_if_exist(QString datas, QString name);
bool add_to_file(QString file, QString line);
void load_from_file(QString user, QString pass, QTableWidget *table);
bool edit_file(QString user, QString pass, QString original,
               QString replace, bool remove = false);

#endif // DATAMANAGER_H
