#include "Utils.h"

QFile *Utils::file_log = 0;

void Utils::log(QString text){
    if (!file_log){
        if (QFile::exists("./logs.txt")){
            QFile::remove("./logs.txt");
        }
        file_log = new QFile("./logs.txt");
        file_log->open(QIODevice::WriteOnly | QIODevice::Text);
    }
    QTextStream out(file_log);
    out.setCodec("UTF-8");
    out << text << "\n";
}
