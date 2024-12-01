#pragma once
#include <iostream>
#include <string>
#include "validations.h"
#include "user.h"

using namespace std;

class Instagram
{
    User *user;

public:
    void showMenu();
    void createAccount();
    void logIn();
    bool search(string username);
};