#include "friendList.h"
// Constructor for FriendList
FriendList::FriendList() : top(nullptr) {}

// Get the top node (useful for debugging or further operations)
FriendNode *FriendList::getTop() const
{
    return top;
}

/// @brief Add a new friend to the list
/// @param f_name The friend's username
void FriendList::addFriend(string f_name)
{
    if (f_name.empty())
    {
        cout << "Error: Friend username cannot be empty!" << endl;
        return;
    }

    FriendNode *newNode = new FriendNode(f_name);
    newNode->next = top;
    top = newNode;
    cout<<endl;
}

/// @brief Display all friends in the list
void FriendList::displayAllFriends()
{
    if (top == nullptr)
    {
        cout << "Friend list is empty!" << endl;
        return;
    }

    FriendNode *current = top;
    int count = 1;

    while (current != nullptr)
    {
        cout << count++ << ". " << current->friend_username << endl;
        current = current->next;
    }
    cout << endl;
}

/// @brief Clear the entire friend list
void FriendList::clearFriendList()
{
    FriendNode *current = top;
    FriendNode *temp;

    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
    top = nullptr; // Mark the list as empty
}

// Destructor to ensure memory cleanup
FriendList::~FriendList()
{
    clearFriendList();
}
