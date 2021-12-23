#include "updater.hpp"

#include <QDir>
#include <QFile>
#include <QMessageBox>

#include <fstream>

Updater::Updater(QString& v_VersionLink, QObject* const c_QObjectPtr)
    : QObject(c_QObjectPtr), m_VersionLink(v_VersionLink) {}

Updater::~Updater() { delete m_SocketPtr; }

void Updater::sf_process() {
  if (m_SocketPtr != nullptr) {
    m_SocketPtr->close();
    delete m_SocketPtr;
  }

  m_SocketPtr = new QTcpSocket(this);
  connect(m_SocketPtr, SIGNAL(readyRead()), this, SLOT(sf_socket_read()));
  connect(m_SocketPtr, SIGNAL(disconnected()), this,
          SLOT(sf_socket_disconnect()));

  m_SocketPtr->connectToHost("127.0.0.1", 2809);
  m_SocketPtr->waitForConnected(1);

  if (m_SocketPtr->state() != QTcpSocket::ConnectedState ||
      !m_SocketPtr->isOpen()) {
    emit s_end_progress();
    emit s_can_not_connect();
    return;
  }

  m_SocketPtr->write(QByteArray::fromStdString(m_VersionLink.toStdString()));
}

void Updater::sf_socket_read() {
  emit s_connecting();

  QByteArray v_RawData{};

  while (m_SocketPtr->bytesAvailable()) {
    emit s_add_progress();
    v_RawData.append(m_SocketPtr->readAll());
    m_SocketPtr->waitForReadyRead(100);
  }

  std::ofstream v_Fout{QString{
      QDir::currentPath() + "/logs/log_" + QString::number(++m_LogCounter) +
      ".txt"}.toStdString()};

  if (v_Fout.is_open()) {
    v_Fout << QString{"Client version: " + m_VersionLink + '\n'}.toStdString();
  } else {
    qDebug() << "Can not save log!";
  }

  std::int64_t v_PositionNow{},
      v_PositionNext{v_RawData.indexOf(",,,,,", v_PositionNow)};

  while (v_PositionNow < v_RawData.size()) {
    emit s_add_progress();

    QString v_ResponseCode{};

    if (v_PositionNext == -1) {
      v_ResponseCode =
          v_RawData.sliced(v_PositionNow, v_PositionNow + v_RawData.size());
    } else {
      v_ResponseCode =
          v_RawData.sliced(v_PositionNow, v_PositionNext - v_PositionNow);
    }

    if (v_ResponseCode == "0") {
      emit s_end_progress();
      emit s_up_to_date();
      return;
    }

    v_PositionNow = v_PositionNext + mc_Separator.size();
    v_PositionNext = v_RawData.indexOf(",,,,,", v_PositionNow);

    if (v_ResponseCode == "1") {
      const QString c_Version{

          v_RawData.sliced(v_PositionNow, v_PositionNext - v_PositionNow)};

      v_PositionNow = v_PositionNext + mc_Separator.size();
      v_PositionNext = v_RawData.indexOf(",,,,,", v_PositionNow);

      m_VersionLink = c_Version;
      v_Fout << QString{"Server version: " + m_VersionLink +
                        "\nFiles to receive: "}
                    .toStdString();
      continue;
    }

    if (v_ResponseCode == "2") {
      const QString c_NewFileName{
          v_RawData.sliced(v_PositionNow, v_PositionNext - v_PositionNow)};

      if (v_Fout.is_open()) {
        v_Fout << QString{c_NewFileName + " "}.toStdString();
      }

      v_PositionNow = v_PositionNext + mc_Separator.size();
      v_PositionNext = v_RawData.indexOf(",,,,,", v_PositionNow);

      const QByteArray c_Data{
          v_RawData.sliced(v_PositionNow, v_PositionNext - v_PositionNow)};

      v_PositionNow = v_PositionNext + mc_Separator.size();
      v_PositionNext = v_RawData.indexOf(",,,,,", v_PositionNow);

      QFile v_File(QDir::currentPath() + "/files/" + c_NewFileName);

      if (v_File.open(QIODevice::WriteOnly)) {
        v_File.write(c_Data);
        v_File.close();
      }

      continue;
    }

    break;
  }

  if (v_Fout.is_open()) {
    v_Fout << '\n';
    v_Fout.close();
  }

  emit s_end_progress();
  emit s_updated();
  emit s_finished();
}

void Updater::sf_socket_disconnect() { m_SocketPtr->close(); }
