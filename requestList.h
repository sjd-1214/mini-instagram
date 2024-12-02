#include <string>
using namespace std;
struct RequestNode
{
    string friend_username;
    int senderIndex;
    int receiverIndex;
    RequestNode *next;
};
struct AcceptedRequest
{
    int senderIndex;
    bool isAccepted;
};

class RequestList
{
private:
    RequestNode *front;
    RequestNode *rear;
    int *receiverIndices;
    int receiverCount;
    void deleteRequest(RequestNode *prev, RequestNode *current);

public:
    RequestList();
    ~RequestList();
    void displayAllRequests();
    void addRequest(const string &username, int senderIndex, int receiverIndex, int **Connection);
    int *showRequests(int **Connection, int &acceptedCount);
};
