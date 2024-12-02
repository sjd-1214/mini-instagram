#pragma once

#include <iostream>
#include <string>
using namespace std;

class MessageStack; // Forward declaration

void reversePrint(MessageStack *);

struct MessageNode
{
    MessageNode *next;
    MessageNode *prev;
    string message;

    MessageNode(string message);
    string getMessage() const;
};

class MessageStack
{
private:
    string recipient_name;
    MessageNode *top;

public:
    MessageStack();
    MessageStack(string friend_username);

    string getName() const;
    void setName(string name);
    MessageNode *getTop() const;
    bool add_message();
};

struct ChatNode
{
    ChatNode *next;
    ChatNode *prev;
    MessageStack *message_stack;

    ChatNode(string username);
};

class ChatStack
{
private:
    ChatNode *top;

public:
    ChatStack();
    bool newChat(string username);
    ChatNode *getTop() const;
};

class Messages
{
private:
    ChatStack *chat;

public:
    Messages();
    void newChat(string username);
    bool send();
    bool display();
};