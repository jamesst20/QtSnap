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

    ClearScreen();

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
        //Connect signal that will be emitted once a snap is downloaded.
        QObject::connect(&snapchat.getConversationController(), &ConversationController::snapDownloadFinished, [=](int id, bool success, QByteArray data){
            if(success){
                QFile file("snap-" + QString::number(id) + ".jpg");
                file.open(QFile::WriteOnly);
                file.write(data);
                file.close();
                qDebug() << "Snap saved as " << "snap-" + QString::number(id) + ".jpg";
            }else{
                cout << "Failed to download snap. Why?";
            }
        });
        //Download all snaps
        QList<Snap> snaps = snapchat.getConversationController().getSnaps();
        foreach(Snap snap, snaps){
            if(snap.isDownloadable()){
                snapchat.getConversationController().getSnap(snap);
            }
        }
    }else if(choice == "2"){
        QObject::connect(&snapchat.getStoryController(), &StoryController::storyDownloadFinished, [=](int id, bool success, QByteArray data){
            if(success){
                QFile file("story-" + QString::number(id) + ".jpg");
                file.open(QFile::WriteOnly);
                file.write(data);
                file.close();
                qDebug() << "Story saved as " << "story-" + QString::number(id) + ".jpg";
            }else{
                cout << "Failed to download story. Why?";
            }

        });
        //Download all stories
        QList<Story> stories = snapchat.getStoryController().getStories();
        foreach(Story story, stories){
            snapchat.getStoryController().getStory(story);
        }
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
