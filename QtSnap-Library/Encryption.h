#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QByteArray>
#include <QDebug>

#include <QtCrypto/QtCrypto>

class Encryption
{
public:
    static QByteArray encryptSnapOrStory(QByteArray data);
    static QByteArray decryptSnap(QByteArray data);
    static QByteArray decryptStory(QByteArray data, QString keyStr, QString ivStr);

private:
    static QByteArray& PKCS7Padding(QByteArray &bytes);
    static QByteArray& RemovePKCS7Padding(QByteArray &bytes);

    static const QString AES_KEY;
};

#endif // ENCRYPTION_H
