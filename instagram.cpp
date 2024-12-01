#include "instagram.h"
///======= Show Menu ======= ///
void Instagram::showMenu()
{
    int choice;
    cout << "1. Create Account" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        createAccount();
        break;
    case 2:
        logIn();
        break;
    case 3:
        cout << "Goodbye!" << endl;
        break;
    }
}
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
    user[user_count] = *newUser;
    user_count++;
    cout << "Yahoooo You Made it!! " << endl;
    cout << "Welcome To Instagram" << endl;
}

///======= Search =======///
bool Instagram::search(string username)
{
    BSTNode *userNode = bst->search(username);
    return userNode != nullptr;
}
//////////////////////////////////////////////////////

///======= Log In ======= ///
BSTNode *activeuser;
void Insta::signin()
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
        home(username);
    }
    else
    {
        cout << "Invalid username or password" << endl;
    }
}
