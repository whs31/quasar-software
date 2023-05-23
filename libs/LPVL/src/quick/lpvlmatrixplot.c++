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

#include "lpvlmatrixplot.h"
#include "LPVL/GLGeometry"
#include "LPVL/Math"
#include <QtQuick/QSGVertexColorMaterial>
#include <QtQuick/QSGGeometryNode>

namespace LPVL
{
    LPVL_REGISTER_QML("LPVLMatrixPlot", "LPVL.Charts");

    MatrixPlot::MatrixPlot(QQuickItem* parent)
        : QQuickItem{parent}
    {
        setFlag(ItemHasContents);
    }

    void MatrixPlot::set(const vector<float>& array2d, int rows, int columns)
    {
        data.clear();
        data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
            data[i].resize(columns);
            for(size_t j = 0; j < columns; ++j)
            data[i][j] = array2d[j + columns * i];
        }
        this->update();
    }

    void MatrixPlot::set(const vector<int> array2d, int rows, int columns)
    {
        data.clear();
        data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
            data[i].resize(columns);
            for(size_t j = 0; j < columns; ++j)
            data[i][j] = (float)array2d[j + columns * i];
        }
        this->update();
    }

    void MatrixPlot::set(const vector<uint8_t> array2d, int rows, int columns)
    {
        data.clear();
            data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
            data[i].resize(columns);
            for(size_t j = 0; j < columns; ++j)
                data[i][j] = (float)array2d[j + columns * i];
        }
        this->update();
    }

    QSGNode* MatrixPlot::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
    {
        QSGGeometry* geometry = nullptr;
        QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);
        if(node == nullptr)
        {
            node = new QSGGeometryNode;

            /*QSGSimpleMaterial<State>* material = new QSGFlatColorMaterial;*//*GLGradientShader::createMaterial();*/
            /*material->setFlag(QSGMaterial::Blending);*/
            QSGVertexColorMaterial* material = new QSGVertexColorMaterial;

            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
            /*static_cast<QSGSimpleMaterial<State>*>(node->material())->state()->color = QColor("red");*/

            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);
            node->setGeometry(geometry);
            node->setFlag(QSGNode::OwnsGeometry);
            geometry->setLineWidth(1);
            geometry->setDrawingMode(QSGGeometry::DrawPoints);
        }

        geometry = node->geometry();

        vector<VertexC> gl;
        float dx = width() / data.front().size();
        float dy = height() / data.size();
        for(size_t row = 0; row < data.size(); ++row)
        {
            for(size_t column = 0; column < data[row].size(); ++column)
            {
                gl.push_back(VertexC(column * dx, row * dy,
                                     data[row][column] * brightness() * tintRed(),
                                     data[row][column] * brightness() * tintGreen(),
                                     data[row][column] * brightness() * tintBlue(), 1));
                gl.push_back(VertexC(column * dx + dx, row * dy,
                                     data[row][column] * brightness() * tintRed(),
                                     data[row][column] * brightness() * tintGreen(),
                                     data[row][column] * brightness() * tintBlue(), 1));
                gl.push_back(VertexC(column * dx + dx, row * dy + dy,
                                     data[row][column] * brightness() * tintRed(),
                                     data[row][column] * brightness() * tintGreen(),
                                     data[row][column] * brightness() * tintBlue(), 1));
                gl.push_back(VertexC(column * dx, row * dy + dy,
                                     data[row][column] * brightness() * tintRed(),
                                     data[row][column] * brightness() * tintGreen(),
                                     data[row][column] * brightness() * tintBlue(), 1));
            }
        }

        geometry->allocate(gl.size());
        for(size_t i = 0; i < gl.size(); i++)
            geometry->vertexDataAsColoredPoint2D()[i].set(gl.at(i).x, gl.at(i).y,
                                                          gl.at(i).r, gl.at(i).g,
                                                          gl.at(i).b, gl.at(i).a);

        node->markDirty(QSGNode::DirtyGeometry);
        return node;
    }

    float MatrixPlot::tintRed() const { return m_tintRed; }
    void MatrixPlot::setTintRed(float other)
    {
        if (qFuzzyCompare(m_tintRed, other))
            return;
        m_tintRed = other;
        emit tintRedChanged();
        this->update();
    }

    float MatrixPlot::tintGreen() const { return m_tintGreen; }
    void MatrixPlot::setTintGreen(float other)
    {
        if (qFuzzyCompare(m_tintGreen, other))
            return;
        m_tintGreen = other;
        emit tintGreenChanged();
        this->update();
    }

    float MatrixPlot::tintBlue() const { return m_tintBlue; }
    void MatrixPlot::setTintBlue(float other)
    {
        if (qFuzzyCompare(m_tintBlue, other))
            return;
        m_tintBlue = other;
        emit tintBlueChanged();
        this->update();
    }

    float MatrixPlot::brightness() const { return m_brightness; }
    void MatrixPlot::setBrightness(float other)
    {
        if (qFuzzyCompare(m_brightness, other))
            return;
        m_brightness = other;
        emit brightnessChanged();
        this->update();
    }
} // LPVL
