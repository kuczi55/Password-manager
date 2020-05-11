#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <string>
#include <QApplication>

using namespace std;

QString genSalt();
template <size_t multiple> size_t round_up(const size_t len);
QString buffer_as_hex(const unsigned char *buf, size_t size);
//QString AESEncrypt(const void *const apBuffer, size_t aBufferSize, QString key);
//QString AESDecrypt(const void *const apBuffer, size_t aBufferSize, QString key);
QString sha256(const QString str);
QString md5(const QString pass);
QString Encrypt(QString decrypted, QString pass);
QString Decrypt(QString encrypted, QString pass);

#endif // ENCRYPTION_H
