#include <iostream>
#include <cstring>
#include <filesystem>

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
    if(path.length() > 0 && path[0] != '/')
        return;

    path = path.substr(1, path.length()-1);
    bool letter_found = false;
    for (int i = 0; i < path.length(); ++i) {
        if(!letter_found && isalpha(path[i])){
            letter_found = true;
            continue;
        }
        if(letter_found){
            if(path[i] == '/' || path[i] == '\\'){
                path.insert(i, ":");
                return;
            }
        }
    }
    if(!letter_found){
        printf("The path is invalid.. exiting");
        exit(-1);
    }
}

int main(int count, char** args) {
    if(count < 2){
        printf("No path provided, exiting..");
        return 0;
    }

    string path = string(args[1]);
    if(path.length() == 1 && path[0] == '/' || path[0] == '\\'){
        printf("Dangerous path provided, exiting..");
        return 0;
    }
    windowsify(path);

    if(!filesystem::exists(path)){
        printf("Path doesn't exist, exiting..");
        return 0;
    }

    filesystem::path path_instance = filesystem::absolute(path);
    bool is_dir = is_directory(path_instance);
    path = path_instance.string();
    enquote(path);

    //swapping \ to / results in "file not found"
    exit(0);
    string takeown = is_dir ? "takeown /r /f " + path : "takeown /f " + path;
    system(takeown.data());

    string icacls = "icacls " + path + " /grant \"%USERDOMAIN%\\%USERNAME%\":(F) /t";
    system(icacls.data());

    if(is_dir){
        string rmdir = "rd /s /q " + path;
        system(rmdir.data());
    }else{
        string del = "del /f /q " + path;
        system(del.data());
    }

    return 0;
}
