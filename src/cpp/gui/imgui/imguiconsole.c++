#include "imguiconsole.h++"
#include <imgui/imgui.h>
#include <QtCore/QDebug>

using namespace Debug;

ImGuiConsole::ImGuiConsole(QObject *parent)
    : QObject{parent}
{

}

void ImGuiConsole::frame()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_Text] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_Border] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_Button] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_Header] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.125, 0.137, 0.161, 0.9);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.125, 0.137, 0.161, 0.9);

    ImGui::Begin("DEBUG CONSOLE");

    ImGui::End();
}
