#pragma once

#ifndef UPDATER_HPP
#define UPDATER_HPP

#include <QTcpSocket>
#include <QWidget>

class Updater : public QObject {
  Q_OBJECT

 public:
  explicit Updater(QString& v_VersionLink,
                   QObject* const c_QObjectPtr = nullptr);
  ~Updater();

 public slots:
  void sf_process();
  void sf_socket_read();
  void sf_socket_disconnect();

 signals:
  void s_connecting();
  void s_can_not_connect();
  void s_up_to_date();
  void s_updated();
  void s_finished();

  void s_add_progress();
  void s_end_progress();

 private:
  QString& m_VersionLink;
  QTcpSocket* m_SocketPtr{nullptr};

  std::uint64_t m_LogCounter{};
  QString mc_Separator{",,,,,"};
};

#endif  // UPDATER_HPP
