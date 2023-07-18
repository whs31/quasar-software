#pragma once

#include <QtCore/QString>
#include <utility>

class INameable
{
  public:
    INameable();
    explicit INameable(QString a_name);

    [[nodiscard]] QString name() const;
    virtual void setName(const QString& new_name);

  protected:
    QString m_name;
};

inline INameable::INameable()
  : m_name(QString())
{}

inline INameable::INameable(QString a_name)
  : m_name(std::move(a_name))
{}

inline QString INameable::name() const { return m_name; }
inline void INameable::setName(const QString& new_name) { m_name = new_name; }
