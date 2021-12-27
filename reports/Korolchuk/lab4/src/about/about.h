#ifndef ABOUT_H
#define ABOUT_H

#include "about_global.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>

class ABOUT_EXPORT About: public QDialog
{
public:
    About(QWidget* parent = nullptr);
};

#endif // ABOUT_H
