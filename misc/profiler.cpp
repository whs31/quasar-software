#include "profiler.h"

Profiler::Profiler(QString profilerName) : header(profilerName)
{ 
    timer = new QElapsedTimer();
}

void Profiler::Start()
{
    timer->restart();
}

void Profiler::Stop(QString name)
{
    float elapsed = timer->elapsed();
    SaveProfile(name, elapsed);
}

void Profiler::ShowProfile()
{
    QString output = "";
    for (size_t i = 0; i < operationName.length(); i++)
    {
        output.append(operationName[i] + ": ");
        output.append(QString::number(operationTime[i], 'f', 1) + " ms\n");
    }
    
    if(SConfig::USEPROFILER)
    {
        QMessageBox openSSLDialogue;
            openSSLDialogue.setWindowTitle(header);
            openSSLDialogue.setIcon(QMessageBox::Icon::Information);
            openSSLDialogue.setText(output);
            openSSLDialogue.exec();
    }
    operationName.clear();
    operationTime.clear();
}

void Profiler::SaveProfile(QString name, float elapsed)
{
    operationName.append(name);
    operationTime.append(elapsed);
}