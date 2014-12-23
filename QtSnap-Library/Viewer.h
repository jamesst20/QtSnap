#ifndef VIEWER_H
#define VIEWER_H

#include <QString>
#include <QJsonObject>

class Viewer
{
public:
    Viewer(QJsonObject viewerObj);

    const QString getViewerUsername() const;
    bool hasScreenshotted() const;
    long getTime() const;

private:
    QString username;
    bool screenshot;
    long timestamp;

    static const QString VIEWER_KEY;
    static const QString SCREENSHOTTED_KEY;
    static const QString TIMESTAMP_KEY;
};

#endif // VIEWER_H
