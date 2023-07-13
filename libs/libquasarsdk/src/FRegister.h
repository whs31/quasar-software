/**
 *  \file FRegisterQML.h
 *  \author Дмитрий Рязанцев
 *  \date 13.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

namespace QuasarSDK
{
  /**
   * \brief Регистрирует сущности класса в мета-системе QML.
   * \details Полный список сущностей по модулям приведен ниже:
   * <h3>Модуль QuaSAR.API 1.0</h3>
   * Импорт модуля:
   * \code {.py}
     import QuaSAR.API 1.0
   * \endcode
   *
   * - Синглтон **NetworkAPI** (QuasarAPI)
   * - Перечисление **Net** (Enums)
   *
   * <h3>Модуль QuaSAR.API.Extras 1.0</h3>
   * Импорт модуля:
   * \code {.py}
     import QuaSAR.API.Extras 1.0
   * \endcode
   *
   * - Синглтон **NetworkOutput** (IO::SAROutputModel)
   */
  void registerQMLTypes();
} // QuasarSDK
