#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QByteArray>
#include <QTextStream>

class Utils
{
public:
    static void log(QByteArray bytes);

private:
    static QFile *file_log;
};

#endif // UTILS_H
