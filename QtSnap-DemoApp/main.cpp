#include <QCoreApplication>

#include "Snapchat.h"

void onLoginCompletted(bool success, QString reason){
    qDebug() << "Success : " << success << " Reason : " << reason;
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

    Snapchat snapchat;
    QObject::connect(&snapchat, &Snapchat::loginCompleted, &onLoginCompletted);

    out << "Logging in...\n";
    out.flush();

    snapchat.login(username, password);

    return a.exec();
}
