#include <iostream>
#include <cstring>
using namespace std;
/**
 * Begone
 */

void enquote(string& path){
    size_t len = path.length();
    if(len < 2){
        return;
    }
    if(path[0] != '"' && path[len-1] != '"'){
        path = "\"" + path + "\"";
    }
}

void windowsify(string& path){
    if(path.length() < 2){
        return;
    }
    if(path[0] == '/'){
        path = path.substr(1, path.length()-1);
    }
    bool letter_found = false;
    for (int i = 0; i < path.length(); ++i) {
        if(!letter_found && isalpha(path[i])){
            letter_found = true;
            continue;
        }
        if(letter_found){
            if(path[i] == ':'){
                return;
            }
            if(path[i] == '/' || path[i] == '\\'){
                // insert == prepend from
                path.insert(i, ":");
                return;
            }
        }
    }
    printf("The path is invalid.. exiting");
    exit(-1);
}

int main(int count, char** args) {
    if(count < 2){
        printf("No path provided, exiting..");
        return 0;
    }

    string path = string(args[1]);
    windowsify(path);
    enquote(path);

    string takeown = "takeown /r /f " + path;
    system(takeown.data());

    string icacls = "icacls " + path + " /grant \"%USERDOMAIN%\\%USERNAME%\":(F) /t";
    system(icacls.data());

    string del = "del /f /q " + path;
    system(del.data());

    string rmdir = "rd /s /q " + path;
    system(rmdir.data());

    return 0;
}
