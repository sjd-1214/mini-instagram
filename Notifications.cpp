#include "Notifications.h"
#include <iostream>
using namespace std;
NotificationList::NotificationList() : top(nullptr) {}
void NotificationList::addNotification(string notification)
{
    NotificationNode *newNode = new NotificationNode(notification);
    newNode->next = top;
    top = newNode;
    cout << "Notification added successfully!" << endl;
}