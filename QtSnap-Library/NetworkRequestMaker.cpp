#include "NetworkRequestMaker.h"

QString NetworkRequestMaker::BASE_URL = "https://feelinsonice-hrd.appspot.com/";
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

void NetworkRequestMaker::executeRequest(int id, const QString &url, const QUrlQuery &params, std::function<void(int, int, QByteArray)> callback_function){
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
    //Ignore certificates error in case of proxy
    reply->ignoreSslErrors();
    //Add to callback list
    this->callback_list.insert(reply, RequestCallbackInfo(id, callback_function));
}

void NetworkRequestMaker::executeRequest(int id, const QString &url, const QList<QHttpPart> &params, std::function<void(int, int, QByteArray)> callback_function){
    //Create request
    QNetworkRequest request = QNetworkRequest(QUrl(BASE_URL + url));
    //Add parameters to QHttpMultiPart
    QHttpMultiPart *parameters = new QHttpMultiPart(this->manager);
    for(int i = 0; i < params.size(); i++){
        parameters->append(params.at(i));
    }
    //Setup headers
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::UserAgentHeader, HEADER_USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + parameters->boundary());
    //Execute POST request
    QNetworkReply *reply = this->manager->post(request, parameters);
    //Ignore certificates error in case of proxy
    reply->ignoreSslErrors();
    //Add to callback list
    this->callback_list.insert(reply, RequestCallbackInfo(id, callback_function));
}

void NetworkRequestMaker::executeRequest(int id, const QString &url, const QHash<QString, QString> &params, std::function<void(int, int, QByteArray)> callback_function){
    QString urlWithParameters = url;
    //Add parameters to URL
    for(int i = 0; i < params.size(); i++){
        urlWithParameters += (i == 0 ? "?" : "&") + params.keys().at(i) + "=" + params.values().at(i);
    }
    //Create request
    QNetworkRequest request = QNetworkRequest(QUrl(BASE_URL + urlWithParameters));
    //Setup headers
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::UserAgentHeader, HEADER_USER_AGENT);
    //Execute GET request
    QNetworkReply *reply = this->manager->get(request);
    //Ignore certificates error in case of proxy
    reply->ignoreSslErrors();
    //Add to callback list
    this->callback_list.insert(reply, RequestCallbackInfo(id, callback_function));
}

void NetworkRequestMaker::finished(QNetworkReply *reply){
    //Read output data
    QByteArray dataRead = reply->readAll();
    //Log request history
    Utils::log("Request to " + reply->url().toString() + " Result : " + dataRead);
    //Get request callback info
    RequestCallbackInfo reqCallInfo = this->callback_list.take(reply);
    //Get the callback function
    std::function<void(int, int, QByteArray)> callbackFunction = reqCallInfo.callback_func;
    //Call it
    callbackFunction(reqCallInfo.id, QVariant(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)).toInt(), dataRead);
}
