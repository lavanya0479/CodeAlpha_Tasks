#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cerrno> 
#include <cstring> 
using namespace std;

void listDirectory(const string& path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(dir);
    } else {
        cerr << "Error opening directory: " << path << endl;
    }
}

void viewFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }
}

void createDirectory(const string& dirname) {
    if (mkdir(dirname.c_str()) == -1) {
        cerr << "Error creating directory: " << dirname << endl;
    } else {
        cout << "Directory created successfully: " << dirname << endl;
    }
}



void copyFile(const string& src, const string& dest) {
    ifstream srcFile(src, ios::binary);
    ofstream destFile(dest, ios::binary);
    if (srcFile && destFile) {
        destFile << srcFile.rdbuf();
        cout << "File copied successfully from " << src << " to " << dest << endl;
    } else {
        cerr << "Error copying file from " << src << " to " << dest << endl;
    }
}

void moveFile(const string& src, const string& dest) {
    if (rename(src.c_str(), dest.c_str()) == 0) {
        cout << "File moved successfully from " << src << " to " << dest << endl;
    } else {
        cerr << "Error moving file from " << src << " to " << dest << endl;
    }
}

int main() {
    string command;
    cout << "\t\t\t\t\t\t**BASIC FILE MANAGER\n\n";
    cout << " ls - Lists the contents of a directory.\n";
    cout << " cat - Displays the contents of a file.\n";
    cout << " mkdir - Creates a new directory.\n";
    cout << " cp - Copies a file to a new location.\n";
    cout << " mv - Moves a file to a new location.\n";
    cout << " exit - Exits the file manager program.\n\n";
    while (true) {
        cout << "Enter a command (ls, cat, mkdir, touch, cp, mv, exit): ";
        cin >> command;

        if (command == "ls") {
            string path;
            cout << "Enter directory path: ";
            cin >> path;
            listDirectory(path);
        } else if (command == "cat") {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            viewFile(filename);
        } else if (command == "mkdir") {
            string dirname;
            cout << "Enter directory name: ";
            cin >> dirname;
            createDirectory(dirname);
        } else if (command == "cp") {
            string src, dest;
            cout << "Enter source file: ";
            cin >> src;
            cout << "Enter destination file: ";
            cin >> dest;
            copyFile(src, dest);
        } else if (command == "mv") {
            string src, dest;
            cout << "Enter source file: ";
            cin >> src;
            cout << "Enter destination file: ";
            cin >> dest;
            moveFile(src, dest);
        } else if (command == "exit") {
            break;
        } else {
            cerr << "Invalid command!" << endl;
        }
    }
    return 0;
}
