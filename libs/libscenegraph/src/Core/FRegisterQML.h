/**
 *  \file FRegisterQML.h
 *  \author Дмитрий Рязанцев
 *  \date 11.07.2023
 *  \copyright Radar-MMS 2023
 */
#pragma once

namespace Scenegraph
{
  /**
   * \brief Регистрирует сущности класса в мета-системе QML.
   * \details Полный список сущностей по модулям приведен ниже:
   * <h3>Модуль Scenegraph 1.0</h3>
   * Импорт модуля:
   * \code {.py}
     import Scenegraph 1.0
   * \endcode
   *
   * <h3>Модуль Scenegraph.Extras 1.0</h3>
   * Импорт модуля:
   * \code {.py}
     import Scenegraph.Extras 1.0
   * \endcode
   *
   * <h3>Модуль Scenegraph.Legacy 1.0</h3>
   * Импорт модуля:
   * \code {.py}
     import Scenegraph.Legacy 1.0
   * \endcode
   *
   * - **ColorProvider** (Scenegraph::Utils::ColorProvider)
   */
  void registerQMLTypes();
} // Scenegraph
