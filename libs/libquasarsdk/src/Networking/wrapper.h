//
// Created by whs31 on 27.07.23.
//

#pragma once

#include <QtCore/QString>

namespace QuasarSDK::Utils
{
  /**
    * \brief Оборачивает строку в формат \c execd.
    * \details Добавляет уникальный ID, длину строки в
    * шестнадцатеричном формате и контрольную сумму CRC16
    * к указанной строке, разделяя это символом \c |.
    * \param string - строка для оборачивания.
    * \param uid_counter - указатель на счетчик. Если указатель не передан, номер сообщения будет равен единице.
    * \return UTF-8 данные для отправки в сокет.
    */
  QByteArray wrapToExecdString(const QString& string, int* uid_counter = nullptr) noexcept;
} // QuasarSDK::Utils
