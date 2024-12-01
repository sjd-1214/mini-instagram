#include "friendList.h"

FriendNode :: FriendNode(string f_name) {
    friend_username = f_name;
}

FriendList :: FriendList(){
    top = nullptr;
}

FriendNode* FriendList :: getTop() const{
    return top;
}