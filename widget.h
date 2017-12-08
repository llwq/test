#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QUdpSocket;   //UDP

namespace Ui {
class Widget;
}

enum MsgType{Msg,UsrEnter,UsrLeft,FileName,Refuse}; //不同的广播消息类型

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent,QString usrname);
    ~Widget();

private:
    Ui::Widget *ui;

protected:
    void usrEnter(QString usrname,QString ipaddr);      //新用户加入
    void usrLeft(QString usrname,QString time);         //用户离开
    void sendMsg(MsgType type,QString srvaddr="");      //广播消息

    QString getIP();                                    //获取IP地址
    QString getUsr();                                   //获取用户名
    QString getMsg();                                   //获取聊天信息

private:
    QUdpSocket *udpSocket;
    qint16 port;
    QString uName;
private slots:
    void processPendingDatagrams();
    void on_sendBtn_clicked();
};

#endif // WIDGET_H
