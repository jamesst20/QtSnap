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
    /// \brief NetworkRequestMaker Create a basic x-www-form-urlencoded POST request.
    /// \param url URL to send the POST request.
    /// \param params Parameters of the request.
    ///
    NetworkRequestMaker(QString url, QUrlQuery params);

    ///
    /// \brief NetworkRequestMaker Create a basic multipart/form-data POST request.
    /// \param url URL to send the POST request.
    /// \param params Parameters of the request. This can include files.
    ///
    NetworkRequestMaker(QString url, QList<QHttpPart> params);

    ///
    /// \brief executeRequest Execute the request
    ///
    void executeRequest();
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
    QHttpMultiPart *httpMultiPart = 0;
    QNetworkRequest request;
    QByteArray parametersByteArray;
    QUrlQuery parameters;

    static const QString BASE_URL;
};

#endif // NETWORKREQUESTMAKER_H
