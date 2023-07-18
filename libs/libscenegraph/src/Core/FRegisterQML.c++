#include "FRegisterQML.h"
#include <QtQml/qqml.h>
#include "Utils/CColorProvider.h"

void Scenegraph::registerQMLTypes()
{
  qmlRegisterModule("Scenegraph.Legacy", 1, 0);
  qmlRegisterType<Scenegraph::Utils::ColorProvider>("Scenegraph.Legacy", 1, 0, "ColorProvider");
}