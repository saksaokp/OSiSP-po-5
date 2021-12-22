#pragma once

#ifndef ABOUT_HPP
#define ABOUT_HPP

#include "About_global.hpp"

#include <QMessageBox>

class ABOUT_EXPORT About {
 public:
  About();

  void f_show() const;

 private:
  QMessageBox* m_AboutBoxPtr;
};

#endif  // ABOUT_HPP
