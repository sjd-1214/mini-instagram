#include "requestList.h"
#include <iostream>
using namespace std;

RequestList::RequestList() : front(nullptr), rear(nullptr) {}

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

void RequestList::addRequest(const string &username, int senderIndex, int receiverIndex, int **Connection)
{

    if (senderIndex < 0 || receiverIndex < 0 || !Connection)
    {
        cout << "Invalid parameters provided.\n";
        return;
    }

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

    Connection[senderIndex][receiverIndex] = 1;
    cout << "Request added successfully.\n";
}

void RequestList::displayAllRequests()
{
    if (front == nullptr)
    {
        cout << "No pending requests.\n";
        return;
    }

    cout << "\nPending Requests:\n";
    RequestNode *current = front;
    int count = 1;
    while (current != nullptr)
    {
        cout << count++ << ". Request from: " << current->friend_username << endl;
        current = current->next;
    }
    cout << endl;
}

int *RequestList::showRequests(int **Connection, int &acceptedCount)
{
    if (!Connection || front == nullptr)
    {
        acceptedCount = 0;
        return nullptr;
    }

    displayAllRequests();

    int requestCount = 0;
    RequestNode *temp = front;
    while (temp != nullptr)
    {
        requestCount++;
        temp = temp->next;
    }

    AcceptedRequest *acceptedRequests = new AcceptedRequest[requestCount];
    acceptedCount = 0;

    cout << "Choose processing method:\n";
    cout << "1. Process all requests\n";
    cout << "2. Process by index\n";
    cout << "3. Process one by one\n";

    int method;
    cin >> method;
    cin.ignore();

    switch (method)
    {
    case 1:
    {
        cout << "1. Accept all\n2. Reject all\nChoice: ";
        int choice;
        cin >> choice;

        while (front != nullptr)
        {
            if (choice == 1)
            {
                Connection[front->senderIndex][front->receiverIndex] = 1;
                Connection[front->receiverIndex][front->senderIndex] = 1;
                acceptedRequests[acceptedCount++].senderIndex = front->senderIndex;
            }
            RequestNode *toDelete = front;
            front = front->next;
            delete toDelete;
        }
        rear = nullptr;
        break;
    }

    case 2:
    {
        cout << "Enter request indices to process (0 to finish):\n";
        int *indices = new int[requestCount]; // Dynamically allocated array
        int idx, indexCount = 0;

        while (true)
        {
            cin >> idx;
            if (idx == 0)
                break;
            if (idx > 0 && idx <= requestCount)
            {
                indices[indexCount++] = idx - 1;
            }
        }

        cout << "1. Accept selected\n2. Reject selected\nChoice: ";
        int choice;
        cin >> choice;

        for (int i = 0; i < indexCount; i++)
        {
            RequestNode *current = front;
            RequestNode *prev = nullptr;
            int currentIdx = 0;

            while (current && currentIdx < indices[i])
            {
                prev = current;
                current = current->next;
                currentIdx++;
            }

            if (current)
            {
                if (choice == 1)
                {
                    Connection[current->senderIndex][current->receiverIndex] = 1;
                    Connection[current->receiverIndex][current->senderIndex] = 1;
                    acceptedRequests[acceptedCount++].senderIndex = current->senderIndex;
                }

                if (prev)
                    prev->next = current->next;
                else
                    front = current->next;

                if (current == rear)
                    rear = prev;
                delete current;
            }
        }

        delete[] indices; // Free dynamically allocated memory
        break;
    }

    case 3:
    {
        while (front != nullptr)
        {
            bool currentRequestAccepted = false;
            cout << "Processing request from: " << front->friend_username << endl;
            cout << "1. Accept\n2. Reject\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                Connection[front->senderIndex][front->receiverIndex] = 1;
                Connection[front->receiverIndex][front->senderIndex] = 1;
                acceptedRequests[acceptedCount++].senderIndex = front->senderIndex;
            }

            RequestNode *toDelete = front;
            front = front->next;
            if (front == nullptr)
                rear = nullptr;
            delete toDelete;

            if (front != nullptr)
            {
                cout << "Process next? (y/n): ";
                char cont;
                cin >> cont;
                if (tolower(cont) != 'y')
                    break;
            }
        }
        break;
    }
    }

    int *senderIndices = new int[acceptedCount];
    for (int i = 0; i < acceptedCount; i++)
    {
        senderIndices[i] = acceptedRequests[i].senderIndex;
    }

    delete[] acceptedRequests;
    return senderIndices;
}
