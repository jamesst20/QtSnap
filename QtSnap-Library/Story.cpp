#include "Story.h"

//Shared key
const QString Story::STORY_KEY = "story";
const QString Story::ID_KEY = "id";
const QString Story::USERNAME_KEY = "username";
const QString Story::MATURE_CONTENT_KEY = "mature_content";
const QString Story::CLIENT_ID_KEY = "client_id";
const QString Story::TIMESTAMP_KEY = "timestamp";
const QString Story::MEDIA_ID_KEY = "media_id";
const QString Story::MEDIA_KEY_KEY = "media_key";
const QString Story::MEDIA_IV_KEY = "media_iv";
const QString Story::THUMBNAIL_IV_KEY = "thumbnail_iv";
const QString Story::MEDIA_TYPE_KEY = "media_type";
const QString Story::TIME_KEY = "time";
const QString Story::CAPTION_TEXT_DISPLAY_KEY = "caption_text_display";
const QString Story::ZIPPED_KEY = "zipped";
const QString Story::TIME_LEFT_KEY = "time_left";
const QString Story::MEDIA_URL_KEY = "media_url";
const QString Story::THUMBNAIL_URL_KEY = "thumbnail_url";
//Other's story key
const QString Story::VIEWED_KEY = "viewed";
//Own story key
const QString Story::STORY_NOTES_KEY = "story_notes";
const QString Story::STORY_EXTRAS_KEY = "story_extras";
const QString Story::VIEW_COUNT_KEY = "view_count";
const QString Story::SCREENSHOT_COUNT_KEY = "screenshot_count";

Story::Story(QJsonObject fullStoryObj, bool isMyStory)
{
    this->isMyStory = isMyStory;

    QJsonObject storyObj = fullStoryObj[STORY_KEY].toObject();

    if(isMyStory){
        //Parse story notes
        QJsonArray storyNotesArray = fullStoryObj[STORY_NOTES_KEY].toArray();
        for(int i = 0; i < storyNotesArray.size(); i++){
            viewers.append(Viewer(storyNotesArray.at(i).toObject()));
        }
        //Parse story extras
        QJsonObject storyExtrasObj = fullStoryObj[STORY_EXTRAS_KEY].toObject();
        this->viewCount = storyExtrasObj[VIEW_COUNT_KEY].toInt();
        this->screenshotCount = storyExtrasObj[SCREENSHOT_COUNT_KEY].toInt();
    }else{
        this->viewed = fullStoryObj[VIEWED_KEY].toBool();
    }

    this->id = storyObj[ID_KEY].toString();
    this->author = storyObj[USERNAME_KEY].toString();
    this->matureContent = storyObj[MATURE_CONTENT_KEY].toBool();
    this->clientID = storyObj[CLIENT_ID_KEY].toString();
    this->timestamp = storyObj[TIMESTAMP_KEY].toString().toLong();
    this->media_id = storyObj[MEDIA_ID_KEY].toString();
    this->media_key = storyObj[MEDIA_KEY_KEY].toString();
    this->media_iv = storyObj[MEDIA_IV_KEY].toString();
    this->thumbnail_iv = storyObj[THUMBNAIL_IV_KEY].toString();
    this->mediaType = storyObj[MEDIA_TYPE_KEY].toInt();
    this->time = storyObj[TIME_KEY].toString().toFloat();
    this->text = storyObj[CAPTION_TEXT_DISPLAY_KEY].toString();
    this->zipped = storyObj[ZIPPED_KEY].toBool();
    this->timeLeft = storyObj[TIME_LEFT_KEY].toString().toLong();
    this->media_url = storyObj[MEDIA_URL_KEY].toString();
    this->thumbnail_url = storyObj[THUMBNAIL_URL_KEY].toString();

}

const QString Story::getID() const {
    return this->id;
}

const QString Story::getAuthor() const {
    return this->author;
}

bool Story::hasMatureContent() const {
    return this->matureContent;
}

const QString Story::getClientID() const {
    return this->clientID;
}

long Story::getSentTime() const {
    return this->timestamp;
}

const QString Story::getMediaID() const {
    return this->media_id;
}

const QString Story::getMediaKey() const {
    return this->media_key;
}

const QString Story::getMediaIV() const {
    return this->media_iv;
}

const QString Story::getThumbnailIV() const {
    return this->thumbnail_iv;
}

bool Story::isVideo() const {
    return this->mediaType == 1;
}

float Story::getDuration() const {
    return this->time;
}

const QString Story::getCaptionText() const {
    return this->text;
}

bool Story::isZipped() const {
    return this->zipped;
}

long Story::getTimeLeft() const {
    return this->timeLeft;
}

const QString Story::getMediaURL() const {
    return this->media_url;
}

const QString Story::getThumbnailURL() const {
    return this->thumbnail_url;
}

//Only for other's story
bool Story::isViewed() const {
    return this->viewed;
}

//Only for our story
int Story::getViewCount() const {
    return this->viewCount;
}

int Story::getScreenshotCount() const {
    return this->screenshotCount;
}

const QList<Viewer> Story::getViewers() const {
    return this->viewers;
}

