#include "encryption.h"
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/md5.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <random>
#include "simplecrypt.h"

random_device my_random_device;
default_random_engine my_random_engine(my_random_device());

QString gen_salt() {

    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!$%^&():'><,|";

    uniform_int_distribution<int> random_number(0, sizeof(charset) - 2);

    QString salt;
    salt.reserve(SHA256_DIGEST_LENGTH);
    for( int i = 0; i < SHA256_DIGEST_LENGTH; i++ ) {
        salt.push_back(charset[random_number(my_random_engine)]);
    }
    return salt;
}

template <size_t multiple> size_t round_up(const size_t len) {
    if (len % multiple == 0) return len;
    else return ((len / multiple) + 1) * multiple;
}

QString buffer_as_hex(const unsigned char *buf, size_t size) {
    stringstream res;
    res << hex << setfill('0');
    for( size_t i = 0; i < size; ++i )
    {
        res << setw(2) << static_cast<unsigned int>(buf[i]);
    }
    return QString::fromStdString(res.str());
}

QString encrypt(QString decrypted, QString pass) {
    quint64 key{1};
    key = static_cast<quint64>(pass.toULongLong());
    SimpleCrypt crypto(key);
    return crypto.encryptToString(decrypted);
}

QString decrypt(QString encrypted, QString pass) {
    quint64 key{1};
    key = static_cast<quint64>(pass.toULongLong());
    SimpleCrypt crypto(key);
    return crypto.decryptToString(encrypted);
}

//QString AESEncrypt(const void *const apBuffer, size_t aBufferSize, QString key) {
//    unsigned char AES_IVector[] = "gVkYp3s6v9y$B&E)";
//    AES_KEY EncryptKey;
//    AES_set_encrypt_key(reinterpret_cast<const unsigned char *>(key.toLocal8Bit().data()), 256, &EncryptKey);
//    unsigned char AES_Encrypted[1024] = {0};
//    AES_cbc_encrypt(static_cast<const unsigned char *>(apBuffer), AES_Encrypted, aBufferSize,
//                    &EncryptKey, AES_IVector, AES_ENCRYPT);
//    const string encrypted(reinterpret_cast<const char *>(AES_Encrypted), round_up<AES_BLOCK_SIZE>(aBufferSize));
//    return QString::fromLocal8Bit((char*) AES_Encrypted);
//}

//QString AESDecrypt(const void *const apBuffer, size_t aBufferSize, QString key) {
//    unsigned char AES_IVector[] = "gVkYp3s6v9y$B&E)";
//    AES_KEY DecryptKey;
//    AES_set_decrypt_key(reinterpret_cast<const unsigned char *>(key.toLocal8Bit().data()), 256, &DecryptKey);
//    unsigned char AES_Decrypted[1024] = {0};
//    AES_cbc_encrypt(static_cast<const unsigned char *>(apBuffer), AES_Decrypted, aBufferSize,
//                    &DecryptKey, AES_IVector, AES_DECRYPT);
//    const string decrypted(reinterpret_cast<const char *>(AES_Decrypted));
//    return QString::fromLocal8Bit(decrypted.c_str());
//}

QString sha256(const QString pass) {
    const string str = pass.toLocal8Bit().constData();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    return buffer_as_hex(hash, SHA256_DIGEST_LENGTH);
}

QString md5(const QString pass) {
    const string str = pass.toLocal8Bit().constData();
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, str.c_str(), str.size());
    MD5_Final(hash, &md5);
    stringstream ss;
    return buffer_as_hex(hash, MD5_DIGEST_LENGTH);
}
