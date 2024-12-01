#include "requestList.h"
#include <iostream>
using namespace std;

// Constructor
RequestList::RequestList() : front(nullptr), rear(nullptr), receiverCount(0) {}

// Destructor
RequestList::~RequestList()
{
    while (front != nullptr)
    {
        RequestNode *temp = front;
        front = front->next;
        delete temp;
    }
}

// Helper function to delete a request
void RequestList::deleteRequest(RequestNode *prev, RequestNode *current)
{
    if (prev == nullptr)
    { // Deleting the front node
        front = current->next;
    }
    else
    {
        prev->next = current->next;
    }
    if (current == rear)
    { // If it's the rear node
        rear = prev;
    }
    delete current;
}

// Add a new request (one-way connection)
void RequestList::addRequest(const string &username, int senderIndex, int receiverIndex, int **Connection)
{
    if (receiverCount >= MAX_RECEIVERS)
    {
        cout << "Maximum receiver limit reached. Cannot add more requests.\n";
        return;
    }

    RequestNode *newNode = new RequestNode{username, senderIndex, nullptr};
    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    Connection[senderIndex][receiverIndex] = 1;       // One-way connection for the request
    receiverIndices[receiverCount++] = receiverIndex; // Track the receiver index
}

// Show requests and handle accept/reject actions
void RequestList::showRequests(int **Connection)
{
    if (receiverCount == 0)
    {
        cout << "No pending requests.\n";
        return;
    }

    for (int i = 0; i < receiverCount; ++i)
    {
        int receiverIndex = receiverIndices[i];
        RequestNode *temp = front;
        RequestNode *prev = nullptr;

        while (temp != nullptr)
        {
            cout << "Request to: " << receiverIndex
                 << " from: " << temp->friend_username
                 << " (Sender Index: " << temp->senderIndex << ")" << endl;

            // Show menu
            cout << "1. Accept\n2. Reject\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {                                                     // Accept request
                Connection[temp->senderIndex][receiverIndex] = 1; // Ensure the original one-way connection
                Connection[receiverIndex][temp->senderIndex] = 1; // Create the bidirectional connection

                cout << "Request accepted. Bidirectional connection established.\n";

                // Delete the current request
                RequestNode *toDelete = temp;
                temp = temp->next;
                deleteRequest(prev, toDelete);
                break; // Move to next receiver
            }
            else if (choice == 2)
            { // Reject request
                cout << "Request rejected.\n";

                // Delete the current request
                RequestNode *toDelete = temp;
                temp = temp->next;
                deleteRequest(prev, toDelete);
                break; // Move to next receiver
            }
            else
            {
                cout << "Invalid choice. Moving to next request.\n";
                prev = temp;
                temp = temp->next;
            }
        }
    }
    receiverCount = 0;
}
