#include "applicationheader.h"


ApplicationHeader::ApplicationHeader(QObject *parent) : QObject{parent} {}
void ApplicationHeader::close(void) { SignalLinker::get()->sendClose(); }
void ApplicationHeader::minimize(void) { SignalLinker::get()->sendMinimize(); }
void ApplicationHeader::log(void) { SignalLinker::get()->sendLog(); }
void ApplicationHeader::settings(void) { SignalLinker::get()->sendSettings(); }
void ApplicationHeader::info(void) { SignalLinker::get()->sendInfo(); }
void ApplicationHeader::emulator(void) { SignalLinker::get()->sendEmulator(); }