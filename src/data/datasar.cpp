#include "datasar.h"

DataSAR *DataSAR::_instance = nullptr;
DataSAR *DataSAR::get(QObject *parent) { if (_instance != NULL) return _instance;
_instance = new DataSAR(parent); return _instance; }
DataSAR::DataSAR(QObject *parent) : QObject{parent} {}

qreal DataSAR::getFreeDiskSpace() const { return freeDiskSpace / (1000 * 1000); }
void DataSAR::setFreeDiskSpace(qreal value) { if (freeDiskSpace == value) return;
freeDiskSpace = value; emit freeDiskSpaceChanged(); }

qreal DataSAR::getTotalDiskSpace() const { return totalDiskSpace / (1000 * 1000); }
void DataSAR::setTotalDiskSpace(qreal value) { if (totalDiskSpace == value) return;
totalDiskSpace = value; emit totalDiskSpaceChanged(); }