#ifndef STORYCONTROLLER_H
#define STORYCONTROLLER_H

#include "Story.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>

class StoryController
{
public:
    StoryController();

    void parseJsonObject(QJsonObject storyObj);

    const QList<Story> getMyStories() const;
    const QList<Story> getStories() const;

private:
    QList<Story> othersStories;
    QList<Story> myStories;

    static const QString MY_STORIES_KEY;
    static const QString FRIEND_STORIES_KEY;
    static const QString STORIES_KEY;
};

#endif // STORYCONTROLLER_H
