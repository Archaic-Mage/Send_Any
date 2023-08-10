#include "client.h"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define PORT 8080

class File {
    string file_name;
    ifstream file;
public:
    vector<char> get_file_name() {
        vector<char> ret;
        for(int i = 0; i < file_name.size(); i++) {
            ret.push_back(file_name[i]);
        }
        return ret;
    }
    File(string file_name) {
        this->file_name = file_name;
        file.open(file_name, ios::in);
    }
    vector<char> read_MB() {
        vector<char> ret;
        int i = 0;
        while(i < 1024 && !file.eof()) {
            char c;
            file >> c;
            ret.push_back(c);
            i++;
        }
        return ret;
    }
    int file_size() {
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.seekg(0, ios::beg);
        return size;
    }
    bool eof() {
        return file.eof();
    }
    ~File() {
        file.close();
    }
};

int main(int argc, char** argv) {

    // get the file name
    string file_name;
    file_name = string(argv[1]);

    string IP;
    IP = string(argv[2]);

    //create a client object 
    Client client(IP, PORT);
    //created file object
    File file(file_name);

    //set up the connection 
    client.set_conn();

    //send the file name
    client.send_data(file.get_file_name());

    //send the lenght of the file
    int file_size = file.file_size();
    cout << "To send " << file_size << " bytes" << endl;
    vector<char> file_size_str;
    while(file_size > 0) {
        file_size_str.push_back(file_size % 10 + '0');
        file_size /= 10;
    }
    reverse(file_size_str.begin(), file_size_str.end());
    client.send_data(file_size_str);

    //send the file data
    //send 1MB at a time
    while(!file.eof()) {
        vector<char> data = file.read_MB();
        client.send_data(data);
        cout << "sent " << data.size() << " bytes" << endl;
    }

    //close the connection
    client.close_conn();
}