#include "requestList.h"

RequestNode :: RequestNode(string f_name){
    friend_username = f_name;
    is_pending = true;
}

RequestList :: RequestList(){
    front = nullptr;
    back = nullptr;
}

