#include <QCoreApplication>
#include <QFile>

#include <cstdlib>
#include <iostream>
#include <string>

#include "Snapchat.h"


using namespace std;

void ClearScreen();

static QTextStream in(stdin);

void onLoginCompletted(bool success, QString reason){
    if(success){
        qDebug() << "Login successful.\n";
    }else{
        qDebug() << "Failed to login : " << reason << "\n";
        qDebug() << "Press return key to exit.";
        //Wait for enter key.
        in.readLine();
        //Exit
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Snapchat snapchat;    

    cout << "Snapchat username : ";
    QString username = in.readLine();

    cout << "Snapchat password : ";
    QString password = in.readLine();

    //Event loop used to force waiting for a signal
    QEventLoop loop;

    QObject::connect(&snapchat, &Snapchat::loginCompleted, &onLoginCompletted);
    QObject::connect(&snapchat, SIGNAL(loginCompleted(bool,QString)), &loop, SLOT(quit()));

    cout << "Logging in...\n";

    //Login
    snapchat.login(username, password);

    //Wait for login finished
    loop.exec();

    //Menu
    ClearScreen();
    cout << "\n\n";
    cout << "======== Please select one of the following ========" << endl;
    cout << "=                                                  =" << endl;
    cout << "=                 1. Download Snaps                =" << endl;
    cout << "=                 2. Download Stories              =" << endl;
    cout << "=                 3. Send a snap                   =" << endl;
    cout << "=                 4. Send a story                  =" << endl;
    cout << "=                                                  =" << endl;
    cout << "====================================================" << endl;

    QString choice = in.readLine(1);

    if(choice == "1"){

    }else if(choice == "2"){

    }else if(choice == "3"){

    }else if(choice == "4"){

    }else{
        cout << endl << "Invalid choice.";
    }

    return a.exec();
}

void ClearScreen() {
    if (system("CLS")) system("clear");
}
