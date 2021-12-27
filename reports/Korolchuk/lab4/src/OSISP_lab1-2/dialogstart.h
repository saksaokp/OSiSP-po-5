#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QWidget>
#include <QDialog>

class dialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit dialogStart(QWidget *parent = nullptr);

    int lvl;
    QString operation;

private slots:
    void chooseLvlClicked();
    void checkUpdatesClicked();
};

#endif // DIALOGSTART_H
