#include <iostream>


#include"Server.h"
#include<iostream>
#include<stdlib.h>
#include <fstream>

using namespace std;
using namespace std;

int  main(int argc, char ** argv) {

    ifstream configFile;
    configFile.open("../configuratin_for_server.txt"); //optional path...

    // configFile.open("/home/tomer/CLionProjects/fromTomerMail/done/homeWork/ex3/configuration_for_client.txt");
    int port;
    configFile >> port;


    Server  server(port);
    //Server server(9000);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
