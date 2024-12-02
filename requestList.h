#include <string>
using namespace std;

const int MAX_RECEIVERS = 100; // Maximum number of receivers

struct RequestNode
{
    string friend_username;
    int senderIndex;
    int receiverIndex;
    RequestNode *next;
};

class RequestList
{
private:
    RequestNode *front;
    RequestNode *rear;
    int receiverIndices[MAX_RECEIVERS];
    int receiverCount;
    void deleteRequest(RequestNode *prev, RequestNode *current);

public:
    RequestList();
    ~RequestList();
    void displayAllRequests();
    void addRequest(const string &username, int senderIndex, int receiverIndex, int **Connection);
    void processTopRequest(int **Connection);
    void showRequests(int **Connection);
};
