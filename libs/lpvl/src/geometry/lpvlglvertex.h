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

#include "LPVL/Global"

namespace LPVL
{
    struct LPVL_EXPORT Vertex
    {
        Vertex() : x(0), y(0) {}
        Vertex(float x, float y) : x(x), y(y) {}
        float x, y;
    };

    struct LPVL_EXPORT VertexT
    {
        VertexT() : x(0), y(0), u(0), v(0) {}
        VertexT(float x, float y, float u, float v) : x(x), y(y), u(u), v(v) {}
        VertexT(const Vertex &xy, float u, float v) : x(xy.x), y(xy.y), u(u), v(v) {}
        float x, y, u, v;
    };
} // LPVL
