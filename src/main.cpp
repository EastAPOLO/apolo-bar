/* Boilerplate code for i3ipcpp lib and to start bar */
#include <iostream>
#include "../i3ipc++/include/i3ipc++/ipc.hpp"

/* Bar settings */
const std::string left = "%{l}";
const std::string right = "%{r}";
const std::string focused = "%{B#383838}";
const std::string urgent = "%{B#992525}";
const std::string underline = "%{B#3A85E2}";
const std::string button = "${B#2B2B2B}";

/* Bar content */
std::string workspaces = "";

void get_workspaces(i3ipc::connection& conn, std::string& workspace){
    auto ws = conn.get_workspaces();

    int count = 0;
    for(int x = 1; x < 11; ++x){
        if(ws.size() > count && ws[count]->num == x){
            if(ws[count]->focused){
                workspace += focused + std::to_string(ws[count]->num);
            }
            if(ws[count]->urgent){
                workspace += urgent + std::to_string(ws[count]->num);
            }
            ++count;
        }
    }
    
}

int main(){
    i3ipc::connection  conn;
    conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_WINDOW | i3ipc::ET_MODE | i3ipc::ET_BINDING);
    get_workspaces(conn, workspaces);
    std::cout << workspaces << std::endl;

    while(true){
        conn.handle_event();
    }

}
