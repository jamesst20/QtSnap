#include "NetworkRequestMaker.h"

const QString NetworkRequestMaker::BASE_URL = "https://feelinsonice-hrd.appspot.com/";
const QString NetworkRequestMaker::HEADER_USER_AGENT = "Snapchat/8.1.0.8 Beta (A0001; Android 21; gzip)";
const QString NetworkRequestMaker::HEADER_URL_ENCODED = "application/x-www-form-urlencoded";

NetworkRequestMaker::NetworkRequestMaker(){
    //Initialize variables
    this->manager = new QNetworkAccessManager(this);

    //Connect signals
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

NetworkRequestMaker::~NetworkRequestMaker(){
    delete this->manager;
}

void NetworkRequestMaker::executeRequest(const QString &url, const QUrlQuery &params){
    //Create request
    QNetworkRequest request = QNetworkRequest(QUrl(BASE_URL + url));
    //Setup headers
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::UserAgentHeader, HEADER_USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, HEADER_URL_ENCODED);
    //Add parameters to byte array
    QByteArray parameters;
    parameters.append(params.toString());
    //Execute POST request
    QNetworkReply *reply = this->manager->post(request, parameters);
    qDebug() << reply;
    //Ignore certificates error in case of proxy
    reply->ignoreSslErrors();
}

void NetworkRequestMaker::executeRequest(const QString &url, const QList<QHttpPart> &params){
    //Create request
    QNetworkRequest request = QNetworkRequest(QUrl(BASE_URL + url));
    //Setup headers
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::UserAgentHeader, HEADER_USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QHttpMultiPart::FormDataType);
    //Add parameters to QHttpMultiPart
    QHttpMultiPart parameters;
    for(int i = 0; i < params.size(); i++){
        parameters.append(params.at(i));
    }
    //Execute POST request
    QNetworkReply *reply = this->manager->post(request, &parameters);

    //Ignore certificates error in case of proxy
    reply->ignoreSslErrors();
}

void NetworkRequestMaker::finished(QNetworkReply *reply){
    //Read output data
    QByteArray dataRead = reply->readAll();
    //Log request history
    Utils::log("Request to " + reply->url().toString() + " Result : " + dataRead);
    //Emit signal telling the request is done
    emit onRequestDone(QVariant(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)).toInt(), dataRead);
}
