#ifndef SNAP_H
#define SNAP_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

class Snap
{
public:
    Snap(QJsonObject snapObj);

    bool isIncoming() const;
    const QString getID() const;
    const QString getSenderName() const;
    const QString getRecipientName() const;
    qint64 getLastInteractionTime() const;
    qint64 getSentTime() const;
    bool isViewed() const;
    bool isScreenshotted() const;
    float getDuration() const;
    bool isZipped() const;
    bool isVideo() const;
    bool isFriendRequest() const;
    bool isDownloadable() const;

private:
    bool incoming;
    QString id;
    QString senderName;
    QString recipientName;
    int mediaType;
    qint64 timestamp;
    qint64 sentTimestamp;
    int state;
    float timer;
    bool zipped;

    //ALWAYS
    static const QString ID_KEY;
    static const QString STATE_KEY;
    static const QString MEDIA_TYPE_KEY;
    static const QString TIMESTAMP_KEY;
    static const QString SENT_TIMESTAMP_KEY;
    //RECEIVED SNAPS - ALWAYS
    static const QString SENDER_KEY;
    //RECEIVED SNAPS - UNSEEN
    static const QString TIMER_KEY;
    //SENT/RECEIVED - VIDEO SNAPS (ALWAYS)
    static const QString ZIPPED_KEY;
    //SENT - ALWAYS
    static const QString RECIPIENT_KEY;

    //MEDIA TYPE
    static const int IMAGE = 0;
    static const int VIDEO = 1;
    static const int VIDEO_NOAUDIO = 2;
    static const int FRIEND_REQUEST = 3;
    static const int FRIEND_REQUEST_IMAGE = 4;
    static const int FRIEND_REQUEST_VIDEO = 5;
    static const int FRIEND_REQUEST_VIDEO_NOAUDIO = 6;

    //STATE
    static const int SENT = 0;
    static const int DELIVERED = 1;
    static const int VIEWED = 2;
    static const int SCREENSHOT = 3;
};

#endif // SNAP_H
