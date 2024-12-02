#include "requestList.h"
#include <iostream>
using namespace std;

// Constructor
RequestList::RequestList() : front(nullptr), rear(nullptr) {}

// Destructor
RequestList::~RequestList()
{
    while (front != nullptr)
    {
        RequestNode *temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

// Add a new request (one-way connection)
void RequestList::addRequest(const string &username, int senderIndex, int receiverIndex, int **Connection)
{
    // Validate indices
    if (senderIndex < 0 || receiverIndex < 0 || !Connection)
    {
        cout << "Invalid parameters provided.\n";
        return;
    }

    // Create new node with all three pieces of information
    RequestNode *newNode = new RequestNode{
        username,
        senderIndex,
        receiverIndex,
        nullptr};

    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    Connection[senderIndex][receiverIndex] = 1; // One-way connection for the request
    cout << "Request added successfully.\n";
}

// Show all pending requests
void RequestList::displayAllRequests()
{
    if (front == nullptr)
    {
        cout << "No pending requests.\n";
        return;
    }

    cout << "\nAll Pending Requests:\n";
    RequestNode *current = front;
    int count = 1;

    while (current != nullptr)
    {
        cout << count++ << ". Request to: " << current->receiverIndex
             << " from: " << current->friend_username
             << " (Sender Index: " << current->senderIndex << ")\n";
        current = current->next;
    }
    cout << endl;
}

void RequestList::processTopRequest(int **Connection)
{
    if (!Connection)
    {
        cout << "Invalid connection matrix.\n";
        return;
    }

    if (front == nullptr)
    {
        cout << "No pending requests.\n";
        return;
    }

    displayAllRequests();

    cout << "Processing topmost request:\n";
    cout << "Request to: " << front->receiverIndex
         << " from: " << front->friend_username
         << " (Sender Index: " << front->senderIndex << ")\n";

    bool validChoice = false;
    int choice;

    do
    {
        cout << "1. Accept\n2. Reject\nChoice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }
        validChoice = (choice == 1 || choice == 2);
        if (!validChoice)
        {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    } while (!validChoice);

    if (choice == 1)
    {
        if (front->senderIndex >= 0 && front->receiverIndex >= 0)
        {
            Connection[front->senderIndex][front->receiverIndex] = 1;
            Connection[front->receiverIndex][front->senderIndex] = 1;
            cout << "Request accepted. Bidirectional connection established.\n";

            // Debug output to verify matrix update
            cout << "Debug - Connection matrix values:" << endl;
            cout << "Connection[" << front->senderIndex << "][" << front->receiverIndex << "] = "
                 << Connection[front->senderIndex][front->receiverIndex] << endl;
            cout << "Connection[" << front->receiverIndex << "][" << front->senderIndex << "] = "
                 << Connection[front->receiverIndex][front->senderIndex] << endl;
        }
        else
        {
            cout << "Error: Invalid indices in connection request.\n";
        }
    }
    else
    {
        cout << "Request rejected.\n";
    }

    RequestNode *temp = front;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
}

// Show requests and handle accept/reject actions one at a time
void RequestList::showRequests(int **Connection)
{
    if (!Connection)
    {
        cout << "Invalid connection matrix.\n";
        return;
    }

    while (front != nullptr)
    {
        processTopRequest(Connection);
        cout << "\nRemaining requests:\n";
        displayAllRequests();

        if (front != nullptr)
        {
            char continue_choice;
            cout << "Process next request? (y/n): ";
            cin >> continue_choice;
            if (tolower(continue_choice) != 'y')
            {
                break;
            }
        }
    }
}