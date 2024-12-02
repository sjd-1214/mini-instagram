#include "instagram.h"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

// Helper Functions for Validation
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

// Constructor
Instagram::Instagram() {
    user_count = 0;
    bst = new BST();
    connections = nullptr;
    user = nullptr;
    activeuser = nullptr;
}

// Update Connections
int **Instagram::updateConnections() {
    if (user_count <= 0)
        return nullptr;

    int **temp_connections = new int *[user_count];
    for (int i = 0; i < user_count; i++) {
        temp_connections[i] = new int[user_count];
        for (int j = 0; j < user_count; j++) {
            temp_connections[i][j] = 0;
        }
    }

    if (connections != nullptr) {
        int oldSize = user_count - 1;
        for (int i = 0; i < oldSize; i++) {
            for (int j = 0; j < oldSize; j++) {
                temp_connections[i][j] = connections[i][j];
            }
        }

        for (int i = 0; i < oldSize; i++) {
            delete[] connections[i];
        }
        delete[] connections;
    }

    return temp_connections;
}

// Show Menu
void Instagram::showMenu() {
    string choiceStr;
    int choice;

    cout << "\n========== Instagram Menu ==========\n";
    cout << "1. Create Account\n";
    cout << "2. Log In\n";
    cout << "3. Show Connections\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";

    getline(cin, choiceStr);

    while (!isValidInteger(choiceStr) || stoi(choiceStr) < 1 || stoi(choiceStr) > 4) {
        cout << "Invalid input! Please enter a valid option (1-4): ";
        getline(cin, choiceStr);
    }
    choice = stoi(choiceStr);

    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            logIn();
            break;
        case 3:
            // showConnections();
            showMenu();
            break;
        case 4:
            cout << "Goodbye!" << endl;
            break;
    }
}

// Create Account
void Instagram::createAccount() {
    cout << "\n===== Create New Account =====\n";
    string username, email, password, first_name, last_name, DOB, choiceStr;
    char gender;

    // Username
    cout << "Enter username: ";
    getline(cin, username);
    while (!isValidString(username) || search(username)) {
        cout << "Invalid or already registered username! Please try again: ";
        getline(cin, username);
    }

    // Email
    cout << "Enter email: ";
    getline(cin, email);
    while (!validate_email(email)) {
        cout << "Invalid email! Please try again: ";
        getline(cin, email);
    }

    // Password
    cout << "Enter password: ";
    getline(cin, password);
    while (!validate_strong_password(password)) {
        cout << "Invalid password! Please try again: ";
        getline(cin, password);
    }

    // First Name
    cout << "Enter first name: ";
    getline(cin, first_name);
    while (!isValidString(first_name)) {
        cout << "Invalid input! Name can only contain letters and spaces. Try again: ";
        getline(cin, first_name);
    }

    // Last Name
    cout << "Enter last name: ";
    getline(cin, last_name);
    while (!isValidString(last_name)) {
        cout << "Invalid input! Name can only contain letters and spaces. Try again: ";
        getline(cin, last_name);
    }

    // Date of Birth
    cout << "Enter DOB (DD-MM-YYYY): ";
    getline(cin, DOB);
    while (!validate_DOB(DOB)) {
        cout << "Invalid DOB format! Please try again: ";
        getline(cin, DOB);
    }

    // Gender
    cout << "1. Male\n2. Female\nChoose your gender: ";
    getline(cin, choiceStr);
    while (!isValidInteger(choiceStr) || (stoi(choiceStr) != 1 && stoi(choiceStr) != 2)) {
        cout << "Invalid choice! Please enter 1 for Male or 2 for Female: ";
        getline(cin, choiceStr);
    }
    gender = (stoi(choiceStr) == 1) ? 'M' : 'F';

    // Create User
    User *newUser = new User(username, email, password, first_name, last_name, DOB, gender);
    cout << "\nSetting up your security questions...\n";
    newUser->setSecurityAnswers();
    bst->insert(newUser);
    user_count++;

    int **new_connections = updateConnections();
    if (new_connections != nullptr) {
        connections = new_connections;
    }
    cout << "\nWelcome to Instagram, " << username << "!\n";
    setActiveUser(bst->search(username));
    home(username);
}

