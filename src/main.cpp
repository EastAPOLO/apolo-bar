/* Boilerplate code for i3ipcpp lib and to start bar */
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <i3ipc++/ipc.hpp>

/* Bar settings */
const std::string left = "%{l}";
const std::string right = "%{r}";
const std::string center = "%{c}";

/* Bar colors */
const std::string focused = "%{B#484848}";
const std::string urgent = "%{B#992525}";
const std::string button = "%{B#383838}";
const std::string underline = "%{+u}%{O1920}";

void init_bar(std::string &workspaces, std::string &clock){
    std::cout << underline << left << workspaces << right << clock << std::endl;
}

void get_workspaces(i3ipc::connection& conn, std::string& workspace){
    auto ws = conn.get_workspaces();
    workspace = "";
    for(int x = 0; x < 10; ++x){
        for(int y = 1; y < 11; ++y){
            if(ws.size() > x && ws[x]->num == y){
                if(ws[x]->focused){
                    workspace += focused + "%{O8}" + std::to_string(ws[x]->num) +  "%{O8}" + "%{B-}%{O4}";
                }
                else if(ws[x]->urgent){
                    workspace += urgent +"%{O8}" + std::to_string(ws[x]->num) + "%{O8}" + "%{B-}%{O4}";
                }
                else{
                    workspace += "%{O8}" + std::to_string(ws[x]->num) + "%{O8}" + "%{B-}%{O4}";
                }
            }
        }
    }
}

void get_time(std::string& l_c, std::string &workspaces){
    while(true){
        l_c = "";
        std::time_t t = time(nullptr);
        std::tm* current = localtime(&t);
        if(current->tm_hour <= 9){
            l_c += button + "%{O8}" + "0" + std::to_string(current->tm_hour) + ":";
        }else{
            l_c += button + "%{O8}" + std::to_string(current->tm_hour) + ":";
        }

        if(current->tm_min <= 9){
            l_c += "0" + std::to_string(current->tm_min) + "%{O8}" + "%{B-}";
        }else {
            l_c += std::to_string(current->tm_min) + "%{O8}" + "%{B-}";
        }
        init_bar(workspaces, l_c);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void workspace_event(const i3ipc::workspace_event_t& ev, i3ipc::connection& conn, std::string &workspaces, std::string &clock){
    get_workspaces(conn, workspaces);
    init_bar(workspaces, clock);
}

int main(){
    /* Bar Content */
    std::string workspaces;
    std::string clock;

    std::thread t1(get_time, std::ref(clock), std::ref(workspaces));
    i3ipc::connection conn;
    conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_WINDOW | i3ipc::ET_MODE | i3ipc::ET_BINDING);
    conn.signal_workspace_event.connect(sigc::bind<i3ipc::connection&>(&workspace_event, conn, workspaces, clock));
    get_workspaces(conn, workspaces);
    init_bar(workspaces, clock);

    while(true){
        conn.handle_event();
    }

    t1.join();

}
