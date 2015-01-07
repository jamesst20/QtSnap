#include "ConversationController.h"

#include "Snapchat.h"

const QString ConversationController::CONVERSATION_MESSAGES_KEY = "conversation_messages";
const QString ConversationController::MESSAGES_KEY = "messages";
const QString ConversationController::SNAP_KEY = "snap";

const QString ConversationController::UPLOAD_PATH = "ph/upload";
const QString ConversationController::SEND_PATH = "loq/send";
const QString ConversationController::BLOB_PATH = "ph/blob";

const QString ConversationController::USERNAME_KEY = "username";
const QString ConversationController::MEDIA_ID_KEY = "media_id";
const QString ConversationController::DATA_KEY = "data";
const QString ConversationController::TYPE_KEY = "type";
const QString ConversationController::TIMESTAMP_KEY = "timestamp";
const QString ConversationController::REQ_TOKEN_KEY = "req_token";
const QString ConversationController::FEATURES_MAP_KEY = "features_map";
const QString ConversationController::ZIPPED_KEY = "zipped";
const QString ConversationController::RECIPIENTS_KEY = "recipients";
const QString ConversationController::TIME_KEY = "time";
const QString ConversationController::ID_KEY = "id";

ConversationController::ConversationController()
{

}

void ConversationController::initialize(Snapchat *snapchatInstance){
    this->snapchatInstance = snapchatInstance;
}

void ConversationController::parseJsonObject(QJsonArray convsArray){
    snaps.clear();
    //For each friend conversation
    for(int i = 0; i < convsArray.size(); i++){
        QJsonArray messagesArray = convsArray.at(i).toObject()[CONVERSATION_MESSAGES_KEY].toObject()[MESSAGES_KEY].toArray();
        //For each snap/messages with this friend
        for(int z = 0; z < messagesArray.size(); z++){
            //If it is a snap
            if(messagesArray.at(z).toObject().contains(SNAP_KEY)){
                snaps.append(Snap(messagesArray.at(z).toObject()[SNAP_KEY].toObject()));
            }
        }
    }
}

const QList<Snap> &ConversationController::getSnaps() const {
    return this->snaps;
}

void ConversationController::sendSnap(QList<QString> recipients, float time, QFile *file, bool isVideo, int requestID){
    if(recipients.size() > 0 && file){
        if(!file->isOpen()){
            file->open(QFile::ReadOnly);
        }
        if(file->isOpen() && file->isReadable()){
            MediaSendInfo mediaSendInfo;
            mediaSendInfo.recipients = recipients;
            mediaSendInfo.file = file;
            mediaSendInfo.isVideo = isVideo;
            mediaSendInfo.mediaID = Encryption::randomMediaID(this->snapchatInstance->getUsername());
            mediaSendInfo.time = time;
            this->queuedMediaSendInfo.insertMulti(requestID, mediaSendInfo);
            //Upload the media and send it.
            uploadMedia(mediaSendInfo);
        }
    }
}

void ConversationController::uploadMedia(const MediaSendInfo mediaSendInfo){
    QList<QHttpPart> params;
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    params.append(Utils::makeHttpPart(MEDIA_ID_KEY, mediaSendInfo.mediaID));
    params.append(Utils::makeHttpPart(USERNAME_KEY, this->snapchatInstance->getUsername()));
    params.append(Utils::makeHttpPart(DATA_KEY, Encryption::encryptSnapOrStory(mediaSendInfo.file->readAll()), true));
    params.append(Utils::makeHttpPart(TYPE_KEY, QString(mediaSendInfo.isVideo ? "1" : "0")));
    params.append(Utils::makeHttpPart(TIMESTAMP_KEY, QString::number(timestamp)));
    params.append(Utils::makeHttpPart(REQ_TOKEN_KEY, TokenLib::getRequestToken(this->snapchatInstance->getAuthToken(), timestamp)));
    params.append(Utils::makeHttpPart(FEATURES_MAP_KEY, QString("{}")));
    //Execute upload request.
    this->snapchatInstance->getNetworkRequestMaker().executeRequest(this->queuedMediaSendInfo.key(mediaSendInfo), UPLOAD_PATH, params, std::bind(&ConversationController::onMediaUploadFinished, this, _1, _2, _3));
}

void ConversationController::onMediaUploadFinished(int requestID, int httpCode, QByteArray) {
    if(httpCode == 200){
        emit mediaUploadFinished(requestID, true);
        //Send the media.
        sendMedia(this->queuedMediaSendInfo.value(requestID));
    }else{
        emit mediaUploadFinished(requestID, false);
    }
}

void ConversationController::sendMedia(const MediaSendInfo mediaSendInfo){

    QJsonArray recipients;
    for(int i = 0; i < mediaSendInfo.recipients.size(); i++){
        recipients.append(mediaSendInfo.recipients.at(i));
    }

    QHash<QString, QString> params;
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    params.insert(MEDIA_ID_KEY, mediaSendInfo.mediaID);
    params.insert(ZIPPED_KEY, "0");
    params.insert(RECIPIENTS_KEY, QJsonDocument(recipients).toJson());
    params.insert(USERNAME_KEY, this->snapchatInstance->getUsername());
    params.insert(TIME_KEY, QString::number(mediaSendInfo.time));
    params.insert(TIMESTAMP_KEY, QString::number(timestamp));
    params.insert(REQ_TOKEN_KEY, TokenLib::getRequestToken(this->snapchatInstance->getAuthToken(), timestamp));
    params.insert(FEATURES_MAP_KEY, "{}");
    //Execute send request.
    this->snapchatInstance->getNetworkRequestMaker().executeRequest(this->queuedMediaSendInfo.key(mediaSendInfo), SEND_PATH, params, std::bind(&ConversationController::onMediaSendFinished, this, _1, _2, _3));
    //Remove MediaSendInfo from queue
    this->queuedMediaSendInfo.remove(this->queuedMediaSendInfo.key(mediaSendInfo));
}

void ConversationController::onMediaSendFinished(int requestID, int httpCode, QByteArray) {
    if(httpCode >= 200 && httpCode < 300){
        emit mediaSendFinished(requestID, true);
    }else{
        emit mediaSendFinished(requestID, false);
    }
}

void ConversationController::getSnap(const Snap &snap, int requestID){
    QHash<QString, QString> params;
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    params.insert(ID_KEY, snap.getID());
    params.insert(USERNAME_KEY, this->snapchatInstance->getUsername());
    params.insert(TIMESTAMP_KEY, QString::number(timestamp));
    params.insert(REQ_TOKEN_KEY, TokenLib::getRequestToken(this->snapchatInstance->getAuthToken(), timestamp));
    //Execute get snap request
    this->snapchatInstance->getNetworkRequestMaker().executeRequest(requestID, BLOB_PATH, params, std::bind(&ConversationController::onSnapDownloadFinished, this, _1, _2, _3));
}

void ConversationController::onSnapDownloadFinished(int requestID, int httpCode, QByteArray data){
    if(httpCode >= 200 && httpCode < 300){
        emit snapDownloadFinished(requestID, true, Encryption::decryptSnap(data));
    }else{
        emit snapDownloadFinished(requestID, false, data);
    }
}


