#ifndef NETWORKREQUESTMAKER_H
#define NETWORKREQUESTMAKER_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QString>
#include <QFile>

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QHttpMultiPart>
#include <QHttpPart>

#include "Utils.h"


class NetworkRequestMaker : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief NetworkRequestMaker Initialize the NetworkRequestMaker.
    ///
    NetworkRequestMaker();

    ///
    /// \brief executeRequest Execute a basic x-www-form-urlencoded POST request.
    /// \param url URL where to send the POST request.
    /// \param params Parameters of the request.
    ///
    void executeRequest(const QString &url, const QUrlQuery &params);

    ///
    /// \brief executeRequest Execute a basic multipart/form-data POST request.
    /// \param url URL where to send the POST request.
    /// \param params Parameters of the request. This can include files.
    ///
    void executeRequest(const QString &url, const QList<QHttpPart> &params);

    ~NetworkRequestMaker();
signals:
    ///
    /// \brief onRequestDone Signal emited once the request has been completed.
    /// \param httpCode HTTP status code.
    /// \param output Data received.
    ///
    void onRequestDone(int httpCode, QByteArray output);

private slots:
    void finished(QNetworkReply*);

private:
    QNetworkAccessManager *manager = 0;

    static const QString BASE_URL;
    static const QString HEADER_USER_AGENT;
    static const QString HEADER_URL_ENCODED;
};

#endif // NETWORKREQUESTMAKER_H
