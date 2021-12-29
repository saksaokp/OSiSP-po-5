#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QtNetwork/QtNetwork>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(const QString& strHost, int nPort, QWidget* parent = nullptr);
    ~Widget();

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    quint16     m_nNextBlockSize;
    bool versionChecked = false;
    bool filesDeleted = false;
    int arrSize = 0;
    bool secondFile = false;

    void sendToServer(QString operation);

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   (                            );
};
#endif // WIDGET_H
