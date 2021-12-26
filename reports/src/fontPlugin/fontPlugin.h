#ifndef FONTPLUGIN_H
#define FONTPLUGIN_H

#include <fontPluginInterface.h>

class FontPlugin : public QObject, public FontPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(FontPluginInterface)
    Q_PLUGIN_METADATA(IID "Sudoku.FontPluginInterface" FILE "fontPlugin.json")

public:
    virtual QFont getFont();
};

#endif // FONTPLUGIN_H
