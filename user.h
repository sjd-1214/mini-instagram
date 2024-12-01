#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "post.h"
#include "requestList.h"
using namespace std;

class User
{
private:
    string username;
    string password;
    string email;
    string first_name;
    string last_name;
    char gender;
    string last_sign_in;
    string DOB;
    PostStack post_stack;
    RequestList request_list;
    string security_answers[3];
    string security_questions[3];

public:
    User();
    User(string username, string email, string password, string first_name, string last_name, string DOB, char gender);

    /////////// Setters /////////////
    void setusername(string);
    void setpassword(string);
    void setemail(string);
    void setfirst_name(string);
    void setlast_name(string);
    void setlast_sign_in(string);
    void setgender(char);
    void setDOB(string);
    void newPost();
    void getLatestPost();
    void sendRequest(string sender, int senderIndex, int receiverIndex, int **Connection);
    void showRequests(int **Connection);

    ////// Getters ///////
    string getfirst_name();
    string getlast_name();
    string getlast_sign_in();
    string getusername();
    string getpassword();
    string getemail();
    char getgender();
    string getDOB();

    /////////// Functions /////////////////
    bool verifySecurityAnswers();
    void setSecurityAnswers();
};
