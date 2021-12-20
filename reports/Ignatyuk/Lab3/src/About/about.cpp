#include "about.hpp"

About::About()
    : m_AboutBoxPtr(new QMessageBox(
          QMessageBox::Information, "About",
          "Sapper v1.0\nAuthor: Andy\nCourse: 3\nSpeciality: S5",
          QMessageBox::Ok)) {}

void About::f_show() const { m_AboutBoxPtr->show(); }
