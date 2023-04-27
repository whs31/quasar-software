#include "imguiconsole.h++"
#include "gui/theme/include/theme.h++"
#include <imgui/imgui.h>
#include <QtCore/QDebug>

using namespace Debug;

ImGuiConsole::ImGuiConsole(QObject *parent)
    : QObject{parent}
{
}

void ImGuiConsole::frame()
{
    ImGui::Begin("Profiler menu");

    ImGui::End();
}
