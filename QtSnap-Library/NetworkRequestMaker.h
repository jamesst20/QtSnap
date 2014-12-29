#ifndef NETWORKREQUESTMAKER_H
#define NETWORKREQUESTMAKER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QFile>

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <functional>

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
    /// \param id Integer returned by the finished signal. Useful for retrieving which request has finished.
    /// \param url URL where to send the POST request.
    /// \param params Parameters of the request.
    /// \param callback_function Function to callback when the request is done.
    ///
    void executeRequest(int id, const QString &url, const QUrlQuery &params, std::function<void(int, int, QByteArray)> callback_function);

    ///
    /// \brief executeRequest Execute a basic multipart/form-data POST request.
    /// \param id Integer returned by the finished signal. Useful for retrieving which request has finished.
    /// \param url URL where to send the POST request.
    /// \param params Parameters of the request. This can include files.
    /// \param callback_function Function to callback when the request is done.
    ///
    void executeRequest(int id, const QString &url, const QList<QHttpPart> &params, std::function<void(int, int, QByteArray)> callback_function);

    ///
    /// \brief executeRequest Execute a basic GET request.
    /// \param id Integer returned by the finished signal. Useful for retrieving which request has finished.
    /// \param url URL where to send GET request;
    /// \param params Parameters of the request.
    /// \param callback_function Function to callback when the request is done.
    ///
    void executeRequest(int id, const QString &url, const QHash<QString, QString> &params, std::function<void(int, int, QByteArray)> callback_function);

    ~NetworkRequestMaker();

private slots:
    void finished(QNetworkReply*);

private:
    QNetworkAccessManager *manager = 0;

    struct RequestCallbackInfo {
        int id;
        std::function<void(int, int, QByteArray)> callback_func;
        RequestCallbackInfo(){}
        RequestCallbackInfo(int id, std::function<void(int, int, QByteArray)> callback_func) {this->id = id; this->callback_func = callback_func;}
    };

    QHash<QNetworkReply*, RequestCallbackInfo> callback_list;

    static const QString BASE_URL;
    static const QString HEADER_USER_AGENT;
    static const QString HEADER_URL_ENCODED;
};

#endif // NETWORKREQUESTMAKER_H
