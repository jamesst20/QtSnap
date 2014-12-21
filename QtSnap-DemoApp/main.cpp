#include <QCoreApplication>

#include "Snapchat.h"

static Snapchat snapchat;

void onLoginCompletted(bool success, QString reason){
    qDebug() << "Login status : " << success << " Reason : " << reason;
    if(success){
        snapchat.refresh();
    }
}

void onRefreshCompletted(bool success, QString reason){
    qDebug() << "Refresh status : " << success << " Reason : " << reason;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);
    out << "Snapchat username : ";
    out.flush();
    QString username = in.readLine();

    out << "Snapchat password : ";
    out.flush();
    QString password = in.readLine();

    QObject::connect(&snapchat, &Snapchat::loginCompleted, &onLoginCompletted);
    QObject::connect(&snapchat, &Snapchat::refreshCompleted, &onRefreshCompletted);

    out << "Logging in...\n";
    out.flush();

    snapchat.login(username, password);


    return a.exec();
}
