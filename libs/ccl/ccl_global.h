#pragma once

#include <QtCore/qglobal.h>

#if defined(CCL_LIBRARY)
    #define CCL_CORE_EXPORT Q_DECL_EXPORT
#else
    #define CCL_CORE_EXPORT Q_DECL_IMPORT
#endif
