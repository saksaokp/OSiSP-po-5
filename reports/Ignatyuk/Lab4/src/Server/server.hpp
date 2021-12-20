#pragma once

#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpSocket>
#include <QTcpServer>

class Server : public QTcpServer {
  Q_OBJECT

 public:
  Server();
  ~Server();

 private:
  QTcpSocket* m_SocketPtr{nullptr};
  const QString mc_Version{"1.2"};

  const QVector<QPair<QString, QStringList>> mc_Changes{
      {QString{"1.0"}, QStringList{}},
      {QString{"1.1"}, QStringList{"first_new_file.mp4"}},
      {QString{"1.2"}, QStringList{"second_new_file.mp4"}}};

  const QString mc_Separator{",,,,,"};

  std::uint64_t m_LogCounter{};

 public slots:
  void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;

  void sf_socket_read();
  void sf_socket_disconnect();
};

#endif  // SERVER_HPP
