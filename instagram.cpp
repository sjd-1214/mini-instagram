#include "instagram.h"
///======== Constructor ===========///
Instagram::Instagram()
{
    user_count = 0;
    bst = new BST();
    connections = nullptr;
    user = nullptr;
    activeuser = nullptr;
}
//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////
///======= Update Connections =======///
int **Instagram::updateConnections()
{
    if (user_count <= 0)
        return nullptr;

    int **temp_connections = new int *[user_count];
    for (int i = 0; i < user_count; i++)
    {
        temp_connections[i] = new int[user_count];
        for (int j = 0; j < user_count; j++)
        {
            temp_connections[i][j] = 0;
        }
    }

    if (connections != nullptr)
    {
        int oldSize = user_count - 1;
        for (int i = 0; i < oldSize; i++)
        {
            for (int j = 0; j < oldSize; j++)
            {
                temp_connections[i][j] = connections[i][j];
            }
        }

        for (int i = 0; i < oldSize; i++)
        {
            delete[] connections[i];
        }
        delete[] connections;
    }

    return temp_connections;
}
//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////
///======= Show Menu ======= ///
void Instagram::showMenu()
{
    int choice;
    cout << "1. Create Account" << endl;
    cout << "2. Log In" << endl;
    cout << "3. show connections" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
    }
    cin.ignore();
    switch (choice)
    {
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
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///======= Create Account ======= ///
void Instagram::createAccount()
{
    cout << "Enter the following details to Create New Account: " << endl;
    ///////////////////////////// Username //////////////////////////////////
    string username;
    cout << "Enter username: ";
    getline(cin, username);

    while (!validateusername(username) || search(username))
    {
        cout << "Username Is Already Registred!! OR Invalid Username " << endl;
        cout << "Enter username: ";
        getline(cin, username);
    }

    ///////////////////////////// Email //////////////////////////////////
    string email;
    cout << "Enter email: ";
    getline(cin, email);

    while (!validate_email(email))
    {
        cout << "Invalid email. Please enter a valid email: ";
        getline(cin, email);
    }
    ///////////////////////////// Password //////////////////////////////////
    string password;
    cout << "Enter password: ";
    getline(cin, password);

    while (!validate_strong_password(password))
    {
        cout << "Invalid password. Please enter a strong password: ";
        getline(cin, password);
    }

    cout << "Sign up successfull!!" << endl;
    cout << "Let' Setup Your Profile" << endl;
    ///================ First Name ==================///
    string first_name;
    cout << "Enter First Name: ";
    getline(cin, first_name);
    ///================ Last Name ===============///
    string last_name;
    cout << "Enter Last Name: ";
    getline(cin, last_name);
    ///================== DOB =================///
    string DOB;
    cout << "Enter DOB (DD-MM-YYY): ";
    getline(cin, DOB);
    while (!validate_DOB(DOB))
    {
        cout << "Invalid DOB. Please enter a valid DOB: ";
        getline(cin, DOB);
    }
    ///================= Gender ================///
    int choice;
    cout << "1. Male" << endl;
    cout << "2. Female" << endl;
    cout << "Choose Your Gender :" << endl;
    cin >> choice;
    char gender;
    while (choice != 1 && choice != 2)
    {
        cout << "Invalid choice. Please enter a valid choice: ";
        cin >> choice;
    }
    if (choice == 1)
    {
        gender = 'M';
    }
    else if (choice == 2)
    {
        gender = 'F';
    }
    cin.ignore();
    User *newUser = new User(username, email, password, first_name, last_name, DOB, gender);
    cout << "Let's Secure Your Account" << endl;
    newUser->setSecurityAnswers();
    bst->insert(newUser);
    user_count++;
    int **new_connections = updateConnections();
    if (new_connections != nullptr)
    {
        connections = new_connections;
    }
    cout << "Yahoooo You Made it!! " << endl;
    cout << "Welcome To Instagram" << endl;
    setActiveUser(bst->search(username));
    home(username);
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// ======= Search ======= ///
bool Instagram::search(string username)
{
    BSTNode *userNode = bst->search(username);
    return userNode != nullptr;
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///======= Log In ======= ///
void Instagram::logIn()
{
    string username;
    string password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    bool is_valid = false;

    BSTNode *userNode = bst->search(username);

    if (userNode != nullptr && userNode->user->getpassword() == password)
    {
        activeuser = userNode;
        time_t now = time(0);
        userNode->user->setlast_sign_in(ctime(&now));
        is_valid = true;
    }

    if (is_valid)
    {
        cout << "Login successfull!!" << endl;
        setActiveUser(bst->search(username));
        home(username);
    }
    else
    {
        cout << "Invalid username or password" << endl;
        showMenu();
    }
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/////////// Reset Password //////////
void Instagram::resetpassword()
{
    if (activeuser->user->verifySecurityAnswers())
    {
        string password;
        cout << "Enter new password: ";
        getline(cin, password);
        while (!validate_strong_password(password) || password == activeuser->user->getpassword())
        {
            cout << "Please enter a new and strong password: ";
            getline(cin, password);
        }
        activeuser->user->setpassword(password);
        cout << "Password updated successfully." << endl;
        cout << "Press 1 to go back to home" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            home(activeuser->user->getusername());
        }
    }
    else
    {
        cout << "Invalid Security Answers" << endl;
    }
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///======= search Profile ======= ///
void Instagram::searchProfile()
{
    string username;
    cout << "Enter username: ";
    getline(cin, username);
    int choice;
    // Search for the user in the BST
    BSTNode *userNode = bst->search(username);
    if (userNode != nullptr)
    {
        // User found
        cout << "+----------------------- User Profile--------------------------+" << endl;
        cout << "First Name: " << userNode->user->getfirst_name() << endl;
        cout << "Last Name: " << userNode->user->getlast_name() << endl;
        cout << "Username: " << userNode->user->getusername() << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "1. Add Friend" << endl;
        cout << "2. Back" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            addfriend(userNode->user->getusername());
        }
        else
        {
            home(activeuser->user->getusername());
        }
    }
    else
    {
        cout << "User Not Found!!" << endl;
        home(activeuser->user->getusername());
    }
}
/// === Set Active User === ///
void Instagram::setActiveUser(BSTNode *activeuser)
{
    this->activeuser = activeuser;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///================================ Sign Out=============================== ///
void Instagram::signout()
{
    cout << "You have been signed out" << endl;
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