/**
 *  \file CBasicFile.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IO/IFile.h"
#include <QtCore/QFileInfo>
#include <utility>

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \brief Абстрактный класс для **существующего** файла в файловой системе.
   */
  class BasicFile : public IFile
  {
    public:
      BasicFile();
      explicit BasicFile(QString path);

      [[nodiscard]] bool fileExists() const override;
      [[nodiscard]] QString filename() const override;
      [[nodiscard]] int fileSize() const override;
      [[nodiscard]] QString fileExtension() const override;
      [[nodiscard]] QString filenameWithExtension() const override;
      [[nodiscard]] QString absoluteFilePath() const override;

      void setAbsoluteFilePath(const QString& path) override;

    protected:
      QString m_absolute_path;
      QFileInfo m_info_provider;
  };

  BasicFile::BasicFile()
    : m_absolute_path(QString())
    , m_info_provider(QFileInfo())
  {}

  BasicFile::BasicFile(QString path)
    : m_absolute_path(std::move(path))
    , m_info_provider(m_absolute_path)
  {}

  bool BasicFile::fileExists() const { return m_info_provider.exists(); }
  QString BasicFile::filename() const { return m_info_provider.baseName(); }
  int BasicFile::fileSize() const { return static_cast<int>(m_info_provider.size()); }
  QString BasicFile::fileExtension() const { return m_info_provider.suffix(); }
  QString BasicFile::filenameWithExtension() const { return m_info_provider.fileName(); }
  QString BasicFile::absoluteFilePath() const { return m_absolute_path; }
  void BasicFile::setAbsoluteFilePath(const QString& path)
  {
    m_absolute_path = path;
    m_info_provider.setFile(path);
  }

} // QuasarSDK::IO