/**
 *  \file CBase64Object.h
 *  \author Дмитрий Рязанцев
 *  \date 12.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once
#include <QtCore/QString>

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \brief Объект, способный конвертировать свои бинарные данные в base64-строку.
   */
  class Base64Object
  {
    public:
      /**
       * \brief Создает пустой Base64Object.
       */
      Base64Object();

      /**
       * \brief Создает Base64Object с указанным массивом данных.
       * \param data_array - массив данных объекта.
       */
      explicit Base64Object(QByteArray data_array);

      [[nodiscard]] QString base64() const;
      void setData(const QByteArray& non_b64_array) noexcept;

      /**
       * \brief Конвертирует произвольную последовательность данных в base64-строку.
       * \param data_array - данные для конвертации.
       * \return base64-строка.
       */
      static QString toBase64(const QByteArray& data_array) noexcept;

    private:
      QByteArray m_data;
      QString m_base64data;
  };
} // QuasarSDK::IO
