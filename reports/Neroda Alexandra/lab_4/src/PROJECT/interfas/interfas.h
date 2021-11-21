#ifndef interfas_H
#define interfas_H

#include <QObject>
#include <interface_theme.h>

class interfas : public QObject, public Interface_theme
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "mp3.Interface_theme" FILE "Interface_theme.json")
    Q_INTERFACES(Interface_theme)
public:
    interfas(QObject *parent =0);
    ~interfas();
    QString name();
    virtual QPalette changeInterfase();
};

#endif // interfas_H
