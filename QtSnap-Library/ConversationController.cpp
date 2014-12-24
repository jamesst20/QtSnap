#include "ConversationController.h"

const QString ConversationController::CONVERSATION_MESSAGES_KEY = "conversation_messages";
const QString ConversationController::MESSAGES_KEY = "messages";
const QString ConversationController::SNAP_KEY = "snap";

ConversationController::ConversationController()
{

}

void ConversationController::parseJsonObject(QJsonArray convsArray){
    snaps.clear();
    //For each friend conversation
    for(int i = 0; i < convsArray.size(); i++){
        QJsonArray messagesArray = convsArray.at(i).toObject()[CONVERSATION_MESSAGES_KEY].toObject()[MESSAGES_KEY].toArray();
        //For each snap/messages with this friend
        for(int z = 0; z < messagesArray.size(); z++){
            //If it is a snap
            if(messagesArray.at(z).toObject().contains(SNAP_KEY)){
                snaps.append(Snap(messagesArray.at(z).toObject()[SNAP_KEY].toObject()));
            }
        }
    }
}

const QList<Snap> ConversationController::getSnaps() const {
    return this->snaps;
}
