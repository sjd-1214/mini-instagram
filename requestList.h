#pragma once
#include <iostream>
#include <string>
using namespace std;

struct RequestNode
{
    string friend_username;
    bool is_pending;
    RequestNode(string);
};

class RequestList
{
private:
RequestNode* front;
RequestNode* back;
public:
    RequestList();
    void bulkRequestAccept();
    void acceptRequest();
    void makeRequest();
};