// Search
bool Instagram::search(string username) {
    BSTNode *userNode = bst->search(username);
    return userNode != nullptr;
}


///======= Log In ======= ///
void Instagram::logIn() {
    string username, password, choiceStr;
    bool is_valid = false;

    // Prompt for username
    cout << "\n===== Log In =====\n";
    cout << "Enter username: ";
    getline(cin, username);

    // Prompt for password
    cout << "Enter password: ";
    getline(cin, password);

    BSTNode *userNode = bst->search(username);

    // Validate login credentials
    if (userNode != nullptr && userNode->user->getpassword() == password) {
        activeuser = userNode;
        time_t now = time(0);
        userNode->user->setlast_sign_in(ctime(&now));
        is_valid = true;
    }

    // Login success or failure
    if (is_valid) {
        cout << "Login successful!!\n";
        setActiveUser(bst->search(username));
        home(username);
    } else {
        cout << "Invalid username or password. Please try again.\n";
        showMenu();
    }
}

/// ======= Reset Password ======= ///
void Instagram::resetpassword() {
    if (activeuser->user->verifySecurityAnswers()) {
        string password;
        cout << "\nEnter new password: ";
        getline(cin, password);

        // Validate the new password
        while (!validate_strong_password(password) || password == activeuser->user->getpassword()) {
            cout << "Password must be strong and different from the previous one. Try again: ";
            getline(cin, password);
        }

        // Set the new password
        activeuser->user->setpassword(password);
        cout << "Password updated successfully.\n";

        // Option to go back to home
        cout << "Press 1 to go back to home: ";
        int choice;
        string choiceStr;
        getline(cin, choiceStr);

        // Validate choice
        while (!isValidInteger(choiceStr) || stoi(choiceStr) != 1) {
            cout << "Invalid input. Please enter '1' to return to home: ";
            getline(cin, choiceStr);
        }

        home(activeuser->user->getusername());
    } else {
        cout << "Invalid security answers. Please try again.\n";
    }
}

///======= Search Profile ======= ///
void Instagram::searchProfile() {
    string username;
    cout << "\n===== Search Profile =====\n";
    cout << "Enter username: ";
    getline(cin, username);

    int choice;
    BSTNode *userNode = bst->search(username);

    // Check if user exists
    if (userNode != nullptr) {
        // Display profile information
        cout << "+----------------------- User Profile -----------------------+\n";
        cout << "First Name: " << userNode->user->getfirst_name() << endl;
        cout << "Last Name: " << userNode->user->getlast_name() << endl;
        cout << "Username: " << userNode->user->getusername() << endl;
        cout << "+-----------------------------------------------------------+\n";
        cout << "1. Add Friend\n";
        cout << "2. Back\n";
        cout << "Enter Your Choice: ";
        string choiceStr;
        getline(cin, choiceStr);

        // Validate choice input
        while (!isValidInteger(choiceStr) || (stoi(choiceStr) != 1 && stoi(choiceStr) != 2)) {
            cout << "Invalid choice! Please enter 1 to add friend or 2 to go back: ";
            getline(cin, choiceStr);
        }

        choice = stoi(choiceStr);

        if (choice == 1) {
            addfriend(userNode->user->getusername());
        } else {
            home(activeuser->user->getusername());
        }
    } else {
        cout << "User not found!\n";
        home(activeuser->user->getusername());
    }
}

/// === Set Active User === ///
void Instagram::setActiveUser(BSTNode *activeuser) {
    this->activeuser = activeuser;
}

///======================== Sign Out ========================///
void Instagram::signout() {
    cout << "You have been signed out.\n";
    showMenu();
}

