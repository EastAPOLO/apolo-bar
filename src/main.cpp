/* Boilerplate code for i3ipcpp lib and to start bar */
#include <iostream>
#include <i3ipc++/ipc.hpp>

/* Bar settings */
const std::string left = "%{l}";
const std::string right = "%{r}";
const std::string center = "%{c}";

/* Bar colors */
const std::string focused = "%{B#383838}";
const std::string urgent = "%{B#992525}";
const std::string button = "${B#2B2B2B}";
const std::string underline = "%{+u}%{U#3A85E2}";

/* Bar content */
std::string workspaces = "";
std::string music = "";
std::string time_date = "Clock";

void init_bar(){
    std::cout << underline << left << workspaces << right << time_date << std::endl;
}

void get_workspaces(i3ipc::connection& conn, std::string& workspace){
    auto ws = conn.get_workspaces();
    workspace = "";
    for(int x = 0; x < 10; ++x){
        for(int y = 1; y < 11; ++y){
            if(ws.size() > x && ws[x]->num == y){
                if(ws[x]->focused){
                    workspace += focused + std::to_string(ws[x]->num) + "%{B-}";
                }
                else if(ws[x]->urgent){
                    workspace += urgent + std::to_string(ws[x]->num) + "%{B-}";
                }
                else{
                    workspace += std::to_string(ws[x]->num) + "%{B-}";
                }
            } 
        }
    }
}



void workspace_event(const i3ipc::workspace_event_t& ev, i3ipc::connection& conn){
    get_workspaces(conn, workspaces);
    init_bar();
}

int main(){
        i3ipc::connection conn; 
        conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_WINDOW | i3ipc::ET_MODE | i3ipc::ET_BINDING);
        conn.signal_workspace_event.connect(sigc::bind<i3ipc::connection&>(&workspace_event, conn));
        get_workspaces(conn, workspaces);
        init_bar();

        while(true){
            conn.handle_event();
        }
}
