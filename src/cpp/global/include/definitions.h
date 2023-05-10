#pragma once

// function attributes
#define __signal void
#define __slot
#define __deprecated __attribute__((deprecated))
#define __qml Q_INVOKABLE
#define __exposed __qml
#define __packed __attribute__((packed))
#define __global static inline
#define __concommand
#define __profile
#define __setter
#define __getter
#define __reserved [[maybe_unused]]
#define __unused __reserved

// class attributes
#define DECLARE_SINGLETON(x) private: static x * instance; public: static x * get(QObject* parent = nullptr);
#define DECLARE_SINGLETON_IMPL(x) x* x::instance = nullptr; x* x::get(QObject* parent) { if(instance != nullptr) return instance; instance = new x(parent); return instance; }

// useful macros
#define QML_EXPOSE_INSTANCE(type, import_module, name, instance) qmlRegisterSingletonInstance<type>(import_module, 1, 0, name, instance);
#define QML_EXPOSE_INSTANTIABLE(type, import_module, name) qmlRegisterType<type>(import_module, 1, 0, name);

