#include "Friend.h"

const QString Friend::NAME_KEY = "name";
const QString Friend::DISPLAY_KEY = "display";
const QString Friend::TYPE_KEY = "type";

Friend::Friend(QJsonObject obj)
{
    this->username = obj[NAME_KEY].toString();
    this->displayName = obj[DISPLAY_KEY].toString();
    this->added = obj[TYPE_KEY].toInt() == 0 ? true : false;
}

QString Friend::getUsername() const{
    return this->username;
}

QString Friend::getDisplayName() const {
    return this->displayName;
}

bool Friend::isAdded(){
    return this->added;
}
