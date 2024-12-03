#include "messages.h"

Messages::Messages()
{
    chat_list = nullptr;
}

void Messages::deleteChatList()
{
    ChatNode *current = chat_list;
    while (current != nullptr)
    {
        ChatNode *temp = current;
        deleteMessages(current->messages);
        current = current->next;
        delete temp;
    }
    chat_list = nullptr;
}

void Messages::deleteMessages(MessageNode *head)
{
    while (head != nullptr)
    {
        MessageNode *temp = head;
        head = head->next;
        delete temp;
    }
}

MessageNode *Messages::getLastMessage(MessageNode *head)
{
    if (head == nullptr)
        return nullptr;

    MessageNode *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current;
}

ChatNode *Messages::findChat(string username)
{
    ChatNode *current = chat_list;
    while (current != nullptr)
    {
        if (current->username == username)
            return current;
        current = current->next;
    }
    return nullptr;
}

void Messages::addMessage(string sender, string receiver, string content)
{
    time_t now = time(0);
    string timestamp = ctime(&now);
    timestamp = timestamp.substr(0, timestamp.length() - 1);

    MessageNode *newMessage = new MessageNode(sender, content, timestamp);

    ChatNode *senderChat = findChat(sender);
    if (senderChat == nullptr)
    {
        senderChat = new ChatNode(sender);
        senderChat->next = chat_list;
        chat_list = senderChat;
    }

    ChatNode *receiverChat = findChat(receiver);
    if (receiverChat == nullptr)
    {
        receiverChat = new ChatNode(receiver);
        receiverChat->next = chat_list;
        chat_list = receiverChat;
    }

    MessageNode *lastMsgSender = getLastMessage(senderChat->messages);
    if (lastMsgSender == nullptr)
    {
        senderChat->messages = newMessage;
    }
    else
    {
        lastMsgSender->next = newMessage;
    }

    MessageNode *receiverCopy = new MessageNode(sender, content, timestamp);
    MessageNode *lastMsgReceiver = getLastMessage(receiverChat->messages);
    if (lastMsgReceiver == nullptr)
    {
        receiverChat->messages = receiverCopy;
    }
    else
    {
        lastMsgReceiver->next = receiverCopy;
    }
}

void Messages::showChat(string username1, string username2)
{
    ChatNode *chat = findChat(username1);
    if (chat == nullptr)
    {
        cout << "No messages found!" << endl;
        return;
    }

    cout << "\n=== Chat History ===" << endl;
    MessageNode *current = chat->messages;
    while (current != nullptr)
    {
        cout << "[" << current->timestamp << "] "
             << ": "
             << current->content << endl;
        current = current->next;
    }
    cout << "===================" << endl;
}

void Messages::showInbox(string username)
{
    ChatNode *userChat = findChat(username);
    if (userChat == nullptr || userChat->messages == nullptr)
    {
        cout << "No messages in inbox!" << endl;
        return;
    }

    cout << "\n=== Message Inbox for " << username << " ===" << endl;
    ChatNode *current = chat_list;
    int count = 1;

    while (current != nullptr)
    {
        if (current->username != username && hasChat(username, current->username))
        {
            // ===== Find last message for preview === //
            MessageNode *lastMsg = getLastMessage(current->messages);
            if (lastMsg != nullptr)
            {
                cout << count++ << ". Chat with " << current->username << endl;
                cout << "   Last message: [" << lastMsg->timestamp << "] "
                     << lastMsg->sender << ": " << lastMsg->content << endl;
            }
        }
        current = current->next;
    }
    cout << "================================" << endl;
}

bool Messages::hasChat(string username1, string username2)
{
    ChatNode *chat1 = findChat(username1);
    if (chat1 == nullptr)
        return false;

    MessageNode *current = chat1->messages;
    while (current != nullptr)
    {
        if (current->sender == username2)
            return true;
        current = current->next;
    }
    return false;
}

void Messages::loadChat(string username1, string username2)
{
    ChatNode *chat1 = findChat(username1);
    if (chat1 == nullptr)
    {
        chat1 = new ChatNode(username1);
        chat1->next = chat_list;
        chat_list = chat1;
    }

    ChatNode *chat2 = findChat(username2);
    if (chat2 == nullptr)
    {
        chat2 = new ChatNode(username2);
        chat2->next = chat_list;
        chat_list = chat2;
    }
}