#include <iostream>
using namespace std;
class NotificationNode
{
private:
    string notification;
    NotificationNode *next;

public:
    NotificationNode(string notification) : notification(notification), next(nullptr) {}
    friend class NotificationList;
};
class NotificationList
{
private:
    NotificationNode *top;

public:
    NotificationList();
    void addNotification(string notification);
};