#ifndef STORYCONTROLLER_H
#define STORYCONTROLLER_H

#include "Story.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QFile>

class Snapchat; //Forward declaration
class StoryController : public QObject
{
    Q_OBJECT

    struct StoryInfo {
        QString mediaID;
        QString mediaKey;
        QString mediaIV;

        bool operator==(const StoryInfo& struct2) const
        {
            return this->mediaID == struct2.mediaID;
        }
    };

public:
    StoryController();

    void initialize(Snapchat *snapchat);

    void parseJsonObject(QJsonObject storyObj);

    const QList<Story> &getMyStories() const;
    const QList<Story> &getStories() const;

    void getStory(Story story, int requestID = rand());

    void sendStory(QString caption, float time, QFile *file, bool isVideo, int requestID = rand(), bool videoSound = true);

private slots:
    void onStoryDownloadFinished(int requestID, int httpCode, QByteArray data);
    void onStoryUploadSendFinished(int requestID, int httpCode, QByteArray data);

signals:
    void storyDownloadFinished(int requestID, bool success, QByteArray data);
    void storyUploadSendFinished(int requestID, bool success, QByteArray data);

private:
    Snapchat *snapchatInstance;

    QList<Story> othersStories;
    QList<Story> myStories;

    QHash<int, StoryInfo> queuedStoryInfo;

    static const QString STORY_BLOB_PATH;
    static const QString RETRY_POST_STORY_PATH;

    static const QString MY_STORIES_KEY;
    static const QString FRIEND_STORIES_KEY;
    static const QString STORIES_KEY;

    static const QString STORY_ID_KEY;
    static const QString CLIENT_ID_KEY;
    static const QString STORY_TIMESTAMP_KEY;
    static const QString GROUP_IDS_KEY;
    static const QString MEDIA_ID_KEY;
    static const QString ZIPPED_KEY;
    static const QString MY_STORY_KEY;
    static const QString USERNAME_KEY;
    static const QString CAPTION_TEXT_DISPLAY_KEY;
    static const QString DATA_KEY;
    static const QString TIME_KEY;
    static const QString TYPE_KEY;
    static const QString TIMESTAMP_KEY;
    static const QString REQ_TOKEN_KEY;

    //MEDIA TYPE
    static const int IMAGE = 0;
    static const int VIDEO = 1;
    static const int VIDEO_NOAUDIO = 2;
};

#endif // STORYCONTROLLER_H
