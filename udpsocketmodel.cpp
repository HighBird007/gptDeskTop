#include "udpsocketmodel.h"

udpsocketmodel &udpsocketmodel::getinstance()
{
    static udpsocketmodel s;
    return s;
}

udpsocketmodel::udpsocketmodel() {
    u.bind(9998);
    connect(&u,&QUdpSocket::readyRead,this,[=](){
        QByteArray data;
        while(u.hasPendingDatagrams()){
             QNetworkDatagram datagram = u.receiveDatagram();
            data.append(datagram.data());
        }
        emit udpnotice(QString::fromUtf8(data));
    });
}
