#include "user.h"
#include <iostream>
using namespace std;

class BSTNode
{
public:
    User *user;
    BSTNode *left;
    BSTNode *right;

    BSTNode(User *user) : user(user), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    BSTNode *root;
    void insert(BSTNode *&node, User *user)
    {
        if (node == nullptr)
        {
            node = new BSTNode(user);
        }
        else if (user->getusername() < node->user->getusername())
        {
            insert(node->left, user);
        }
        else if (user->getusername() > node->user->getusername())
        {
            insert(node->right, user);
        }
    }

    BSTNode *search(BSTNode *node, const string &username)
    {
        if (node == nullptr)
            return nullptr;
        if (node->user->getusername() == username)
            return node;
        if (username < node->user->getusername())
            return search(node->left, username);
        return search(node->right, username);
    }

public:
    BST() : root(nullptr) {}

    void insert(User *user)
    {
        insert(root, user);
    }

    BSTNode *search(const string &username)
    {
        return search(root, username);
    }
    BSTNode *getRoot()
    {
        return root;
    }
};
