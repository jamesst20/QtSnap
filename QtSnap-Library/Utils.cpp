#include "Utils.h"

QFile* Utils::file_log = 0;

QHttpPart Utils::makeHttpPart(QString name, QByteArray body, bool file){
    QHttpPart httpPart;
    if(!file){
        httpPart.setHeader(QNetworkRequest::ContentDispositionHeader,  QVariant("form-data; name=\"" + name + "\""));
    }else{
        httpPart.setHeader(QNetworkRequest::ContentDispositionHeader,  QVariant("form-data; name=\"" + name + "\"; filename=\"data\""));
        httpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    }
    httpPart.setBody(body);
    return httpPart;
}

QHttpPart Utils::makeHttpPart(QString name, QString body, bool file){
    return Utils::makeHttpPart(name, body.toUtf8(), file);
}

void Utils::log(QString text){
    if (!file_log){
        if (QFile::exists("./logs.txt")){
            QFile::remove("./logs.txt");
        }
        file_log = new QFile("./logs.txt");
        file_log->open(QIODevice::WriteOnly | QIODevice::Text);
    }
    QTextStream out(file_log);
    out.setCodec("UTF-8");
    out << text << "\n";
}
