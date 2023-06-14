#pragma once

#include <vector>
#include <QtCore/QAbstractListModel>
#include <LPVL/Global>

using std::vector;

namespace GUI
{
    class WarningsModel : public QAbstractListModel
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(WarningsModel)

        struct WarningData {
            int type;
            QString msg;
            bool is_major;
        };

        public:
            enum Notification
            {
                NotConnected,
                Uncalibrated
            };
            Q_ENUM(Notification)

            enum ModelRoles
            {
                Index = Qt::UserRole + 1,
                Message,
                Major
            };

            int rowCount(const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role) const override;
            bool setData(const QModelIndex& index, const QVariant& value, int role) override;

            Q_INVOKABLE void append(int type, const QString& message, bool is_major);
            Q_INVOKABLE void remove(int type) noexcept;
            Q_INVOKABLE void clear();

        protected:
            QHash<int, QByteArray> roleNames() const override;

        private:
            WarningsModel(QObject* parent = nullptr);

        private:
            vector<WarningData> storage;
};
} // GUI

