#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include "Friend.h"

#include <QObject>
#include <QList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class FriendController : public QObject
{
    Q_OBJECT

public:
    FriendController();

    void parseJsonObject(QJsonObject friendsObj);

    const QList<Friend> &getFriends() const;
    const QList<Friend> &getFriendRequests() const;
    const QList<QString> &getBestFriends() const;

signals:
    void onFriendsRefreshed();

private:
    QList<Friend> friends;
    QList<Friend> friendRequests;
    QList<QString> bestFriends;


    static const QString FRIENDS_KEY;
    static const QString ADDED_FRIENDS_KEY;
    static const QString BESTS_KEY;
};

#endif // FRIENDCONTROLLER_H
