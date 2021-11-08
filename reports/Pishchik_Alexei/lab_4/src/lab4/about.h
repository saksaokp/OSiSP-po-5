#ifndef ABOUT_H
#define ABOUT_H

#include "about_global.h"
#include <QDialog>

class ABOUT_EXPORT About : public QDialog
{
public:
    explicit About(QWidget *parent = nullptr);
    void on_info_programm_clicked();
};

#endif // ABOUT_H
