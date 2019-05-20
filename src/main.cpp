/* Boilerplate code for i3ipcpp lib and to start bar */
#include <iostream>
#include "../i3ipc++/include/i3ipc++/ipc.hpp"

const std::string left = "%{l}";

int main(){
    i3ipc::connection  conn;
    conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_BINDING);

    conn.signal_workspace_event.connect([](const i3ipc::workspace_event_t&  ev){
        if(ev.current->num == 1){
            std::cout << left << ev.current->num << std::endl; 
        }
        if(ev.current->num > 1){
            std::cout << left << ev.old->num << '\t' << ev.current->num << std::endl;
        }
    });

    while (true) {
        conn.handle_event();
            
    }

}
