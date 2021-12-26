#include "fontPlugin.h"


QFont FontPlugin::getFont()
{
    QFont font("Helvetica", 7, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    font.setStretch(QFont::Expanded);
    return font ;
}


