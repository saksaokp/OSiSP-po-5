#include "server.hpp"

#include <QDir>
#include <QFile>

#include <fstream>
#include <string>

Server::Server() {
  this->m_SocketPtr = new QTcpSocket{};

  this->connect(this->m_SocketPtr, SIGNAL(readyRead()), this,
                SLOT(sf_socket_read()));
  this->connect(this->m_SocketPtr, SIGNAL(disconnected()), this,
                SLOT(sf_socket_disconnect()));

  if (this->listen(QHostAddress::Any, 2809)) {
    qDebug() << "Listening...";
    return;
  }

  qDebug() << "Error while listening!";
}

Server::~Server() { delete this->m_SocketPtr; }

void Server::incomingConnection(qintptr handle) {
  this->m_SocketPtr->setSocketDescriptor(handle);
  qDebug() << "Connected successfully!";
}

void Server::sf_socket_read() {
  QStringList v_Data{QString{this->m_SocketPtr->readAll()}.split(mc_Separator)};

  const QString c_ClientVersion{v_Data.first()};
  v_Data.pop_front();

  if (this->mc_Version == c_ClientVersion) {
    this->m_SocketPtr->write(QByteArray{"0"});
    qDebug() << "Everything is up to date!";
    return;
  }

  qDebug() << "Sending data to client...";
  this->m_SocketPtr->write(QByteArray{QString{
      '1' + mc_Separator + mc_Version +
      mc_Separator}.toStdString().c_str()});

  auto v_It{this->mc_Changes.begin()};

  for (; v_It != this->mc_Changes.end(); ++v_It) {
    if (v_It->first == c_ClientVersion) {
      ++v_It;
      break;
    }
  }

  std::ofstream v_Fout{QString{
      QDir::currentPath() + "/logs/log_" + QString::number(++m_LogCounter) +
      ".txt"}.toStdString()};

  if (!v_Fout.is_open()) {
    qDebug() << " Can not save log!";
  }

  std::uint64_t v_ChangeNumber{};

  QByteArray v_DataToSend{};

  for (; v_It != this->mc_Changes.end(); ++v_It) {
    QDir v_ChangesDir(QDir::currentPath() + "/versions/" + v_It->first);
    v_ChangesDir.setFilter(QDir::Files | QDir::NoSymLinks);

    if (v_Fout.is_open()) {
      v_Fout << QString{"Change: " + QString::number(++v_ChangeNumber) +
                        "\nClient version: " + c_ClientVersion +
                        "\nServer version: " + mc_Version + "\nFiles to send: "}
                    .toStdString();
    }

    QStringList v_NewFiles{};

    for (const QFileInfo& c_File : v_ChangesDir.entryInfoList()) {
      v_NewFiles.append(c_File.fileName());

      if (v_Fout.is_open()) {
        v_Fout << QString{c_File.fileName() + " "}.toStdString();
      }
    }

    if (v_Fout.is_open()) {
      v_Fout << "\n\n";
    }

    for (const QString& c_FileName : v_NewFiles) {
      v_DataToSend.append(QString{
          '2' + mc_Separator + c_FileName +
          mc_Separator}.toStdString()
                              .c_str());

      QFile v_File(v_ChangesDir.path() + '/' + c_FileName);
      constexpr uint64_t c_PART_SIZE{4096};

      if (v_File.open(QIODevice::ReadOnly)) {
        while (true) {
          const QByteArray c_DataPart{v_File.read(c_PART_SIZE)};

          if (c_DataPart.size() == 0) {
            break;
          }

          v_DataToSend.append(c_DataPart);
        }

        v_File.close();
      }

      v_DataToSend.append(mc_Separator.toStdString().c_str(),
                          mc_Separator.size());
    }
  }

  if (v_Fout.is_open()) {
    v_Fout.close();
  }

  this->m_SocketPtr->write(v_DataToSend);
  m_SocketPtr->waitForBytesWritten(-1);
  qDebug() << "Data was sent successfully!";
}

void Server::sf_socket_disconnect() {
  this->m_SocketPtr->close();
  qDebug() << "Disconnected successfully!\n";
}
