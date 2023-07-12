/**
 *  \file CFile.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IO/IFile.h"

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \brief Абстрактный класс для файла в файловой системе.
   */
  class File : public IFile
  {
    public:
      [[nodiscard]] QString name() const override;
      void setName(const QString&) override;

      [[nodiscard]] QString extension() const override;
      void setExtension(const QString&) override;

      [[nodiscard]] QString fullName() const override;

      [[nodiscard]] QString absolutePath() const override;
      virtual void setAbsolutePath(const QString&);           ///< Задает абсолютный путь к файлу в файловой системе.

    protected:
      QString m_absolutePath;

    private:
      QString m_name;
      QString m_extension;
  };

  QString File::name() const { return m_name; }
  void File::setName(const QString& x) { m_name = x; }

  QString File::extension() const { return m_extension; }
  void File::setExtension(const QString& x) { m_extension = x; }

  QString File::fullName() const { return QString(m_name + "." + m_extension); }

  QString File::absolutePath() const { return m_absolutePath; }
  void File::setAbsolutePath(const QString& x) { m_absolutePath = x; }
} // QuasarSDK::IO