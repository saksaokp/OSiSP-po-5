#include "widget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkAccessManager>

Widget::Widget(const QString& strHost, int nPort, QWidget *parent)
    : QWidget(parent), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);

    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    m_ptxtInfo  = new QTextEdit;
    m_ptxtInfo->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    setLayout(pvbxLayout);

    sendToServer("version");
}

void Widget::slotReadyRead()
{
    if (!versionChecked) {
        QDataStream in(m_pTcpSocket);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        for (;;) {
            if (!m_nNextBlockSize) {
                if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }

                in >> m_nNextBlockSize;
            }

            if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
                break;
            }

            QString body;
            in >> body;

            m_ptxtInfo->append("Got version from server");

            QFile file(QDir::currentPath() + "/programVersion.txt");
            file.open(QIODevice::ReadOnly);
            QString version = file.readAll();
            file.close();

            m_ptxtInfo->append(version);

            if (body.toInt() == version.toInt()) {
                switch (QMessageBox::warning(this, "Обновления не требуются",
                   "Программа уже обновлена до последней версии",
                   QMessageBox::Ok | QMessageBox::Cancel,
                   QMessageBox::Cancel))
                {
                    case QMessageBox::Ok:
                        this->close();
                        break;
                    case QMessageBox::Cancel:
                        this->close();
                        break;
                }
            }
            else if (body.toInt() > version.toInt()) {
                QByteArray ba;
                ba.append(body.toUtf8());

                QFile file(QDir::currentPath() + "/programVersion.txt");
                file.open(QIODevice::WriteOnly);
                file.write(ba);
                file.close();

                switch (QMessageBox::warning(this, "Последние обновления не установлены",
                   "Желаете обновить программу?",
                   QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                   QMessageBox::Cancel))
                {
                    case QMessageBox::Yes:
                        sendToServer("body");
                        break;
                    case QMessageBox::No:
                        this->close();
                        break;
                    case QMessageBox::Cancel:
                        this->close();
                        break;
                }
            }

            m_nNextBlockSize = 0;
        }

        m_nNextBlockSize = 0;
        versionChecked = true;
    }
    else {
        if (!secondFile) {
            m_ptxtInfo->append("Got file.dll info from server");

            if (!filesDeleted) {
                QFile::remove(QDir::currentPath() + "/../arkanoid/helper_class.dll");
                QFile::remove(QDir::currentPath() + "/../arkanoid/OSISP_lab1-2.exe");
                filesDeleted = true;
            }

            QByteArray byteArr;

            QThread::msleep(300);
            while (m_pTcpSocket->bytesAvailable() > 0) {
                byteArr.append(m_pTcpSocket->readAll());
                m_pTcpSocket->flush();
            }

            arrSize += byteArr.size();

            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QString s = codec->toUnicode(byteArr);
            QStringList list = s.split("\n\n\n\n");

            if (list.size() == 1) {
                QByteArray output;
                output.append(codec->fromUnicode(list[0]));

                QFile file(QDir::currentPath() + "/../arkanoid/helper_class.dll");
                file.open(QIODevice::WriteOnly | QIODevice::Append);
                file.write(output);
                file.close();

                m_ptxtInfo->append("File.dll updated");
                m_ptxtInfo->append(QString::number(arrSize));
            }
            else if (list.size() == 2) {
                QByteArray output;
                output.append(codec->fromUnicode(list[0]));

                QByteArray output2;
                output2.append(codec->fromUnicode(list[1]));

                QFile file(QDir::currentPath() + "/../arkanoid/helper_class.dll");
                file.open(QIODevice::WriteOnly | QIODevice::Append);
                file.write(output);
                file.close();

                m_ptxtInfo->append("File.dll updated");

                QFile file2(QDir::currentPath() + "/../arkanoid/OSISP_lab1-2.exe");
                file2.open(QIODevice::WriteOnly | QIODevice::Append);
                file2.write(output2);
                file2.close();

                m_ptxtInfo->append("File.exe updated");
                m_ptxtInfo->append(QString::number(arrSize));

                secondFile = true;
            }
        }
        else {
            m_ptxtInfo->append("Got file.exe info from server");

            QByteArray byteArr;

            QThread::msleep(300);
            while (m_pTcpSocket->bytesAvailable() > 0) {
                byteArr.append(m_pTcpSocket->readAll());
                m_pTcpSocket->flush();
            }

            arrSize += byteArr.size();

            QFile file(QDir::currentPath() + "/../arkanoid/OSISP_lab1-2.exe");
            file.open(QIODevice::WriteOnly | QIODevice::Append);
            file.write(byteArr);
            file.close();

            m_ptxtInfo->append("File.exe updated");
            m_ptxtInfo->append(QString::number(arrSize));
        }
    }
}

void Widget::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtInfo->append(strError);
}

void Widget::sendToServer(QString operation)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << operation;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
}

void Widget::slotConnected()
{
    m_ptxtInfo->append("Received the connected() signal");
}

Widget::~Widget()
{
}

