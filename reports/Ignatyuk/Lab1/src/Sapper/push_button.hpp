#pragma once

#ifndef PUSH_BUTTON_HPP
#define PUSH_BUTTON_HPP

#include <QPushButton>

class PushButton : public QPushButton {
  Q_OBJECT

 public:
  PushButton(const std::uint64_t& c_Index = std::uint64_t{},
    QPushButton* const c_PushButtonPtr = nullptr, const QString& c_Text = QString{});

  static constexpr std::uint64_t c_BUTTON_SIZE{25};

  std::uint64_t f_get_index() const;
  std::uint64_t f_get_icon_index() const;

  void f_set_index(const std::uint64_t& c_Index);

  bool f_is_flag();
  void f_clear();

 private:
  std::uint64_t m_Index{};
  std::uint64_t m_IconIndex{};

  void mousePressEvent(QMouseEvent* const event);

 signals:
  void left_clicked(const std::uint64_t&);
  void right_clicked(const std::uint64_t&);
  void middle_clicked(const std::uint64_t&);
};

#endif  // PUSH_BUTTON_HPP
