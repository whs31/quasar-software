#pragma once
#include <QObject>

class ThemePrivate;
class Theme : public QObject
{
    Q_OBJECT
    public:
        explicit Theme(QObject *parent = nullptr);

        signals:

    protected:
        ThemePrivate* const d_ptr;

    private:
        Q_DECLARE_PRIVATE(Theme)
};
