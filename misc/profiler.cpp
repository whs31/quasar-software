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
    float totalElapsed = 0;
    for(float f : operationTime)
    {
        totalElapsed += f;
    }
    for (size_t i = 0; i < operationName.length(); i++)
    {
        output.append(operationName[i] + ": ");
        output.append(QString::number(operationTime[i], 'f', 0) + " ms\n");
    }

    output.append("\nTotal elapsed time: " + QString::number(totalElapsed, 'f', 0) + " ms");
    
    if(SConfig::getHashBoolean("ShowProfiler"))
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