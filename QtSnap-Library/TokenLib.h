#ifndef TOKENLIB_H
#define TOKENLIB_H

#include <QString>
#include <QCryptographicHash>

class TokenLib
{
public:
    static QString getRequestToken(QString token, long timestamp);
    static QString getStaticRequestToken(long timestamp);

private:
    static const QString SECRET;
    static const QString PATTERN;
    static const QString STATIC_TOKEN;

    static QString hexDigest(QString toDigest);
};

#endif // TOKENLIB_H
