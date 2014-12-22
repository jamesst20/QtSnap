#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include "Friend.h"

#include <QList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class FriendController
{

public:
    FriendController(QJsonObject friendsObj);

    QList<Friend> getFriends();
    QList<Friend> getFriendRequests();
    QList<QString> getBestFriends();

private:
    QList<Friend> friends;
    QList<Friend> friendRequests;
    QList<QString> bestFriends;


    static const QString FRIENDS_KEY;
    static const QString ADDED_FRIENDS_KEY;
    static const QString BESTS_KEY;
};

#endif // FRIENDCONTROLLER_H
