#ifndef STORY_H
#define STORY_H

#include "Viewer.h"

#include <QJsonObject>
#include <QJsonArray>

#include <QList>

class Story
{

public:
    Story(QJsonObject fullStoryObj, bool isMyStory);

    const QString getID() const;
    const QString getAuthor() const;
    bool hasMatureContent() const;
    const QString getClientID() const;
    qint64 getSentTime() const;
    const QString getMediaID() const;
    const QString getMediaKey() const;
    const QString getMediaIV() const;
    const QString getThumbnailIV() const;
    bool isVideo() const;
    float getDuration() const;
    const QString getCaptionText() const;
    bool isZipped() const;
    qint64 getTimeLeft() const;
    const QString getMediaURL() const;
    const QString getThumbnailURL() const;
    //Only for other's story
    bool isViewed() const;
    //Only for our story
    int getViewCount() const;
    int getScreenshotCount() const;
    const QList<Viewer> getViewers() const;


private:
    bool isMyStory;

    //For all stories
    QString id;
    QString author;
    bool matureContent;
    QString clientID;
    qint64 timestamp;
    QString media_id;
    QString media_key;
    QString media_iv;
    QString thumbnail_iv;
    int mediaType;
    float time;
    QString text;
    bool zipped;
    qint64 timeLeft;
    QString media_url;
    QString thumbnail_url;

    //Only for other's story
    bool viewed;
    //Only for our story
    int viewCount;
    int screenshotCount;
    QList<Viewer> viewers;

    //Shared key
    static const QString STORY_KEY;
    static const QString ID_KEY;
    static const QString USERNAME_KEY;
    static const QString MATURE_CONTENT_KEY;
    static const QString CLIENT_ID_KEY;
    static const QString TIMESTAMP_KEY;
    static const QString MEDIA_ID_KEY;
    static const QString MEDIA_KEY_KEY;
    static const QString MEDIA_IV_KEY;
    static const QString THUMBNAIL_IV_KEY;
    static const QString MEDIA_TYPE_KEY;
    static const QString TIME_KEY;
    static const QString CAPTION_TEXT_DISPLAY_KEY;
    static const QString ZIPPED_KEY;
    static const QString TIME_LEFT_KEY;
    static const QString MEDIA_URL_KEY;
    static const QString THUMBNAIL_URL_KEY;
    //Other's story key
    static const QString VIEWED_KEY;
    //Own story key
    static const QString STORY_NOTES_KEY;
    static const QString STORY_EXTRAS_KEY;
    static const QString VIEW_COUNT_KEY;
    static const QString SCREENSHOT_COUNT_KEY;

};

#endif // STORY_H
