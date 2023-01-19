#include "applicationheader.h"


ApplicationHeader::ApplicationHeader(QObject *parent) : QObject{parent} {}
void ApplicationHeader::close(void) { SignalLinker::get()->sendClose(); }