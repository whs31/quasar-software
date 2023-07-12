/**
 *  \file IFile.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QString>

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \brief Интерфейс, описывающий абстрактный файл в файловой системе.
   */
  class IFile
  {
    public:
      [[nodiscard]] virtual QString name() const = 0;             ///< Возвращает имя файла без расширения.
      virtual void setName(const QString&) = 0;                   ///< Задает имя файла без расширения.

      [[nodiscard]] virtual QString extension() const = 0;        ///< Возвращает расширение файла *без точки*.
      virtual void setExtension(const QString&) = 0;              ///< Задает расширение файла *без точки*.

      [[nodiscard]] virtual QString fullName() const = 0;         ///< Возвращает полное имя файла с расширением.
      [[nodiscard]] virtual QString absolutePath() const = 0;     ///< Возвращает абсолютный путь к файлу в файловой системе.
  };
} // QuasarSDK::IO