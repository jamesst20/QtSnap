#ifndef FRIEND_H
#define FRIEND_H

#include <QList>
#include <QJsonObject>

class Friend
{
public:
    Friend(QJsonObject obj);

    QString getUsername() const;
    QString getDisplayName() const;
    bool isAdded();

private:
    static const QString NAME_KEY;
    static const QString DISPLAY_KEY;
    static const QString TYPE_KEY; //0 = added, 1 = not added.

    QString username;
    QString displayName;
    bool added;
};

#endif // FRIEND_H
