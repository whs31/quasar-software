#include "FRegisterQML.h"
#include <QtQml/qqml.h>
#include "Utils/CColorProvider.h"

void Scenegraph::registerQMLTypes()
{
  qmlRegisterType<Scenegraph::Utils::ColorProvider>("Scenegraph.Legacy", 1, 0, "ColorProvider");
}