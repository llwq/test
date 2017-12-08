#include "widget.h"
#include "ui_widget.h"

#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>

Widget::Widget(QWidget *parent, QString usrname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    uName=usrname;
    udpSocket=new QUdpSocket(this);
    port=23232;
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    sendMsg(UsrEnter);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMsg(MsgType type, QString srvaddr)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    QString address=getIP();
    out<<type<<getUsr();                        //写入信息类型和用户名

    switch(type)
    {
        case Msg:
            if(ui->msgTxtEdit->toPlainText()=="")
            {
               QMessageBox::warning(0,tr("warning"),tr("sendMessage cannot be empty"),
                                    QMessageBox::Ok);
               return;
            }
            out<<address<<getMsg();             //写入IP地址和聊天信息
            ui->msgBrowser->verticalScrollBar()->setValue(
                        ui->msgBrowser->verticalScrollBar()->maximum());
            break;
         case UsrEnter:
            out<<address;
            break;
        case UsrLeft:
            break;
        case FileName:
            break;
        case Refuse:
            break;
    }
    //UDP广播
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
}

void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())         //判断是否有等待读取数据
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());   //读取数据
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int MsgType;
        in>>MsgType;
        QString usrName,ipAddr,msg;
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        switch(MsgType)
        {
        case Msg:
            in>>usrName>>ipAddr>>msg;
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->msgBrowser->append("[ "+usrName+" ]");
            ui->msgBrowser->append(msg);
            break;
        case UsrEnter:
            in>>usrName>>ipAddr;
            usrEnter(usrName,ipAddr);
            break;
        case UsrLeft:
            in>>usrName;
            usrLeft(usrName,time);
            break;
        case FileName:
            break;
        case Refuse:
            break;
        }
    }
}

void Widget::usrEnter(QString usrname, QString ipaddr)
{
    bool isEmpty=ui->usrTblWidget->findItems(usrname,Qt::MatchExactly).isEmpty();
    if(isEmpty)                 //用户不在列表中
    {
        QTableWidgetItem *usr=new QTableWidgetItem(usrname);
        QTableWidgetItem *ip=new QTableWidgetItem(ipaddr);
        ui->usrTblWidget->setColumnCount(3);            //设置列数
        ui->usrTblWidget->setRowCount(5);               //设置行数
        ui->usrTblWidget->setHorizontalHeaderLabels();  //设置标题
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0,0,usr);
        ui->usrTblWidget->setItem(0,1,ip);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->msgBrowser->append(tr("%1 on line!").arg(usrname));
        ui->usrNumLbl->setText(tr("on line number: %1").arg(ui->
                               usrTblWidget->rowCount()));
        sendMsg(UsrEnter);      //需要再次发送新用户登录信息
    }
}

void Widget::usrLeft(QString usrname, QString time)
{
    int rowNum=ui->usrTblWidget->findItems(usrname,Qt::MatchExactly).
            first()->row();
    ui->usrTblWidget->removeRow(rowNum);
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->msgBrowser->append(tr("%1 leaves at %2!").arg(usrname).arg(time));
    ui->usrNumLbl->setText(tr("on line number: %1").arg(ui->
                           usrTblWidget->rowCount()));
}

QString Widget::getIP()
{
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach(QHostAddress addr,list)
    {
        if(addr.protocol()==QAbstractSocket::IPv4Protocol)
            return addr.toString();
    }
    return 0;
}

QString Widget::getUsr()
{
    return uName;
}

QString Widget::getMsg()
{
    QString msg=ui->msgTxtEdit->toHtml();
    ui->msgTxtEdit->clear();
    ui->msgTxtEdit->setFocus();
    return msg;
}

void Widget::on_sendBtn_clicked()
{
    sendMsg(Msg);
}
