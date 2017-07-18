#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QHostInfo>
#include<QDialog>
class QUdpSocket;
class QTextedit;

namespace Ui {
class Widget;
}

//枚举变量标志信息类型，分别为消息，新用户加入，用户退出
enum MessageType{Message,NewParticipant,ParticipantLeft};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:

    void sendMessage();
    QString getMessage();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 localport;
    QHostAddress localaddress ;
    qint16 remoteport;
    QHostAddress remoteaddress ;
    QColor color;
    QTextedit *messageedit;


private slots:

    void processPendingDatagrams();
    void on_sendButton_clicked();

    //调整字体
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_sizeComboBox_currentIndexChanged(const QString &arg1);
    void on_boldToolButton_clicked(bool checked);
    void on_italicToolButton_clicked(bool checked);
    void on_underlineToolButton_clicked(bool checked);
    void on_colorToolButton_clicked();

    //退出
    void on_exitButton_clicked();
    void on_clearToolButton_clicked();
};

#endif // WIDGET_H
