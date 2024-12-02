#include <iostream>
using namespace std;
class NewsFeedNode
{
public:
    string post;
    NewsFeedNode *next;
    NewsFeedNode(string post) : post(post), next(nullptr) {}
};
class NewsFeed
{
private:
    NewsFeedNode *top;

public:
    NewsFeed();
    void addPost(string post);
    void displayAllPosts();
    ~NewsFeed();
};