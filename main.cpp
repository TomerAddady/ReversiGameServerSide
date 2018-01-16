#include <iostream>


#include"Server.h"
#include<iostream>
#include<stdlib.h>
#include <fstream>
#include "GameManager.h"
using namespace std;
using namespace std;

int  main(int argc, char ** argv) {

    ifstream configFile;
    configFile.open("../configuratin_for_server.txt"); //optional path...

    // configFile.open("/home/tomer/CLionProjects/fromTomerMail/done/homeWork/ex3/configuration_for_client.txt");
    int port;
    configFile >> port;
   // cout << port << "psfkpfg" << endl;

    Server  server(port);
    GameManager * gameManager = GameManager :: getInstance();
    //Server server(9000);
    try {
        server.run();
        //server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    server.closeServer();
}
