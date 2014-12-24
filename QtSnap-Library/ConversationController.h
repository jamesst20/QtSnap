#ifndef CONVERSATIONCONTROLLER_H
#define CONVERSATIONCONTROLLER_H

#include "Snap.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QList>

class ConversationController
{
public:
    ConversationController();

    void parseJsonObject(QJsonArray convsArray);

    const QList<Snap> getSnaps() const;
private:
    QList<Snap> snaps;

    static const QString CONVERSATION_MESSAGES_KEY;
    static const QString MESSAGES_KEY;
    static const QString SNAP_KEY;
};

#endif // CONVERSATIONCONTROLLER_H
