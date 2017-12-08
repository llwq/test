#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    setWindowTitle(tr("My QQ"));
    setWindowIcon(QPixmap("D:/1.jpg"));

    tbtn1_1=new QToolButton;
    tbtn1_1->setText(tr("zhang san"));
    tbtn1_1->setIcon(QPixmap("D:/1.jpg"));
    tbtn1_1->setIconSize(QSize(20,30));
    tbtn1_1->setAutoRaise(true);
    tbtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn1_2=new QToolButton;
    tbtn1_2->setText(tr("li si"));
    tbtn1_2->setIcon(QPixmap("12.png"));
    tbtn1_2->setIconSize(QPixmap("12.png").size());
    tbtn1_2->setAutoRaise(true);
    tbtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn1_3=new QToolButton;
    tbtn1_3->setText(tr("wang wu"));
    tbtn1_3->setIcon(QPixmap("13.png"));
    tbtn1_3->setIconSize(QPixmap("13.png").size());
    tbtn1_3->setAutoRaise(true);
    tbtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn1_4=new QToolButton;
    tbtn1_4->setText(tr("xiao zhao"));
    tbtn1_4->setIcon(QPixmap("14.png"));
    tbtn1_4->setIconSize(QPixmap("14.png").size());
    tbtn1_4->setAutoRaise(true);
    tbtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn1_5=new QToolButton;
    tbtn1_5->setText(tr("xiao sun"));
    tbtn1_5->setIcon(QPixmap("15.png"));
    tbtn1_5->setIconSize(QPixmap("15.png").size());
    tbtn1_5->setAutoRaise(true);
    tbtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *box1=new QGroupBox;
    QVBoxLayout *layout1=new QVBoxLayout(box1);
    layout1->setMargin(10);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(tbtn1_1);
    layout1->addWidget(tbtn1_2);
    layout1->addWidget(tbtn1_3);
    layout1->addWidget(tbtn1_4);
    layout1->addWidget(tbtn1_5);
    layout1->addStretch();

    tbtn2_1=new QToolButton;
    tbtn2_1->setText(tr("xiao wang"));
    tbtn2_1->setIcon(QPixmap("21.png"));
    tbtn2_1->setIconSize(QPixmap("21.png").size());
    tbtn2_1->setAutoRaise(true);
    tbtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn2_2=new QToolButton;
    tbtn2_2->setText(tr("xiao zhang"));
    tbtn2_2->setIcon(QPixmap("22.png"));
    tbtn2_2->setIconSize(QPixmap("22.png").size());
    tbtn2_2->setAutoRaise(true);
    tbtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *box2=new QGroupBox;
    QVBoxLayout *layout2=new QVBoxLayout(box2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    layout2->addWidget(tbtn2_1);
    layout2->addWidget(tbtn2_2);

    tbtn3_1=new QToolButton;
    tbtn3_1->setText(tr("xiao chen"));
    tbtn3_1->setIcon(QPixmap("31.png"));
    tbtn3_1->setIconSize(QPixmap("31.png").size());
    tbtn3_1->setAutoRaise(true);
    tbtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tbtn3_2=new QToolButton;
    tbtn3_2->setText(tr("xiao li"));
    tbtn3_2->setIcon(QPixmap("32.png"));
    tbtn3_2->setIconSize(QPixmap("32.png").size());
    tbtn3_2->setAutoRaise(true);
    tbtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *box3=new QGroupBox;
    QVBoxLayout *layout3=new QVBoxLayout(box3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->addWidget(tbtn3_1);
    layout3->addWidget(tbtn3_2);

    this->addItem((QWidget*)box1,tr("my friends"));
    this->addItem((QWidget*)box2,tr("strangers"));
    this->addItem((QWidget*)box3,tr("black list"));

    connect(tbtn1_1,SIGNAL(clicked(bool)),this,SLOT(showChatWidget1()));
    connect(tbtn1_2,SIGNAL(clicked(bool)),this,SLOT(showChatWidget2()));
    connect(tbtn1_3,SIGNAL(clicked(bool)),this,SLOT(showChatWidget3()));
    connect(tbtn1_4,SIGNAL(clicked(bool)),this,SLOT(showChatWidget4()));
    connect(tbtn1_5,SIGNAL(clicked(bool)),this,SLOT(showChatWidget5()));
    connect(tbtn2_1,SIGNAL(clicked(bool)),this,SLOT(showChatWidget6()));
    connect(tbtn2_2,SIGNAL(clicked(bool)),this,SLOT(showChatWidget7()));
    connect(tbtn3_1,SIGNAL(clicked(bool)),this,SLOT(showChatWidget8()));
    connect(tbtn3_2,SIGNAL(clicked(bool)),this,SLOT(showChatWidget9()));
}

void Drawer::showChatWidget1()
{
    chatWidget1=new Widget(0,tbtn1_1->text());
    chatWidget1->setWindowTitle(tbtn1_1->text());
    chatWidget1->setWindowIcon(tbtn1_1->icon());
    chatWidget1->show();
}
void Drawer::showChatWidget2()
{
    chatWidget2=new Widget(0,tbtn1_2->text());
    chatWidget2->setWindowTitle(tbtn1_2->text());
    chatWidget2->setWindowIcon(tbtn1_2->icon());
    chatWidget2->show();
}
void Drawer::showChatWidget3()
{
    chatWidget3=new Widget(0,tbtn1_3->text());
    chatWidget3->setWindowTitle(tbtn1_3->text());
    chatWidget3->setWindowIcon(tbtn1_3->icon());
    chatWidget3->show();
}
void Drawer::showChatWidget4()
{
    chatWidget4=new Widget(0,tbtn1_4->text());
    chatWidget4->setWindowTitle(tbtn1_4->text());
    chatWidget4->setWindowIcon(tbtn1_4->icon());
    chatWidget4->show();
}
void Drawer::showChatWidget5()
{
    chatWidget5=new Widget(0,tbtn1_5->text());
    chatWidget5->setWindowTitle(tbtn1_5->text());
    chatWidget5->setWindowIcon(tbtn1_5->icon());
    chatWidget5->show();
}
void Drawer::showChatWidget6()
{
    chatWidget6=new Widget(0,tbtn2_1->text());
    chatWidget6->setWindowTitle(tbtn2_1->text());
    chatWidget6->setWindowIcon(tbtn2_1->icon());
    chatWidget6->show();
}
void Drawer::showChatWidget7()
{
    chatWidget7=new Widget(0,tbtn2_2->text());
    chatWidget7->setWindowTitle(tbtn2_2->text());
    chatWidget7->setWindowIcon(tbtn2_2->icon());
    chatWidget7->show();
}
void Drawer::showChatWidget8()
{
    chatWidget8=new Widget(0,tbtn3_1->text());
    chatWidget8->setWindowTitle(tbtn3_1->text());
    chatWidget8->setWindowIcon(tbtn3_1->icon());
    chatWidget8->show();
}
void Drawer::showChatWidget9()
{
    chatWidget9=new Widget(0,tbtn3_2->text());
    chatWidget9->setWindowTitle(tbtn3_2->text());
    chatWidget9->setWindowIcon(tbtn3_2->icon());
    chatWidget9->show();
}
