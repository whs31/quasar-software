#include "imguiconsole.h++"
#include "gui/theme/include/theme.h++"
#include <imgui/imgui.h>
#include <QtCore/QDebug>

using namespace Debug;

ImGuiConsole::ImGuiConsole(QObject *parent)
    : QObject{parent}
{
    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_WindowBg] = THEME->hexToFloatColor(THEME->color("dark0"));
    style->Colors[ImGuiCol_Text] = THEME->hexToFloatColor(THEME->color("light1"));
    style->Colors[ImGuiCol_TextDisabled] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_PopupBg] = THEME->hexToFloatColor(THEME->color("dark1"));
    style->Colors[ImGuiCol_Border] = THEME->hexToFloatColor(THEME->color("dark1"));
    style->Colors[ImGuiCol_BorderShadow] = THEME->hexToFloatColor(THEME->color("dark0"));
    style->Colors[ImGuiCol_FrameBg] = THEME->hexToFloatColor(THEME->color("dark1"));
    style->Colors[ImGuiCol_FrameBgHovered] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_FrameBgActive] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_TitleBg] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_TitleBgCollapsed] = THEME->hexToFloatColor(THEME->color("dark1"));
    style->Colors[ImGuiCol_TitleBgActive] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_ScrollbarBg] = THEME->hexToFloatColor(THEME->color("dark1"));
    style->Colors[ImGuiCol_ScrollbarGrab] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_ScrollbarGrabActive] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_SliderGrab] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_SliderGrabActive] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_Button] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_ButtonHovered] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_ButtonActive] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_Header] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_HeaderHovered] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_HeaderActive] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_ResizeGrip] = THEME->hexToFloatColor(THEME->color("dark3"));
    style->Colors[ImGuiCol_ResizeGripHovered] = THEME->hexToFloatColor(THEME->color("light0"));
    style->Colors[ImGuiCol_ResizeGripActive] = THEME->hexToFloatColor(THEME->color("dark2"));
    style->Colors[ImGuiCol_TextSelectedBg] = THEME->hexToFloatColor(THEME->color("accent"));

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
