#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QHttpPart>
#include <QByteArray>
#include <QTextStream>

class Utils
{
public:
    static void log(QString bytes);
    static QHttpPart makeHttpPart(const QString name, const QByteArray body, bool file = false);
    static QHttpPart makeHttpPart(const QString name, const QString body, bool file = false);

private:
    static QFile *file_log;
};

#endif // UTILS_H
