#ifndef SNAPCHAT_H
#define SNAPCHAT_H

#include <memory>
#include <iostream>
#include <functional>

#include <QString>
#include <QDateTime>
#include <QJsonDocument>

#include <QJsonObject>
#include <QJsonArray>

#include "TokenLib.h"
#include "Utils.h"
#include "NetworkRequestMaker.h"

#include "StoryController.h"
#include "FriendController.h"
#include "ConversationController.h"

using namespace std::placeholders;

class Snapchat : public QObject
{
    Q_OBJECT
public:
    Snapchat();

    void login(QString username, QString password);
    void refresh();

    const QString& getUsername() const;
    const QString& getAuthToken() const;
    NetworkRequestMaker& getNetworkRequestMaker();
    FriendController& getFriendController();
    StoryController& getStoryController();
    ConversationController& getConversationController();


private slots:
    void onLoginCompleted(int id, int httpCode, QByteArray data);
    void onRefreshCompleted(int id, int httpCode, QByteArray data);

signals:
    void loginCompleted(bool success, QString reason);
    void refreshCompleted(bool success, QString reason);

private:
    void parseSnapchatObjs();

    NetworkRequestMaker nrm;

    QString username;
    QString authToken;

    FriendController friendController;
    StoryController storyController;
    ConversationController conversationController;

    QJsonObject fullSnapchatObj;
    QJsonObject updatesSnapchatObj;
    QJsonObject friendsSnapchatObj;
    QJsonObject storiesSnapchatObj;
    QJsonArray conversationsSnapchatObj;

    static const QString LOGIN_PATH;
    static const QString ALL_UPDATES_PATH;

    static const QString UPDATES_RESPONSE_KEY;
    static const QString FRIENDS_RESPONSE_KEY;
    static const QString STORIES_RESPONSE_KEY;
    static const QString CONVERSATIONS_REPONSE_KEY;

    static const QString USERNAME_KEY;
    static const QString PASSWORD_KEY;
    static const QString TIMESTAMP_KEY;
    static const QString REQ_TOKEN_KEY;
    static const QString AUTH_TOKEN_KEY;
    static const QString FEATURES_MAP_KEY;
    static const QString MESSAGE_KEY;
    static const QString CHECKSUMS_DICT_KEY;

};

#endif // SNAPCHAT_H
