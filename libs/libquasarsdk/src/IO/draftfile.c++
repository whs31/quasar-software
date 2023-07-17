#include "IO/CDraftFile.h"
#include <QtCore/QFile>
#include <QtCore/QDebug>

namespace QuasarSDK::IO
{

  DraftFile::DraftFile()
    : BasicFile()
    , m_filename({QString(), QString()})
  {}

  DraftFile::DraftFile(const QString& name, const QString& extension)
    : BasicFile()
    , m_filename({name, extension})
  {}

  QString DraftFile::filename() const { return m_filename.filename; }
  QString DraftFile::fileExtension() const { return m_filename.extension; }
  QString DraftFile::filenameWithExtension() const { return (m_filename.filename + "." + m_filename.extension); }

  bool DraftFile::saveToDisk(const QByteArray& data_to_save) noexcept
  {
    if(BasicFile::absoluteFilePath().isEmpty())
    {
      qWarning() << "[DRAFT FILE] Tried to save file to empty path";
      return false;
    }

    QFile file(BasicFile::absoluteFilePath());
    if(not file.open(QIODevice::WriteOnly))
    {
      qWarning() << "[DRAFT FILE] Failed to open file" << filenameWithExtension() << "at" << BasicFile::absoluteFilePath();
      return false;
    }
    file.write(data_to_save);
    file.close();

    qDebug() << "[DRAFT FILE] Saved" << filenameWithExtension() << "to" << BasicFile::absoluteFilePath();
    return true;
  }

  bool DraftFile::saveToDisk(const QString& path_to, const QByteArray& data_to_save) noexcept
  {
    if(path_to.isEmpty())
    {
      qWarning() << "[DRAFT FILE] Tried to save file to empty path";
      return false;
    }

    QFile file(path_to);
    if(not file.open(QIODevice::WriteOnly))
    {
      qWarning() << "[DRAFT FILE] Failed to open file" << filenameWithExtension() << "at" << path_to;
      return false;
    }
    file.write(data_to_save);
    file.close();

    qDebug() << "[DRAFT FILE] Saved" << filenameWithExtension() << "to" << path_to;
    return true;
  }

  bool DraftFile::removeFromDisk() noexcept
  {
    qDebug() << "[DRAFT FILE] Deleted" << filenameWithExtension() << "from" << BasicFile::absoluteFilePath();
    return QFile::remove(BasicFile::absoluteFilePath());
  }
} // QuasarSDK::IO