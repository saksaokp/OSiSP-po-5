#include "helperclass.hpp"

#include <QMouseEvent>

PushButton::PushButton(const std::uint64_t& c_Index,
                       QPushButton* const c_PushButtonPtr,
                       const QString& c_Text)
    : QPushButton(c_PushButtonPtr), m_Index(c_Index) {
  setMinimumSize(PushButton::c_BUTTON_SIZE, PushButton::c_BUTTON_SIZE);
  setMaximumSize(PushButton::c_BUTTON_SIZE, PushButton::c_BUTTON_SIZE);
  setText(c_Text);
}

std::uint64_t PushButton::f_get_index() const { return m_Index; }

std::uint64_t PushButton::f_get_icon_index() const { return m_IconIndex; }

bool PushButton::f_is_flag() { return m_IconIndex == 1; }

void PushButton::f_clear() {
  m_IconIndex = std::uint64_t{};
  setFlat(false);
  setIcon(QIcon());
}

void PushButton::mousePressEvent(QMouseEvent* const event) {
  switch (event->button()) {
    case Qt::RightButton: {
      if (isFlat()) {
        return;
      }

      ++m_IconIndex;

      if (m_IconIndex > 2) {
        m_IconIndex -= 3;
      }

      emit right_clicked(m_Index);
      break;
    }
    case Qt::LeftButton: {
      if (m_IconIndex != 0) {
        return;
      }

      emit left_clicked(m_Index);
      break;
    }
    default: {}
  }
}
