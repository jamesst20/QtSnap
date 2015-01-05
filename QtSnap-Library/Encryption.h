#ifndef ENCRYPTION_H
#define ENCRYPTION_H


#include <QUuid>
#include <QDebug>
#include <QByteArray>

#include "Crypto/aes.h"

class Encryption
{
public:
    static QByteArray encryptSnapOrStory(QByteArray input);
    static QByteArray decryptSnap(QByteArray input);
    static QByteArray decryptStory(QByteArray input, QString keyStr, QString ivStr);

    static QString randomMediaID(QString username);

private:
    static QByteArray& PKCS7Padding(QByteArray &bytes);
    static QByteArray& RemovePKCS7Padding(QByteArray &bytes);

    static const QString AES_KEY;
};

#endif // ENCRYPTION_H