///================================ Home ================================= ///
void Instagram::home(string username)
{
    int choice;
    string post;
    string date;
    cout << "welcome " << username << endl;
    cout << "1. Search User" << endl;
    cout << "2. Sign Out" << endl;
    cout << "3. New Post" << endl;
    cout << "4. Show Recent Post" << endl;
    cout << "5. Reset Password" << endl;
    cout << "6. Show Requests" << endl;
    cout << "7. Show Friend List" << endl;
    cout << "8. Show Suggestions" << endl;
    cout << "9. Show Notifications" << endl;
    cout << "Enter Choice:";
    cin >> choice;
    cin.ignore();
    if (choice == 1)
    {
        searchProfile();
    }
    else if (choice == 2)
    {
        signout();
    }
    else if (choice == 3)
    {
        activeuser->user->newPost();

        home(username);
    }
    else if (choice == 4)
    {
        activeuser->user->getLatestPost();
    }
    else if (choice == 5)
    {
        resetpassword();
    }
    else if (choice == 6)
    {
        int acceptedCount = 0;
        int *accepted_indices = activeuser->user->showRequests(connections, acceptedCount);

        if (accepted_indices != nullptr)
        {
            for (int i = 0; i < acceptedCount; i++)
            {
                string sender_username = getUsernameByIndex(accepted_indices[i]);
                bst->search(sender_username)->user->sendNotifications("accepted", activeuser->user->getusername());
                activeuser->user->addFriend(sender_username);
            }
            delete[] accepted_indices;
        }

        cout << "Press 1 to go back to home" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            home(activeuser->user->getusername());
        }
    }
    else if (choice == 7)
    {
        showFriendList();
        cout << "Press 1 to go back to home" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            home(activeuser->user->getusername());
        }
    }
    else if (choice == 8)
    {
        showSuggestion();
        cout << "Press 1 to go back to home" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            home(activeuser->user->getusername());
        }
    }
    else if (choice == 9)
    {
        showNotifiactions();
        home(activeuser->user->getusername());
    }
    else
    {
        cout << "Invalid choice" << endl;
        home(activeuser->user->getusername());
    }
}
//// ===== get user index ======== //////
int Instagram::getuserindex(string username)
{
    int current_index = 0;
    BSTNode *node = bst->getRoot();
    return findIndexInBST(node, username, current_index);
}

//// ========= add friend ======== ///////////
void Instagram::addfriend(string username)
{

    BSTNode *userNode = bst->search(username);
    if (userNode == nullptr)
    {
        cout << "User not found" << endl;
        return;
    }

    if (username == activeuser->user->getusername())
    {
        cout << "Cannot send request to yourself!" << endl;
        return;
    }

    int senderIndex = getuserindex(activeuser->user->getusername());
    int receiverIndex = getuserindex(username);

    if (connections[senderIndex][receiverIndex] == 1 || connections[receiverIndex][senderIndex] == 1)
    {
        cout << "Connection already exists!" << endl;
        home(activeuser->user->getusername());
    }

    userNode->user->sendRequest(activeuser->user->getusername(),
                                senderIndex, receiverIndex, connections);
    userNode->user->sendNotifications("request", activeuser->user->getusername());
    activeuser->user->addFriend(username);

    home(activeuser->user->getusername());
}

// void Instagram::showConnections()
// {
//     if (connections == nullptr)
//     {
//         cout << "Error: Connection matrix not initialized" << endl;
//         return;
//     }

//     for (int i = 0; i < user_count; i++)
//     {
//         for (int j = 0; j < user_count; j++)
//         {
//             cout << connections[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

void Instagram::showFriendList()
{
    if (activeuser == nullptr)
    {
        cout << "Error: No active user" << endl;
        return;
    }

    cout << "Friend List for " << activeuser->user->getusername() << ":" << endl;
    activeuser->user->displayAllFriends();
}

