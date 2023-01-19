#include "signallinker.h"

SignalLinker *SignalLinker::_instance = nullptr;
SignalLinker *SignalLinker::get(QObject *parent) { 
    if (_instance != NULL) return _instance;
    _instance = new SignalLinker(parent);
    return _instance;
} SignalLinker::SignalLinker(QObject *parent) : QObject{parent} {}

void SignalLinker::sendClose(void) { emit closeSignal(); }