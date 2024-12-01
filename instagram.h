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

public:
    Instagram();
    void showMenu();
    void createAccount();
    void logIn();
    void searchProfile();
    void resetpassword();
    void setActiveUser(BSTNode *activeuser);
    bool search(string username);
    int **updateConnections();
    void signout();
    void home(string username);
};