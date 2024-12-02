#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
using namespace std;

// Helper Validation Functions
bool isValidString(const string &input) {
    for (char c : input) {
        if (!isalpha(c) && c != ' ') return false; // Only letters and spaces allowed
    }
    return true;
}

bool isValidInteger(const string &input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c)) return false; // Only digits allowed
    }
    return true;
}

// User Class Implementation
#include "user.h"

User::User() {
    username = "";
    email = "";
    password = "";
    first_name = "";
    last_name = "";
    DOB = "";
    gender = '\0';
    security_questions[0] = "What is your pet name?";
    security_questions[1] = "What is your favourite color?";
    security_questions[2] = "What is your favourite food?";
    post_stack = PostStack();
    request_list = RequestList();
    friend_list = FriendList();
}

User::User(string username, string email, string password, string first_name, string last_name, string DOB, char gender) {
    this->username = username;
    this->email = email;
    this->password = password;
    this->first_name = first_name;
    this->last_name = last_name;
    this->DOB = DOB;
    this->gender = gender;
    security_questions[0] = "What is your pet name?";
    security_questions[1] = "What is your favourite color?";
    security_questions[2] = "What is your favourite food?";
}

////////////// Setters ///////////////
void User::setpassword(string password) { this->password = password; }
void User::setemail(string email) { this->email = email; }
void User::setfirst_name(string first_name) { this->first_name = first_name; }
void User::setlast_name(string last_name) { this->last_name = last_name; }
void User::setlast_sign_in(string last_sign_in) { this->last_sign_in = last_sign_in; }
void User::setDOB(string DOB) { this->DOB = DOB; }
void User::setgender(char gender) { this->gender = gender; }
void User::setusername(string username) { this->username = username; }

/////////////// Getters /////////////////
string User::getfirst_name() { return this->first_name; }
string User::getlast_name() { return this->last_name; }
string User::getusername() { return this->username; }
string User::getpassword() { return this->password; }
string User::getemail() { return email; }
string User::getDOB() { return DOB; }
string User::getlast_sign_in() { return last_sign_in; }
char User::getgender() { return gender; }

////// Verify security answers ////////////
bool User::verifySecurityAnswers() {
    string arr[3];
    for (int i = 0; i < 3; i++) {
        cout << "\n============================\n";
        cout << "Question " << i + 1 << ": " << security_questions[i] << endl;
        cout << "Your answer: ";
        getline(cin, arr[i]);

        while (!isValidString(arr[i]) || arr[i] != security_answers[i]) {
            cout << "Invalid or incorrect answer! Try again.\n";
            cout << security_questions[i] << endl;
            cout << "Your answer: ";
            getline(cin, arr[i]);
        }
    }
    cout << "\n*** All answers verified successfully! ***\n" << endl;
    return true;
}

//////// Set security answers ////////////
void User::setSecurityAnswers() {
    for (int i = 0; i < 3; i++) {
        string answer;
        cout << "\n============================\n";
        cout << security_questions[i] << endl;
        cout << "Your answer: ";
        getline(cin, answer);
        
        while (!isValidString(answer)) {
            cout << "Invalid input! Please enter a valid answer (letters only): ";
            getline(cin, answer);
        }
        
        security_answers[i] = answer;
    }
    cout << "\n\n*** Security Answers Set Successfully! ***\n" << endl;
}

//////// Function to add a new post //////////
void User::newPost() {
    string post;
    cout << "\n============================\n";
    cout << "Enter your post content:\n";
    getline(cin, post);

    while (!isValidString(post)) {
        cout << "Invalid input! Post content can only contain letters and spaces.\n";
        getline(cin, post);
    }

    time_t now = time(0);
    string posttime = ctime(&now);
    post_stack.newPost(this->username, post, posttime);
    cout << "\n*** Post added successfully at " << posttime << " ***\n" << endl;
}

///////// Get latest post ///////////
void User::getLatestPost() {
    post_stack.peek();
}

////// Friend Request Functions ///////////
void User::sendRequest(string sender, int senderIndex, int receiverIndex, int **Connection) {
    request_list.addRequest(sender, senderIndex, receiverIndex, Connection);
}

int *User::showRequests(int **Connection, int &is_accepted) {
    return request_list.showRequests(Connection, is_accepted);
}

// === Friend Functions === //
void User::addFriend(string f_name) {
    friend_list.addFriend(f_name);
}

void User::displayAllFriends() {
    friend_list.displayAllFriends();
}

void User::clearFriendList() {
    friend_list.clearFriendList();
}

void User::sendNotifications(string type, string username) {
    notification_list.addNotification(type, username);
}

void User::showNotifications() {
    notification_list.showNotifications();
}
