#include <QCoreApplication>

#include "Snapchat.h"

static Snapchat snapchat;
static QTextStream in(stdin);
static QTextStream out(stdout);

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

    //Event loop used to force waiting for a signal
    QEventLoop loop;

    out << "Snapchat username : ";
    out.flush();
    QString username = in.readLine();

    out << "Snapchat password : ";
    out.flush();
    QString password = in.readLine();

    QObject::connect(&snapchat, &Snapchat::loginCompleted, &onLoginCompletted);
    QObject::connect(&snapchat, SIGNAL(loginCompleted(bool,QString)), &loop, SLOT(quit()));

    out << "Logging in...\n";
    out.flush();

    snapchat.login(username, password);

    //Wait for login finished
    loop.exec();

    //TODO Menu

    return a.exec();
}
