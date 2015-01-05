#include "StoryController.h"

#include "Snapchat.h"

const QString StoryController::STORY_BLOB_PATH = "bq/story_blob";

const QString StoryController::MY_STORIES_KEY = "my_stories";
const QString StoryController::FRIEND_STORIES_KEY = "friend_stories";
const QString StoryController::STORIES_KEY = "stories";

const QString StoryController::STORY_ID = "story_id";

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
    params.insert(STORY_ID, story.getMediaID());
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
