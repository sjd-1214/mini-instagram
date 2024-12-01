#pragma once
#include "user.h"
#include <iostream>
using namespace std;

class BSTNode
{
public:
    User *user;     // Pointer to User object
    BSTNode *left;  // Left child node
    BSTNode *right; // Right child node

    BSTNode(User *user);
};

class BST
{
private:
    BSTNode *root;
    void insert(BSTNode *&node, User *user);
    BSTNode *search(BSTNode *node, const string &username);

public:
    BST();
    void insert(User *user);
    BSTNode *search(const string &username);
    BSTNode *getRoot();
};
