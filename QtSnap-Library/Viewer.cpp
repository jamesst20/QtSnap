#include "Viewer.h"

const QString Viewer::VIEWER_KEY = "viewer";
const QString Viewer::SCREENSHOTTED_KEY = "screenshotted";
const QString Viewer::TIMESTAMP_KEY = "timestamp";

Viewer::Viewer(QJsonObject viewerObj)
{
    this->username = viewerObj[VIEWER_KEY].toString();
    this->screenshot = viewerObj[SCREENSHOTTED_KEY].toBool();
    this->timestamp = viewerObj[TIMESTAMP_KEY].toString().toLong();
}

const QString Viewer::getViewerUsername() const {
    return this->username;
}

bool Viewer::hasScreenshotted() const {
    return this->screenshot;
}

long Viewer::getTime() const {
    return this->timestamp;
}