void Instagram::showSuggestion()
{
    if (connections == nullptr || activeuser == nullptr)
    {
        cout << "No Suggestions" << endl;
        return;
    }

    int active_user_index = getuserindex(activeuser->user->getusername());
    if (active_user_index == -1)
    {
        cout << "Error: Active user not found in the system" << endl;
        return;
    }

    int *direct_friends = new int[user_count]();
    int *suggestions = new int[user_count]();
    double *suggestion_scores = new double[user_count]();
    bool *visited = new bool[user_count]();
    int direct_friend_count = 0;
    int suggestion_count = 0;

    for (int i = 0; i < user_count; i++)
    {
        if (connections[active_user_index][i] == 1)
        {
            direct_friends[direct_friend_count++] = i;
            visited[i] = true;
        }
    }

    visited[active_user_index] = true;

    int *queue = new int[user_count]();
    int front = 0, rear = 0;

    for (int i = 0; i < direct_friend_count; i++)
    {
        queue[rear++] = direct_friends[i];
    }

    while (front < rear)
    {
        int current = queue[front++];

        for (int i = 0; i < user_count; i++)
        {
            if (connections[current][i] == 1 && !visited[i])
            {
                visited[i] = true;
                suggestions[suggestion_count++] = i;
                double score = 0.0;

                int mutual_friends = 0;
                for (int j = 0; j < direct_friend_count; j++)
                {
                    if (connections[i][direct_friends[j]] == 1)
                    {
                        mutual_friends++;
                    }
                }
                score += 0.5 * (mutual_friends / (double)direct_friend_count);

                BSTNode *suggestion_user = bst->search(getUsernameByIndex(i));
                if (suggestion_user != nullptr && suggestion_user->user != nullptr)
                {
                    score += 0.3;
                }
                score += 0.2 * (1.0 / (front + 1));

                suggestion_scores[i] = score * 100;
            }
        }
    }

    for (int i = 0; i < suggestion_count - 1; i++)
    {
        for (int j = 0; j < suggestion_count - i - 1; j++)
        {
            if (suggestion_scores[suggestions[j]] < suggestion_scores[suggestions[j + 1]])
            {
                int temp_suggestion = suggestions[j];
                suggestions[j] = suggestions[j + 1];
                suggestions[j + 1] = temp_suggestion;
            }
        }
    }

    if (suggestion_count == 0)
    {
        cout << "No friend suggestions available!" << endl;
    }
    else
    {
        cout << "Friend Suggestions:" << endl;
        for (int i = 0; i < suggestion_count; i++)
        {
            BSTNode *suggestion_user = bst->search(getUsernameByIndex(suggestions[i]));
            if (suggestion_user != nullptr && suggestion_user->user != nullptr)
            {
                cout << i + 1 << ". "
                     << suggestion_user->user->getusername()
                     << " (Relevance Score: " << fixed << setprecision(2)
                     << suggestion_scores[suggestions[i]] << "%)" << endl;
            }
        }

        cout << "\nEnter the number of the user to send a friend request (0 to go back): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= suggestion_count)
        {
            BSTNode *selected_user = bst->search(getUsernameByIndex(suggestions[choice - 1]));
            if (selected_user != nullptr && selected_user->user != nullptr)
            {
                addfriend(selected_user->user->getusername());
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice. Returning to home menu." << endl;
        }
    }

    delete[] direct_friends;
    delete[] suggestions;
    delete[] suggestion_scores;
    delete[] visited;
    delete[] queue;
}

string Instagram::getUsernameByIndex(int index)
{
    int current_index = 0;
    BSTNode *node = findUserNodeByIndex(bst->getRoot(), index, current_index);
    if (node != nullptr && node->user != nullptr)
    {
        return node->user->getusername();
    }
    return "";
}

BSTNode *Instagram::findUserNodeByIndex(BSTNode *root, int target_index, int &current_index)
{
    if (root == nullptr)
        return nullptr;

    BSTNode *left_result = findUserNodeByIndex(root->left, target_index, current_index);
    if (left_result != nullptr)
        return left_result;

    if (current_index == target_index)
        return root;
    current_index++;

    return findUserNodeByIndex(root->right, target_index, current_index);
}
void Instagram::showNotifiactions()
{
    activeuser->user->showNotifications();
}