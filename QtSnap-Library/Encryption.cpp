#include "Encryption.h"

const QString Encryption::AES_KEY = "M02cnQ51Ji97vwT4";

QByteArray Encryption::encryptSnapOrStory(QByteArray data){
    //Add padding
    Encryption::PKCS7Padding(data);
    //AES/ECB Encryption by hand
    QByteArray encrypted(data.length(), '\0');
    char *encodedBuffer = encrypted.data();
    aes_context ctx;
    aes_setkey_enc(&ctx, (unsigned char *)AES_KEY.toStdString().c_str(), 128);
    for (int i = 0; i < data.length(); i += 16) {
        aes_crypt_ecb(&ctx, AES_ENCRYPT, (unsigned char*)data.constData() + i, (unsigned char*)encodedBuffer + i);
    }
    return encrypted;
}

QByteArray Encryption::decryptSnap(QByteArray data){
    //AES/ECB Decryption by hand
    QByteArray decrypted(data.length(), '\0');
    char *encodedBuffer = decrypted.data();
    aes_context ctx;
    aes_setkey_dec(&ctx, (unsigned char *)AES_KEY.toUtf8().constData(), 128);
    for (int i = 0; i < data.length(); i += 16) {
        aes_crypt_ecb(&ctx, AES_DECRYPT, (unsigned char*)data.constData() + i, (unsigned char*)encodedBuffer + i);
    }
    //Remove PKCS7 Padding
    Encryption::RemovePKCS7Padding(decrypted);
    return decrypted;
}

QByteArray Encryption::decryptStory(QByteArray data, QString keyStr, QString ivStr){
    QByteArray key = keyStr.toUtf8();
    QByteArray iv = ivStr.toUtf8();
    //AES/CBC Encryption by hand..
    QByteArray decrypted;
    aes_context ctx;
    aes_setkey_dec(&ctx, (unsigned char *)key.constData(), 128);
    char *inputBuffer = data.data();
    char *ivBuffer = iv.data();
    for (int i=0; i<data.length() / 16; i++) {
        for (int j=0; j<16; j++) {
            inputBuffer[i + j] ^= ivBuffer[j];
        }
        aes_crypt_ecb(&ctx, AES_DECRYPT, (unsigned char*)data.data() + (i * 16), (unsigned char*)ivBuffer);
        decrypted += QByteArray::fromRawData(ivBuffer, 16);
    }
    //Remove PKCS7 Padding
    Encryption::RemovePKCS7Padding(decrypted);
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

QString Encryption::randomMediaID(QString username){
    return QString(username + "~" + QUuid::createUuid().toString().replace("{", "").replace("}", "")).toUpper();
}
