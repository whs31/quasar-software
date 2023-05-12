#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QList>

//! @brief      Логгер для кастомной имплементации консоли отладки.
//! @details        Сохраняет логи в отдельный файл, перенаправляет их в консоль отладки
//!                 и задает цвет для разных типов сообщений.

class ConsolePrivate;
class Console : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Console)

    public:
        explicit Console(QObject* parent = nullptr);

        //! @brief
        void append(const QString& message);

        //! @brief
        void sendCommand(const QString& command);

    protected:
        ConsolePrivate* const d_ptr;
};
