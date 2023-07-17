#include "register.h"
#include "Networking/quasar_api.h"
#include "Networking/network_enums.h"
#include "IO/saroutputmodel.h"

// This block included only if Qt5/6::Quick linked to project.
#ifdef QT_QML_LIB
#include <QtQml/qqml.h>
#endif

namespace QuasarSDK
{
  void registerQMLTypes()
  {
    #ifdef QT_QML_LIB
    qmlRegisterSingletonInstance<QuasarAPI>("QuaSAR.API", 1, 0, "NetworkAPI", QuasarAPI::get());
    qmlRegisterUncreatableType<QuasarSDK::Enums>("QuaSAR.API", 1, 0, "Net", "Enumeration");
    qmlRegisterSingletonInstance<QuasarSDK::IO::SAROutputModel>("QuaSAR.API.Extras", 1, 0, "NetworkOutput", QuasarAPI::get()->outputModel());
    #endif
  }
} // QuasarSDK