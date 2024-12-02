#pragma once
#include <iostream>
#include <string>
#include "validations.h"
#include "user.h"
#include "bst.h"

using namespace std;

class Instagram
{
    User *user;
    int **connections;
    BST *bst;
    int user_count;
    BSTNode *activeuser;

    int findIndexInBST(BSTNode *node, const string &username, int &current_index)
    {
        if (node == nullptr)
        {
            return -1;
        }
        int leftResult = findIndexInBST(node->left, username, current_index);
        if (leftResult != -1)
        {
            return leftResult;
        }
        if (node->user->getusername() == username)
        {
            return current_index;
        }
        current_index++;

        return findIndexInBST(node->right, username, current_index);
    }

public:
    Instagram();
    void showMenu();
    void createAccount();
    void logIn();
    void searchProfile();
    void resetpassword();
    void setActiveUser(BSTNode *activeuser);
    void addfriend(string username);
    int getuserindex(string username);
    void showConnections();
    bool search(string username);
    int **updateConnections();
    void signout();
    void home(string username);
};