#ifndef UDPSOCKETMODEL_H
#define UDPSOCKETMODEL_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
class udpsocketmodel : public QObject
{
    Q_OBJECT
public:
    static udpsocketmodel& getinstance();
private:
    udpsocketmodel();

    QUdpSocket u;
signals:
    void udpnotice(QString);
};

#endif // UDPSOCKETMODEL_H
