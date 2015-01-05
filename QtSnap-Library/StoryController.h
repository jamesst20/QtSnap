#ifndef STORYCONTROLLER_H
#define STORYCONTROLLER_H

#include "Story.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>

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

private slots:
    void onStoryDownloadFinished(int requestID, int httpCode, QByteArray data);

signals:
    void storyDownloadFinished(int requestID, bool success, QByteArray data);

private:
    Snapchat *snapchatInstance;

    QList<Story> othersStories;
    QList<Story> myStories;

    QHash<int, StoryInfo> queuedStoryInfo;

    static const QString STORY_BLOB_PATH;

    static const QString MY_STORIES_KEY;
    static const QString FRIEND_STORIES_KEY;
    static const QString STORIES_KEY;

    static const QString STORY_ID;
};

#endif // STORYCONTROLLER_H
