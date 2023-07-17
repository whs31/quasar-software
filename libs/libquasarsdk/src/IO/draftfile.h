/**
 *  \file CDraftFile.h
 *  \author Дмитрий Рязанцев
 *  \date 12.07.2023
 *  \copyright Radar-MMS 2023
 */

#include "IO/CBasicFile.h"

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \brief Класс, описывающий черновик файла - файл, который еще не был сохранен на диск, но готовится к этому.
   */
  class DraftFile : public BasicFile
  {
    public:
      DraftFile();                                                              ///< Создает пустой черновик файла.
      DraftFile(const QString& name, const QString& extension);                 ///< Создает черновик файла с указанным именем и расширением.

      [[nodiscard]] QString filename() const override;                          ///< Имя файла черновика (*без расширения*).
      [[nodiscard]] QString fileExtension() const override;                     ///< Расширение файла черновика.
      [[nodiscard]] QString filenameWithExtension() const override;             ///< Полное имя файла черновика с расширением.

      /**
       * \brief Сохраняет файл на диск по пути absoluteFilePath().
       * \details Имя и расширение сохраненного файла совпадает с параметрами filename() и fileExtension().
       *
       * Если сохранение не удалось, функция вернет <tt>false</tt>.
       * \param data_to_save - данные для сохранения.
       * \return Результат сохранения.
       */
      bool saveToDisk(const QByteArray& data_to_save) noexcept;

      /**
       * \brief Сохраняет файл в указанное место на диске.
       * \details Изменяет параметр absoluteFilePath(), если сохранение удалось.
       *
       * Если сохранение не удалось, функция вернет <tt>false</tt>.
       * \param path_to - путь, куда нужно сохранить файл.
       * \param data_to_save - данные для сохранения.
       * \return Результат сохранения.
       */
      bool saveToDisk(const QString& path_to, const QByteArray& data_to_save) noexcept;

      /**
       * \brief Удаляет сохраненный файл с диска.
       * \details Если файл еще не был сохранен, или удаление не удалось
       * по иной причине, функция вернет <tt>false</tt>.
       * \return Результат удаления.
       */
      bool removeFromDisk() noexcept;

    protected:
      struct filename_t
      {
        QString filename;
        QString extension;
      } m_filename;
  };
} // QuasarSDK::IO