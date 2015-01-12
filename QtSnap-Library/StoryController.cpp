#include "StoryController.h"

#include "Snapchat.h"

const QString StoryController::STORY_BLOB_PATH = "bq/story_blob";
const QString StoryController::RETRY_POST_STORY_PATH = "bq/retry_post_story";

const QString StoryController::MY_STORIES_KEY = "my_stories";
const QString StoryController::FRIEND_STORIES_KEY = "friend_stories";
const QString StoryController::STORIES_KEY = "stories";

const QString StoryController::STORY_ID_KEY = "story_id";
const QString StoryController::CLIENT_ID_KEY = "client_id";
const QString StoryController::STORY_TIMESTAMP_KEY = "story_timestamp";
const QString StoryController::GROUP_IDS_KEY = "group_ids";
const QString StoryController::MEDIA_ID_KEY = "media_id";
const QString StoryController::ZIPPED_KEY = "zipped";
const QString StoryController::MY_STORY_KEY = "my_story";
const QString StoryController::USERNAME_KEY = "username";
const QString StoryController::CAPTION_TEXT_DISPLAY_KEY = "caption_text_display";
const QString StoryController::DATA_KEY = "data";
const QString StoryController::TIME_KEY = "time";
const QString StoryController::TYPE_KEY = "type";
const QString StoryController::TIMESTAMP_KEY = "timestamp";
const QString StoryController::REQ_TOKEN_KEY = "req_token";

StoryController::StoryController()
{

}

void StoryController::initialize(Snapchat *snapchat){
    this->snapchatInstance = snapchat;
}

void StoryController::parseJsonObject(QJsonObject storyObj){
    QJsonArray myStoriesArray = storyObj[MY_STORIES_KEY].toArray();
    QJsonArray friendStoriesArray = storyObj[FRIEND_STORIES_KEY].toArray();
    //Parse my stories
    this->myStories.clear();
    for(int i = 0; i < myStoriesArray.size(); i++){
        this->myStories.append(Story(myStoriesArray.at(i).toObject(), true));
    }

    //Parse other's stories
    this->othersStories.clear();
    //For each friend having posted a story
    for(int i = 0; i < friendStoriesArray.size(); i++){
        QJsonArray storiesByThisFriend = friendStoriesArray.at(i).toObject()[STORIES_KEY].toArray();
        //For each snap in his story
        for(int z = 0; z < storiesByThisFriend.size(); z++){
            this->othersStories.append(Story(storiesByThisFriend.at(z).toObject(), false));
        }
    }
}

const QList<Story> &StoryController::getMyStories() const{
    return this->myStories;
}

const QList<Story> &StoryController::getStories() const{
    return this->othersStories;
}

void StoryController::getStory(Story story, int requestID){
    //Create story info. Required for later (i.e. decryption).
    StoryInfo storyInfo;
    storyInfo.mediaID = story.getMediaID();
    storyInfo.mediaKey = story.getMediaKey();
    storyInfo.mediaIV = story.getMediaIV();
    //Request parameters
    QHash<QString, QString> params;
    params.insert(STORY_ID_KEY, story.getMediaID());
    //Add to queue
    this->queuedStoryInfo.insertMulti(requestID, storyInfo);
    //Execute download request
    this->snapchatInstance->getNetworkRequestMaker().executeRequest(requestID, STORY_BLOB_PATH, params, std::bind(&StoryController::onStoryDownloadFinished, this, _1, _2, _3));
}

void StoryController::onStoryDownloadFinished(int requestID, int httpCode, QByteArray data){
    //Get story info from queue
    StoryInfo storyInfo = this->queuedStoryInfo.value(requestID);
    //Check if the request was successful
    if(httpCode >= 200 && httpCode < 300){
        //emit storyDownloadFinished(requestID, true, data);
        emit storyDownloadFinished(requestID, true, Encryption::decryptStory(data, storyInfo.mediaKey, storyInfo.mediaIV));
    }else{
        emit storyDownloadFinished(requestID, false, data);
    }
    //Remove from queue
    this->queuedStoryInfo.remove(requestID);
}

void StoryController::sendStory(QString caption, float time, QFile *file, bool isVideo, int requestID, bool videoSound){
    if(file){
        if(!file->isOpen()){
            file->open(QFile::ReadOnly);
        }
        if(file->isOpen() && file->isReadable()){
            QList<QHttpPart> params;
            qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
            QString mediaID = Encryption::randomMediaID(this->snapchatInstance->getUsername());
            params.append(Utils::makeHttpPart(CLIENT_ID_KEY, mediaID));
            params.append(Utils::makeHttpPart(MEDIA_ID_KEY, mediaID));
            params.append(Utils::makeHttpPart(GROUP_IDS_KEY, QString("[]")));
            params.append(Utils::makeHttpPart(ZIPPED_KEY, QString("0")));
            params.append(Utils::makeHttpPart(MY_STORY_KEY, QString("true")));
            params.append(Utils::makeHttpPart(USERNAME_KEY, this->snapchatInstance->getUsername()));
            params.append(Utils::makeHttpPart(CAPTION_TEXT_DISPLAY_KEY, caption));
            params.append(Utils::makeHttpPart(DATA_KEY, Encryption::encryptSnapOrStory(file->readAll()), true));
            params.append(Utils::makeHttpPart(TIME_KEY, QString::number(time)));
            params.append(Utils::makeHttpPart(TYPE_KEY, QString::number((isVideo && videoSound) ? (VIDEO) : (isVideo && !videoSound ? (VIDEO_NOAUDIO) : (IMAGE)))));
            params.append(Utils::makeHttpPart(TIMESTAMP_KEY, QString::number(timestamp)));
            params.append(Utils::makeHttpPart(REQ_TOKEN_KEY, TokenLib::getRequestToken(this->snapchatInstance->getAuthToken(), timestamp)));
            //TODO : STORY_TIMESTAMP_KEY, THUMBNAIL_DATA. WITHOUT THOSE, THERE ARE RISK OF BANISHMENT.
            this->snapchatInstance->getNetworkRequestMaker().executeRequest(requestID, RETRY_POST_STORY_PATH, params, std::bind(&onStoryUploadSendFinished, this, _1, _2, _3));
        }
    }
}

void StoryController::onStoryUploadSendFinished(int requestID, int httpCode, QByteArray data){
    emit storyUploadSendFinished(requestID, httpCode >= 200 && httpCode < 300, data);
}
