/**
 *  \file CMessageModel.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QAbstractListModel>
#include <memory>
#include <vector>
#include "IMessage.h"

using std::vector;
using std::unique_ptr;

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \ingroup sdk_models
   * \brief Базовый класс для модели сообщений.
   */
  class MessageModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Message,
        Type
      };

      explicit MessageModel(QObject* parent = nullptr);                                         ///< Создает новую модель сообщений с указанным родителем.

      [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;     ///< Возвращает количество элементов в модели.
      [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;           ///< Возвращает значение для указанной роли.
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;         ///< Устанавливает значение для указанной роли.

      /**
       * \brief Добавляет в модель новое сообщение.
       * \details Функция принимает **указатель**. Рекомендуется использовать <tt>make_unique</tt>.
       * \param message - указатель на новое сообщение.
       */
      void append(unique_ptr<IMessage> message);

      /**
       * \brief Очищает модель.
       * \note Эта функция может быть вызвана в QML через мета-объектную систему.
       */
      Q_INVOKABLE void clear();

    protected:
      [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    protected:
      vector<unique_ptr<IMessage>> m_storage;
  };
} // QuasarSDK::IO
