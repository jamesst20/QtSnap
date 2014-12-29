#include "Encryption.h"

const QString Encryption::AES_KEY = "M02cnQ51Ji97vwT4";

QByteArray Encryption::encryptSnapOrStory(QByteArray data){
    QCA::Initializer init;
    QByteArray encrypted;

    if(!QCA::isSupported("aes128-ecb")){
        qDebug() << "AES128-ECB not supported!\n";
    } else {
        QCA::SymmetricKey key(AES_KEY.toUtf8());

        QCA::Cipher cipher(QString("aes128"),
                           QCA::Cipher::ECB,
                           QCA::Cipher::NoPadding, //Padding done manually above. Broken in QCA with ECB...
                           QCA::Encode,
                           key);

        encrypted = cipher.process(Encryption::PKCS7Padding(data)).toByteArray();

        //qDebug() << "AES128 encryption of " << data << qPrintable(QString("is [0x") + QCA::arrayToHex(encrypted) + QString("]\n"));
    }
    return encrypted;
}

QByteArray Encryption::decryptSnap(QByteArray data){
    QCA::Initializer init;
    QByteArray decrypted;

    if(!QCA::isSupported("aes128-ecb")){
        qDebug() << "AES128-ECB not supported!\n";
    } else {
        QCA::SymmetricKey key(AES_KEY.toUtf8());

        QCA::Cipher cipher(QString("aes128"),
                           QCA::Cipher::ECB,
                           QCA::Cipher::NoPadding, //Padding done manually above. Broken in QCA with ECB...
                           QCA::Decode,
                           key);

        //Cipher decryption
        QCA::SecureArray decryptedWithPKCS7Padding = cipher.process(data);
        //Get the byte array
        decrypted = decryptedWithPKCS7Padding.toByteArray();
        //Remove PKCS7 Padding
        Encryption::RemovePKCS7Padding(decrypted);

        //qDebug() << "AES128 decryption of" << qPrintable(QString("[0x") + QCA::arrayToHex(data) + QString("] is")) << decrypted << "\n";
    }
    return decrypted;
}

QByteArray Encryption::decryptStory(QByteArray data, QString keyStr, QString ivStr){
    QCA::Initializer init;
    QByteArray decrypted;

    if(!QCA::isSupported("aes128-cbc-pkcs7")){
        qDebug() << "AES128-ECB not supported!\n";
    } else {
        QCA::SymmetricKey key(keyStr.toUtf8());
        QCA::InitializationVector iv(ivStr.toUtf8());

        QCA::Cipher cipher(QString("aes128"),
                           QCA::Cipher::CBC,
                           QCA::Cipher::PKCS7,
                           QCA::Decode,
                           key, iv);

        //Cipher decryption
        decrypted = cipher.process(data).toByteArray();

        //qDebug() << "AES128-CBC decryption of" << qPrintable(QString("[0x") + QCA::arrayToHex(data) + QString("] is")) << decrypted << "\n";
    }
    return decrypted;
}

QByteArray& Encryption::PKCS7Padding(QByteArray &bytes){
    //ECB Requires data length to be multiple of 16. If it is not the case
    //That is where PKCS7Padding is useful for.

    //How many times 16 fits in size.
    int count = bytes.size() / 16;
    //How many bytes to add
    int loop = 16 - (bytes.size() - count*16);
    //We always add padding.
    if(loop == 0) loop = 16;
    //PKCS7Padding
    for(int i = 0; i < loop; i++){
        bytes.append((byte)loop);
    }
    return bytes;
}

QByteArray& Encryption::RemovePKCS7Padding(QByteArray &bytes){
    int bytesCountToRemove = (int)bytes.at(bytes.length()-1);
    bytes.remove(bytes.length() - bytesCountToRemove, bytesCountToRemove);
    return bytes;
}
