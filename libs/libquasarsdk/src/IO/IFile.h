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
      [[nodiscard]] virtual bool fileExists() const = 0;              ///< Валидность файла. Если функция вернула <tt>false</tt>, то остальные поля вернут пустую строку.
      [[nodiscard]] virtual QString filename() const = 0;             ///< Имя файла без расширения.
      [[nodiscard]] virtual int fileSize() const = 0;                 ///< Размер файла в байтах.
      [[nodiscard]] virtual QString fileExtension() const = 0;        ///< Расширение файла *без точки*.
      [[nodiscard]] virtual QString filenameWithExtension() const = 0;///< Полное имя файла с расширением.
      [[nodiscard]] virtual QString absoluteFilePath() const = 0;     ///< Абсолютный путь к файлу в файловой системе.

      /**
       * \brief Задает путь к реальному файлу в файловой системе.
       * \details Если путь корректный, то функция fileExists() вернет <tt>true</tt>.
       * \param path - путь к файлу.
       */
      virtual void setAbsoluteFilePath(const QString& path) = 0;
  };
} // QuasarSDK::IO