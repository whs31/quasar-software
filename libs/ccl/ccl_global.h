#pragma once

#include <QtCore/qglobal.h>

#if defined(CCL_LIBRARY)
    #define CCL_CORE_EXPORT Q_DECL_EXPORT
#else
    #define CCL_CORE_EXPORT Q_DECL_IMPORT
#endif

// class attributes
#define NO_COPY(name) private: name (const name&); name & operator=(const name &);
#define DEFINE_AS_SINGLETON(name) public: static name * get() { static name instance; return &instance; } private: NO_COPY(name)

// header definitions
#define QML_EXPOSE_INSTANCE(type, import_module, name, instance) qmlRegisterSingletonInstance<type>(import_module, 1, 0, name, instance);
#define QML_EXPOSE_INSTANTIABLE(type, import_module, name) qmlRegisterType<type>(import_module, 1, 0, name);

#define PROPERTY(type, name, setter, member) private: Q_PROPERTY(type name READ name WRITE setter NOTIFY name##Changed) public: type name () const { return member; } void setter(const type & t); private:
#define PROPERTY_DEF(type, name, setter, member) private: Q_PROPERTY(type name READ name WRITE setter NOTIFY name##Changed) public: type name () const { return member; } void setter(const type & t) { if(member == t) return; member = t; emit name##Changed(); } private:
#define PROPERTY_PTR(type, name, setter, member) private: Q_PROPERTY(type name READ name WRITE setter NOTIFY name##Changed) public: type name () const { return member; } void setter(type  t) { member = t; emit name##Changed(); } private:

// useful macro
#define unused_parameter(x) (void)x
#define deprecated_function(reason) __attribute__ ((deprecated( reason )))
