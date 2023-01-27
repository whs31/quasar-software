#include "signallinker.h"

SignalLinker *SignalLinker::_instance = nullptr;
SignalLinker *SignalLinker::get(QObject *parent) { 
    if (_instance != NULL) return _instance;
    _instance = new SignalLinker(parent);
    return _instance;
} SignalLinker::SignalLinker(QObject *parent) : QObject{parent} {}

void SignalLinker::sendClose(void) { emit closeSignal(); }
void SignalLinker::sendMinimize(void) { emit minimizeSignal(); }
void SignalLinker::sendLog(void) { emit logSignal(); }
void SignalLinker::sendSettings(void) { emit settingsSignal(); }
void SignalLinker::sendInfo(void) { emit infoSignal(); }
void SignalLinker::sendEmulator(void) { emit emulatorSignal(); }

void SignalLinker::formSingleImage(void) { emit formSingleImageSignal(); }
void SignalLinker::clearSARStorage(void) { emit clearSARStorageSignal(); }