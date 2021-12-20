#include "fontPlugin.h"

QFont FontPlugin::getFont()
{
   QFont font;
   return font.defaultFamily();
}
