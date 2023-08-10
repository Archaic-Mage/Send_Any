#include "Server.h"

using namespace std;

class File {
    string file_name;
    ofstream file;
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
        file.open(file_name, ios::app);
    }
    void write_MB(vector<char> data) {
        file << data.data();
    }
    ~File() {
        file.close();
    }
};

int main(int argc, char** argv) {
    Server server(8080);

    while(true) {
        int connfd = server.accept_conn();
        cout << "Connection accepted" << endl;

        //recieve the file name
        vector<char> file_name = server.recieve(connfd);
        string file_name_str(file_name.begin(), file_name.end());


        //recieve the lenght of the file
        vector<char> len = server.recieve(connfd);
        int length = atoi(len.data());

        //recieve file data
        File file(file_name_str);
        while(length > 0) {
            vector<char> data = server.recieve(connfd);
            file.write_MB(data);
            length -= data.size();
        }
    }
}