#include "user.h"

User::User(){
    username = "";
    email = "";
    password = "";
    first_name = "";
    last_name = "";
    DOB = "";
    gender = '\0';
    security_questions[0]="What is your pet name?";
    security_questions[1]="What is your favourite color?";
    security_questions[2]="What is your favourite food?";
}

User::User(string username, string email, string password, string first_name, string last_name, string DOB, char gender){
    this->username = username;
    this->email = email;
    this->password = password;
    this->first_name = first_name;
    this->last_name = last_name;
    this->DOB = DOB;
    this->gender = gender;
    security_questions[0]="What is your pet name?";
    security_questions[1]="What is your favourite color?";
    security_questions[2]="What is your favourite food?";   
}