#include "FriendController.h"

const QString FriendController::FRIENDS_KEY = "friends";
const QString FriendController::ADDED_FRIENDS_KEY = "added_friends";
const QString FriendController::BESTS_KEY = "bests";

FriendController::FriendController()
{

}

void FriendController::parseJsonObject(QJsonObject friendsObj){
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

    //Tell listeners
    emit onFriendsRefreshed();
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