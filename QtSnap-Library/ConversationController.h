#ifndef CONVERSATIONCONTROLLER_H
#define CONVERSATIONCONTROLLER_H

#include "Snap.h"
#include "Encryption.h"

#include <QJsonArray>
#include <QJsonObject>

#include <QFile>
#include <QList>

class Snapchat;//Forward Declaration
class ConversationController : public QObject
{
    Q_OBJECT

    struct MediaSendInfo {
        QList<QString> recipients;
        QString mediaID;
        float time;
        QFile *file;
        bool isVideo;

        bool operator==(const MediaSendInfo& struct2) const
        {
            return this->mediaID == struct2.mediaID;
        }
    };

public:
    ConversationController();

    void initialize(Snapchat *snapchatInstance);
    void parseJsonObject(const QJsonArray convsArray);

    const QList<Snap> &getSnaps() const;

    void sendSnap(QList<QString> recipients, float time, QFile *file, bool isVideo, int requestID = rand());
    void getSnap(const Snap &snap, int requestID = rand());

private slots:
    void onMediaUploadFinished(int requestID, int httpCode, QByteArray data);
    void onMediaSendFinished(int requestID, int httpCode, QByteArray data);
    void onSnapDownloadFinished(int requestID, int httpCode, QByteArray data);

signals:
    void mediaUploadFinished(int requestID, bool success);
    void mediaSendFinished(int requestID, bool success);
    void snapDownloadFinished(int requestID, bool success, QByteArray data);

private:
    void uploadMedia(const MediaSendInfo mediaSendInfo);
    void sendMedia(const MediaSendInfo mediaSendInfo);

    Snapchat *snapchatInstance;

    QList<Snap> snaps;

    QHash<int, MediaSendInfo> queuedMediaSendInfo;

    static const QString CONVERSATION_MESSAGES_KEY;
    static const QString MESSAGES_KEY;
    static const QString SNAP_KEY;

    static const QString UPLOAD_PATH;
    static const QString SEND_PATH;
    static const QString BLOB_PATH;

    static const QString USERNAME_KEY;
    static const QString MEDIA_ID_KEY;
    static const QString DATA_KEY;
    static const QString TYPE_KEY;
    static const QString TIMESTAMP_KEY;
    static const QString REQ_TOKEN_KEY;
    static const QString FEATURES_MAP_KEY;
    static const QString ZIPPED_KEY;
    static const QString RECIPIENTS_KEY;
    static const QString TIME_KEY;
    static const QString ID_KEY;

};

#endif // CONVERSATIONCONTROLLER_H
