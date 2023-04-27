#include "imguiconsole.h++"
//#include "gui/theme/include/theme.h++"
#include <imgui/imgui.h>
#include <QtCore/QDebug>

using namespace Debug;

ImGuiConsole::ImGuiConsole(QObject *parent)
    : QObject{parent}
{
    //ImGui::GetStyle().FrameRounding = 12;
    for(int i = 0; i < 100; i++)
        telsockAppend("asd" + QString::number(i));
}

void ImGuiConsole::frame()
{
    ImGui::Begin("Telemetry Socket");
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_ReadOnly;

    ImGui::InputTextMultiline("##source", telsock_data.toLocal8Bit().data(), telsock_data.length() * sizeof(char), ImVec2(-FLT_MIN, ImGui::GetWindowHeight() - 34), flags);

    ImGui::ShowDemoWindow();
    ImGui::End();
}

void ImGuiConsole::telsockAppend(const QString& string)
{
    telsock_data.append(string + "\n");
}
