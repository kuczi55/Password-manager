#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QApplication>
#include <QListWidget>


QString return_line(QString datas, QString name);
bool check_if_exist(QString datas, QString name);
bool add_to_file(QString file, QString line);
void load_from_file(QListWidget* list, QString user, QString pass);
bool edit_file(QString user, QString pass, QString original,
               QString replace, bool remove = false);

#endif // DATAMANAGER_H
