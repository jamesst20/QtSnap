#include "FriendController.h"

const QString FRIENDS_KEY = "friends";
const QString ADDED_FRIENDS_KEY = "added_friends";
const QString BESTS_KEY = "bests";

FriendController::FriendController(QJsonObject friendsObj)
{
    QJsonArray friendsJson = friendsObj[FRIENDS_KEY].toArray();
    QJsonArray friendRequestsJson = friendsObj[ADDED_FRIENDS_KEY].toArray();
    QJsonArray bestFriendsJson = friendsObj[BESTS_KEY].toArray();

    //Add friends to list
    for(int i = 0; i < friendsJson.size(); i++){
        friends.append(Friend(friendsJson.at(i).toObject()));
    }
    //Add friends request (basically friends + requests) to list
    for(int i = 0; i < friendRequestsJson.size(); i++){
        friendRequests.append(Friend(friendRequestsJson.at(i).toObject()));
    }
    //Add best friends to list
    for(int i = 0; i < bestFriendsJson.size(); i++){
        bestFriends.append(bestFriendsJson.at(i).toString());
    }
}

QList<Friend> FriendController::getFriends(){
    return this->friends;
}

QList<Friend> FriendController::getFriendRequests(){
    return this->friendRequests;
}

QList<QString> FriendController::getBestFriends(){
    return this->bestFriends;
}
