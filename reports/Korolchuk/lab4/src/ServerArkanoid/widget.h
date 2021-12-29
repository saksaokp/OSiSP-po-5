#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QtNetwork/QtNetwork>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str, const QString& path, const QString& path2);

public slots:
        virtual void slotNewConnection();
        void slotReadClient();

public:
    Widget(int nPort, QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
