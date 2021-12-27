#include "widget.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

Widget::Widget(int nPort, QWidget *parent)
    : QWidget(parent), m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
           );

    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

void Widget::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );
}

void Widget::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QString str;
        in >> str;

        QString strMessage = QTime::currentTime().toString() + " Client has sended - " + str;
        m_ptxt->append(strMessage);

        m_nNextBlockSize = 0;

        if (str.compare("body") == 0) {
            sendToClient(pClientSocket,
                         "body",
                         QDir::currentPath() + "/../build-helper_class-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/helper_class.dll",
                         QDir::currentPath() + "/../build-OSISP_lab1-2-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/OSISP_lab1-2.exe"
                        );
        }
        else if (str.compare("version") == 0){
            sendToClient(pClientSocket,
                         "version",
                         QDir::currentPath() + "/programVersion.txt",
                         ""
                        );
        }
    }
}

void Widget::sendToClient(QTcpSocket* pSocket, const QString& str, const QString& path, const QString& path2)
{
    if (str.compare("version") == 0) {
        QByteArray arrBlock;
        QFile file(path);
        file.open(QIODevice::ReadOnly);

        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        out << quint16(0);

        QString version = file.readAll();
        out << version;

        file.close();

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        pSocket->write(arrBlock);
    }
    else if (str.compare("body") == 0) {
        QByteArray arrBlock;

        QFile file(path);
        file.open(QIODevice::ReadOnly);

        arrBlock.append(file.readAll());

        file.close();

        arrBlock.append("\n\n\n\n");

        QFile file2(path2);
        file2.open(QIODevice::ReadOnly);

        arrBlock.append(file2.readAll());

        file2.close();

        qDebug() << arrBlock.size();

        pSocket->write(arrBlock);
    }
}

Widget::~Widget()
{
}

