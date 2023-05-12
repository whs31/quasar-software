#pragma once

// function attributes
#define __signal void
#define __property_signal void
#define __exposed Q_INVOKABLE
#define __packed __attribute__((packed))
#define __global static inline
#define __async

#ifdef W_ATTRIBUTES
#define __reserved [[maybe_unused]]
#else
#define __reserved
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
