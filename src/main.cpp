#include <iostream>
#include <i3ipc++/ipc.hpp>

int main(){
    i3ipc::connection  conn;
    conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_BINDING);
}
