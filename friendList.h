#pragma once
#include <iostream>
#include <string>
using namespace std;

struct FriendNode
{
    string friend_username;
    FriendNode(string);

};

class FriendList
{
private:
    FriendNode* top;
public:
    FriendList();
    FriendNode* getTop()const;
    void addFriend();
};
