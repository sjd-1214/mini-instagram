#include "messages.h"

// MessageNode Implementation
MessageNode::MessageNode(string message) {
    next = prev = nullptr;
    this->message = message;
}

string MessageNode::getMessage() const {
    return message;
}

// MessageStack Implementation
MessageStack::MessageStack() {
    top = nullptr;
    recipient_name = "";
}

MessageStack::MessageStack(string friend_username) {
    top = nullptr;
    recipient_name = friend_username;
}

string MessageStack::getName() const {
    return recipient_name;
}

void MessageStack::setName(string name) {
    recipient_name = name;
}

MessageNode* MessageStack::getTop() const {
    return top;
}

bool MessageStack::add_message() {
    string message;
    cout << "Enter Your Message: ";
    getline(cin, message);

    MessageNode* new_message = new MessageNode(message);

    if (top == nullptr) {
        top = new_message;
    } else {
        new_message->prev = top;
        top->next = new_message;
        top = new_message;
    }
    return true;
}

// ChatNode Implementation
ChatNode::ChatNode(string username) {
    next = nullptr;
    prev = nullptr;
    message_stack = new MessageStack(username);
}

// ChatStack Implementation
ChatStack::ChatStack() {
    top = nullptr;
}

bool ChatStack::newChat(string username) {
    ChatNode* new_chat = new ChatNode(username);

    if (top == nullptr) {
        top = new_chat;
    } else {
        new_chat->prev = top;
        top->next = new_chat;
        top = new_chat;
    }
    return true;
}

ChatNode* ChatStack::getTop() const {
    return top;
}

// Messages Implementation
Messages::Messages() {
    chat = new ChatStack();
}

void Messages::newChat(string username) {
    chat->newChat(username);
}

bool Messages::send() {
    string recipient;
    cout << "To whom you want to send the message: ";
    getline(cin, recipient);

    bool is_found = false;
    ChatNode* current = chat->getTop();

    while (current != nullptr) {
        if (current->message_stack->getName() == recipient) {
            is_found = true;
            break;
        }
        current = current->prev;
    }

    if (!is_found) {
        cout << "User NOT FOUND\n";
        return false;
    }

    if (current->message_stack->add_message()) {
        cout << "Message SENT\n";
        return true;
    }

    return false;
}

bool Messages::display() {
    string username;
    cout << "Enter the username of the recipient: ";
    getline(cin, username);

    bool is_found = false;
    ChatNode* current = chat->getTop();

    while (current != nullptr) {
        if (current->message_stack->getName() == username) {
            is_found = true;
            break;
        }
        current = current->prev;
    }

    if (!is_found) {
        cout << "User NOT FOUND\n";
        return false;
    }

    reversePrint(current->message_stack);
    return true;
}

// Helper Function: reversePrint
void reversePrint(MessageStack* x) {
    MessageNode* current = x->getTop();

    while (current != nullptr && current->prev != nullptr) {
        current = current->prev;
    }

    while (current != nullptr) {
        cout << current->getMessage() << endl << endl;
        current = current->next;
    }
}