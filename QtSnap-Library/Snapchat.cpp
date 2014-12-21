#include "Snapchat.h"

const QString Snapchat::LOGIN_PATH = "loq/login";

const QString Snapchat::UPDATES_RESPONSE_KEY = "updates_response";
const QString Snapchat::FRIENDS_RESPONSE_KEY = "friends_response";
const QString Snapchat::STORIES_RESPONSE_KEY = "stories_response";
const QString Snapchat::CONVERSATIONS_REPONSE_KEY = "conversations_response";

const QString Snapchat::USERNAME_KEY = "username";
const QString Snapchat::PASSWORD_KEY = "password";
const QString Snapchat::TIMESTAMP_KEY = "timestamp";
const QString Snapchat::REQ_TOKEN_KEY = "req_token";
const QString Snapchat::MESSAGE_KEY = "message";


Snapchat::Snapchat()
{

}

void Snapchat::login(QString username, QString password){
    this->username = username;

    QUrlQuery params;

    long timestamp = QDateTime::currentMSecsSinceEpoch();
    params.addQueryItem(USERNAME_KEY, username);
    params.addQueryItem(PASSWORD_KEY, password);
    params.addQueryItem(REQ_TOKEN_KEY, TokenLib::getStaticRequestToken(timestamp));
    params.addQueryItem(TIMESTAMP_KEY, QString::number(timestamp));

    NetworkRequestMaker *nrm = new NetworkRequestMaker(LOGIN_PATH, params);
    connect(nrm, SIGNAL(onRequestDone(int,QByteArray)), this, SLOT(onLoginCompleted(int,QByteArray)));
    nrm->executeRequest();

}

void Snapchat::onLoginCompleted(int httpCode, QByteArray data){
    //Get the signal emitter (NetworkRequestMaker)
    NetworkRequestMaker *nrm = qobject_cast<NetworkRequestMaker *>(sender());
    //Delete it, free memory
    nrm->deleteLater();

    QJsonParseError jsonError;
    QJsonDocument fullSnapchatDoc = QJsonDocument::fromJson(data, &jsonError);

    if(jsonError.error == QJsonParseError::NoError){
        this->fullSnapchatObj = fullSnapchatDoc.object();

        if(this->fullSnapchatObj.contains(UPDATES_RESPONSE_KEY)){
            emit loginCompleted(true, "");
        }else{
            emit loginCompleted(false, fullSnapchatObj.contains(MESSAGE_KEY) ? fullSnapchatObj[MESSAGE_KEY].toString() : "Unknown error");
        }
    }else{
        emit loginCompleted(false, "Json Parser error : " + jsonError.errorString());
    }
}
