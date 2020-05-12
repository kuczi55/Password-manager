#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <QApplication>

using namespace std;

namespace crypt {
    QString gen_salt();
    QString buffer_as_hex(const unsigned char *buf, size_t size);
    QString sha256(const QString str);
    QString md5(const QString pass);
    QString encrypt(QString decrypted, QString pass);
    QString decrypt(QString encrypted, QString pass);
}

#endif // ENCRYPTION_H
