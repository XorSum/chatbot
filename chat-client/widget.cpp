#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include<QLabel>
#include<QTextEdit>
#include<QUdpSocket>
#include<QHostInfo>
#include<QMessageBox>
#include<QScrollBar>
#include<QDateTime>
#include<QNetworkInterface>
#include<QProcess>
#include<QColorDialog>
#include<string>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    localport  = 8084;
    localaddress =  QHostAddress("127.0.0.1");

    remoteport  = 8082;
    remoteaddress =  QHostAddress("127.0.0.1");

    udpSocket->bind(localaddress,localport);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));


}

Widget::~Widget()
{
    delete ui;
}
//接收
void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        ui->messageBrowser->setTextColor(Qt::blue);
        ui->messageBrowser->append(datagram.data());
    }
}

//发送
void Widget::on_sendButton_clicked()
{
    if(ui->messageTextEdit->toPlainText()=="")
         {
             QMessageBox::warning(0,tr("警告"),
                                  tr("发送内容不能为空"),QMessageBox::Ok);
             return;
         }

    ui->messageBrowser->verticalScrollBar()
            ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
    QString str= ui->messageTextEdit->toPlainText();
    ui->messageBrowser->setTextColor(Qt::black);
    if(color.isValid())
    {
        ui->messageTextEdit->setTextColor(color);
        ui->messageTextEdit->setFocus();
        ui->messageBrowser->setTextColor(color);
    }
    ui->messageBrowser->append(str);
    //ui->messageBrowser->setTextColor(Qt::black);
    QByteArray  data=ui->messageTextEdit->toPlainText().toUtf8();
    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();

    udpSocket->writeDatagram(data,data.length(),remoteaddress, remoteport);


}

//更改字体族
void Widget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->messageTextEdit->setCurrentFont(f);
    ui->messageTextEdit->setFocus();
    ui->messageBrowser->setCurrentFont(f);
}

//更改字体大小
void Widget::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->messageTextEdit->setFontPointSize(arg1.toDouble());
    ui->messageTextEdit->setFocus();
    ui->messageBrowser->setFontPointSize(arg1.toDouble());
}

//加粗
void Widget::on_boldToolButton_clicked(bool checked)
{
    if(checked)
      { ui->messageTextEdit->setFontWeight(QFont::Bold);
        ui->messageBrowser->setFontWeight(QFont::Bold);
    }

    else
       {ui->messageTextEdit->setFontWeight(QFont::Normal);
       ui->messageTextEdit->setFocus();
       ui->messageBrowser->setFontWeight(QFont::Normal);
    }
}

//倾斜
void Widget::on_italicToolButton_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
    ui->messageBrowser->setFontItalic(checked);
}

//下划线
void Widget::on_underlineToolButton_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
    ui->messageBrowser->setFontUnderline(checked);
}

//颜色
void Widget::on_colorToolButton_clicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        ui->messageTextEdit->setTextColor(color);
        ui->messageTextEdit->setFocus();
        ui->messageBrowser->setTextColor(color);
     }
}

//退出
void Widget::on_exitButton_clicked()
{
    close();
}


//清空
void Widget::on_clearToolButton_clicked()
{
    ui->messageBrowser->clear();
}

void Widget::on_underlineToolButton_clicked()
{

}
