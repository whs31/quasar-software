#include "applicationheader.h"


ApplicationHeader::ApplicationHeader(QObject *parent) : QObject{parent}
{
    connect(RuntimeData::get(), SIGNAL(windowLockChanged()), this, SLOT(emitWindowLockAliasChanged()));
}
void ApplicationHeader::close(void) { SignalLinker::get()->sendClose(); }
void ApplicationHeader::minimize(void) { SignalLinker::get()->sendMinimize(); }
void ApplicationHeader::log(void) { SignalLinker::get()->sendLog(); }
void ApplicationHeader::settings(void) { SignalLinker::get()->sendSettings(); }
void ApplicationHeader::info(void) { SignalLinker::get()->sendInfo(); }
void ApplicationHeader::emulator(void) { SignalLinker::get()->sendEmulator(); }

bool ApplicationHeader::getWindowLockAlias() const { return RuntimeData::get()->windowLock(); }
void ApplicationHeader::emitWindowLockAliasChanged() { emit windowLockAliasChanged(); }

QColor ApplicationHeader::getErrorDarkAlias() const { return ThemeManager::get()->getErrorDark(); }
QColor ApplicationHeader::getPrimaryDarkAlias() const { return ThemeManager::get()->getPrimaryDark(); }
QColor ApplicationHeader::getTextWhiteAlias() const { return ThemeManager::get()->getTextWhite(); }
