#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>
#include <QToolButton>
#include "widget.h"

class Drawer : public QToolBox
{
    Q_OBJECT
public:
    Drawer(QWidget *parent=0,Qt::WindowFlags f=0);

private:
    QToolButton *tbtn1_1;
    QToolButton *tbtn1_2;
    QToolButton *tbtn1_3;
    QToolButton *tbtn1_4;
    QToolButton *tbtn1_5;
    QToolButton *tbtn2_1;
    QToolButton *tbtn2_2;
    QToolButton *tbtn3_1;
    QToolButton *tbtn3_2;

    Widget *chatWidget1;
    Widget *chatWidget2;
    Widget *chatWidget3;
    Widget *chatWidget4;
    Widget *chatWidget5;
    Widget *chatWidget6;
    Widget *chatWidget7;
    Widget *chatWidget8;
    Widget *chatWidget9;
private slots:
    void  showChatWidget1();
    void  showChatWidget2();
    void  showChatWidget3();
    void  showChatWidget4();
    void  showChatWidget5();
    void  showChatWidget6();
    void  showChatWidget7();
    void  showChatWidget8();
    void  showChatWidget9();
};

#endif // DRAWER_H
