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
    friends.clear();
    for(int i = 0; i < friendsJson.size(); i++){
        friends.append(Friend(friendsJson.at(i).toObject()));
    }
    //Add friends request (basically friends + requests) to list
    friendRequests.clear();
    for(int i = 0; i < friendRequestsJson.size(); i++){
        friendRequests.append(Friend(friendRequestsJson.at(i).toObject()));
    }
    //Add best friends to list
    bestFriends.clear();
    for(int i = 0; i < bestFriendsJson.size(); i++){
        bestFriends.append(bestFriendsJson.at(i).toString());
    }

    //Tell listeners
    emit onFriendsRefreshed();
}

const QList<Friend> &FriendController::getFriends() const{
    return this->friends;
}

const QList<Friend> &FriendController::getFriendRequests() const{
    return this->friendRequests;
}

const QList<QString> &FriendController::getBestFriends() const{
    return this->bestFriends;
}
