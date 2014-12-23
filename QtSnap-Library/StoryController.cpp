#include "StoryController.h"

const QString StoryController::MY_STORIES_KEY = "my_stories";
const QString StoryController::FRIEND_STORIES_KEY = "friend_stories";
const QString StoryController::STORIES_KEY = "stories";

StoryController::StoryController()
{

}

void StoryController::parseJsonObject(QJsonObject storyObj){
    QJsonArray myStoriesArray = storyObj[MY_STORIES_KEY].toArray();
    QJsonArray friendStoriesArray = storyObj[FRIEND_STORIES_KEY].toArray();
    qDebug() << "Friend stories array : " << friendStoriesArray.size();
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

const QList<Story> StoryController::getMyStories() const{
    return this->myStories;
}

const QList<Story> StoryController::getStories() const{
    return this->othersStories;
}
