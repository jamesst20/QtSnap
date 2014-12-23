#include "Snapchat.h"

const QString Snapchat::LOGIN_PATH = "loq/login";
const QString Snapchat::ALL_UPDATES_PATH = "loq/all_updates";

const QString Snapchat::UPDATES_RESPONSE_KEY = "updates_response";
const QString Snapchat::FRIENDS_RESPONSE_KEY = "friends_response";
const QString Snapchat::STORIES_RESPONSE_KEY = "stories_response";
const QString Snapchat::CONVERSATIONS_REPONSE_KEY = "conversations_response";

const QString Snapchat::USERNAME_KEY = "username";
const QString Snapchat::PASSWORD_KEY = "password";
const QString Snapchat::TIMESTAMP_KEY = "timestamp";
const QString Snapchat::REQ_TOKEN_KEY = "req_token";
const QString Snapchat::AUTH_TOKEN_KEY = "auth_token";
const QString Snapchat::FEATURES_MAP_KEY = "features_map";
const QString Snapchat::MESSAGE_KEY = "message";
const QString Snapchat::CHECKSUMS_DICT_KEY = "checksums_dict";


Snapchat::Snapchat()
{

}

void Snapchat::login(QString username, QString password){
    this->username = username;

    QUrlQuery params;

    long timestamp = QDateTime::currentMSecsSinceEpoch();
    params.addQueryItem(USERNAME_KEY, username);
    params.addQueryItem(TIMESTAMP_KEY, QString::number(timestamp));
    params.addQueryItem(REQ_TOKEN_KEY, TokenLib::getStaticRequestToken(timestamp));
    params.addQueryItem(PASSWORD_KEY, password);
    params.addQueryItem(FEATURES_MAP_KEY, "{\"all_updates_friends_response\":true}");


    NetworkRequestMaker *nrm = new NetworkRequestMaker();
    connect(nrm, SIGNAL(onRequestDone(int,QByteArray)), this, SLOT(onLoginCompleted(int,QByteArray)));
    nrm->executeRequest(LOGIN_PATH, params);

}

void Snapchat::onLoginCompleted(int httpCode, QByteArray data){
    QJsonParseError jsonError;
    QJsonDocument fullSnapchatDoc = QJsonDocument::fromJson(data, &jsonError);

    if(jsonError.error == QJsonParseError::NoError){
        this->fullSnapchatObj = fullSnapchatDoc.object();

        if(this->fullSnapchatObj.contains(UPDATES_RESPONSE_KEY)){            
            parseSnapchatObjs();
            emit loginCompleted(true, "");
        }else{
            emit loginCompleted(false, fullSnapchatObj.contains(MESSAGE_KEY) ? fullSnapchatObj[MESSAGE_KEY].toString() : "Unknown error. Http Code : " + httpCode);
        }
    }else{
        emit loginCompleted(false, "Json Parser error : " + jsonError.errorString());
    }
}

void Snapchat::refresh(){
    QUrlQuery params;

    long timestamp = QDateTime::currentMSecsSinceEpoch();
    params.addQueryItem(USERNAME_KEY, username);
    params.addQueryItem(TIMESTAMP_KEY, QString::number(timestamp));
    params.addQueryItem(REQ_TOKEN_KEY, TokenLib::getRequestToken(authToken, timestamp));
    params.addQueryItem(FEATURES_MAP_KEY, "{\"all_updates_friends_response\":true}");
    params.addQueryItem(CHECKSUMS_DICT_KEY, "{}");


    NetworkRequestMaker *nrm = new NetworkRequestMaker();
    connect(nrm, SIGNAL(onRequestDone(int,QByteArray)), this, SLOT(onRefreshCompleted(int,QByteArray)));
    nrm->executeRequest(ALL_UPDATES_PATH, params);
}

void Snapchat::onRefreshCompleted(int httpCode, QByteArray data){
    if(httpCode >= 200 && httpCode < 300){
        this->fullSnapchatObj = QJsonDocument::fromJson(data).object();
        parseSnapchatObjs();
        emit refreshCompleted(true, "");
    }else{
        emit refreshCompleted(false, "Bad HTTP Code : " + httpCode);
    }
}

void Snapchat::parseSnapchatObjs(){
    //Store Snapchat Objs
    this->updatesSnapchatObj = fullSnapchatObj[UPDATES_RESPONSE_KEY].toObject();
    this->friendsSnapchatObj = fullSnapchatObj[FRIENDS_RESPONSE_KEY].toObject();
    this->storiesSnapchatObj = fullSnapchatObj[STORIES_RESPONSE_KEY].toObject();
    this->conversationsSnapchatObj = fullSnapchatObj[CONVERSATIONS_REPONSE_KEY].toArray();
    //Initialize Controllers
    this->friendController.parseJsonObject(this->friendsSnapchatObj);
    //Save authToken used for all requests.
    this->authToken = this->updatesSnapchatObj[AUTH_TOKEN_KEY].toString();
}

FriendController* Snapchat::getFriendController(){
    return &this->friendController;
}
