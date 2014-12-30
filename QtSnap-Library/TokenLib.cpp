#include "TokenLib.h"

const QString TokenLib::SECRET = "iEk21fuwZApXlz93750dmW22pw389dPwOk";
const QString TokenLib::PATTERN = "0001110111101110001111010101111011010001001110011000110001000110";
const QString TokenLib::STATIC_TOKEN = "m198sOkJEn37DjqZ32lpRu76xmw288xSQ9";

QString TokenLib::getRequestToken(QString token, qint64 timestamp){
    QString firstHex = hexDigest(TokenLib::SECRET + token);
    QString secondHex = hexDigest(QString::number(timestamp) + TokenLib::SECRET);

    QString requestToken;
    //Create request token via pattern
    for(int i = 0; i < TokenLib::PATTERN.size(); i++){
        QChar pattern = TokenLib::PATTERN.at(i);

        if(pattern == '0'){
            requestToken.append(firstHex.at(i));
        }else{
            requestToken.append(secondHex.at(i));
        }
    }
    return requestToken;
}

QString TokenLib::getStaticRequestToken(qint64 timestamp){
    return getRequestToken(TokenLib::STATIC_TOKEN, timestamp);
}

QString TokenLib::hexDigest(QString toDigest){
    QCryptographicHash hash(QCryptographicHash::Sha256);

    hash.addData(toDigest.toUtf8());

    return QString(hash.result().toHex());
}
