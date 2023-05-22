/* ---------------------------------------------------------------------
 * LPVL - Linear Algebra, Plotting and Visualisation Library
 * Copyright (C) 2023 whs31.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 * http://www.gnu.org/licenses.
 *
 * github.com/whs31/lpvl
 * ---------------------------------------------------------------------- */

#pragma once

#include <QtCore/QtGlobal>

#if defined LPVL_LIBRARY && !defined LPVL_STATIC
    #define LPVL_EXPORT Q_DECL_EXPORT
#elif !defined LPVL_LIBRARY && !defined LPVL_STATIC
    #define LPVL_EXPORT Q_DECL_IMPORT
#else
    #define LPVL_EXPORT
#endif

#define LPVL_DECLARE_NO_COPY(name) private: name (const name&); name & operator=(const name &);
#define LPVL_DECLARE_SINGLETON(name) public: static name * get() { static name instance; return &instance; } private: CSS_DECLARE_NO_COPY(name)
