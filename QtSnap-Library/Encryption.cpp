#include "Encryption.h"

const QString Encryption::AES_KEY = "M02cnQ51Ji97vwT4"; //16 bytes --> 128 bits

QByteArray Encryption::encryptSnapOrStory(QByteArray input){
    //Add padding
    Encryption::PKCS7Padding(input);

    QByteArray result;
    result.resize(input.size());

    //Create aes cipher
    aes_context ctx;
    aes_init(&ctx);
    //Set encryption key
    aes_setkey_enc(&ctx, (unsigned char *)AES_KEY.toStdString().c_str(), AES_KEY.size()*8);
    //AES_ECB only proceeds block of 16 bytes.
    for (int i = 0; i < input.length(); i += 16) {
        aes_crypt_ecb(&ctx, AES_ENCRYPT,
                      (const unsigned char*)input.constData() + i,
                      (unsigned char*)result.data() + i);
    }
    //Free memory
    aes_free(&ctx);
    return result;
}

QByteArray Encryption::decryptSnap(QByteArray input){
    //AES/ECB Decryption by hand
    QByteArray result;
    result.resize(input.size());
    //Create aes cipher
    aes_context ctx;
    aes_init(&ctx);
    //Set decryption key
    aes_setkey_dec(&ctx, (unsigned char *)AES_KEY.toUtf8().constData(), AES_KEY.size()*8);
    //AES_ECB only proceeds block of 16 bytes.
    for (int i = 0; i < input.length(); i += 16) {
        aes_crypt_ecb(&ctx, AES_DECRYPT,
                      (const unsigned char*)input.constData() + i,
                      (unsigned char*)result.data() + i);
    }
    //Free memory
    aes_free(&ctx);

    //Remove PKCS7 Padding
    Encryption::RemovePKCS7Padding(result);
    return result;
}

QByteArray Encryption::decryptStory(QByteArray data, QString keyStr, QString ivStr){
    QByteArray result;
    QByteArray key = QByteArray::fromBase64(keyStr.toUtf8());
    QByteArray iv = QByteArray::fromBase64(ivStr.toUtf8());

    result.resize(data.size());

    aes_context ctx;
    aes_init(&ctx);

    aes_setkey_dec(&ctx, (const unsigned char*)key.data(), key.size()*8);

    aes_crypt_cbc(&ctx, AES_DECRYPT,
                  data.size(),
                  (unsigned char*)iv.data(),
                  (const unsigned char*)data.data(),
                  (unsigned char*)result.data());
    aes_free(&ctx);

    Encryption::RemovePKCS7Padding(result);

    return result;
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
        bytes.append((quint8)loop);
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
