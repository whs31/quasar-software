#include "internalconfig.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "config/paths.h"

namespace Config
{

InternalConfig *InternalConfig::get() { static InternalConfig instance; return &instance; }

InternalConfig::InternalConfig()
{
    QFile file(Config::Paths::config() + "/constants.json");
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray jsonData = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if(not doc.isNull() and doc.isObject())
            {
                QJsonObject json = doc.object();
                for(auto it = json.begin(); it != json.end(); ++it)
                    m_values.insert(it.key(), it.value().toVariant());
            }
        }
        return;
    }

    QJsonObject json;
    for(auto it = m_defaults.begin(); it != m_defaults.end(); ++it)
        json.insert(it.key(), QJsonValue::fromVariant(it.value()));

    QJsonDocument doc(json);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(doc.toJson());
        file.close();
    }

    m_values = m_defaults;
}

} // Config
