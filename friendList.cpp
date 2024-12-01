#include "friendList.h"

FriendNode :: FriendNode(){
    friend_username = "";
    relation = "";
}

FriendNode :: FriendNode(string f_name,string rel) {
    friend_username = f_name;
    relation = rel;
}