#include "imguiconsole.h++"
//#include "gui/theme/include/theme.h++"
#include <imgui/imgui.h>
#include <QtCore/QDebug>

using namespace Debug;

int ImGuiConsole::skip_frames = 0;
ImGuiConsole::ImGuiConsole(QObject *parent)
    : QObject{parent}
{

}

void ImGuiConsole::frame()
{
    if(set_up == false)
        setup();

    ImGui::SetNextWindowSize(ImVec2(525, 500), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiCond_FirstUseEver);
    ImGui::Begin("Execd Socket");
    {
        const int size_of_graph = 100;

        ImGui::InputTextMultiline("ExecdsockData", execdsock_data.toLocal8Bit().data(), execdsock_data.length() * sizeof(char),
                                  ImVec2(-FLT_MIN, ImGui::GetWindowHeight() - 34 - size_of_graph), ImGuiInputTextFlags_ReadOnly);

        if(skip_frames == 9)
        {
            for(size_t i = 1; i < GRAPH_SIZE; ++i)
                execdsock_graph_data[i-1] = execdsock_graph_data[i];

            if(execdsock_load_size)
            {
                execdsock_graph_data[GRAPH_SIZE - 1] = execdsock_load_size;
                execdsock_load_size = 0;
            }
            else
                execdsock_graph_data[GRAPH_SIZE - 1] = execdsock_load_size;
        }

        ImGui::PlotHistogram("", execdsock_graph_data, GRAPH_SIZE,
                             0, "Network Load (bytes)", FLT_MIN, 256, ImVec2(ImGui::GetWindowWidth(), size_of_graph));
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(520, 500), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(530, 5), ImGuiCond_FirstUseEver);
    ImGui::Begin("Feedback Socket");
    {
        const int size_of_graph = 100;

        ImGui::InputTextMultiline("FeedbacksockData", feedbacksock_data.toLocal8Bit().data(), feedbacksock_data.length() * sizeof(char),
                                  ImVec2(-FLT_MIN, ImGui::GetWindowHeight() - 34 - size_of_graph), ImGuiInputTextFlags_ReadOnly);

        if(skip_frames == 9)
        {
            for(size_t i = 1; i < GRAPH_SIZE; ++i)
                feedbacksock_graph_data[i-1] = feedbacksock_graph_data[i];

            if(feedbacksock_load_size)
            {
                feedbacksock_graph_data[GRAPH_SIZE - 1] = feedbacksock_load_size;
                feedbacksock_load_size = 0;
            }
            else
                feedbacksock_graph_data[GRAPH_SIZE - 1] = feedbacksock_load_size;
        }

        ImGui::PlotHistogram("", feedbacksock_graph_data, GRAPH_SIZE,
                             0, "Network Load (bytes)", FLT_MIN, 256, ImVec2(ImGui::GetWindowWidth(), size_of_graph));
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(860, 500), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(1055, 5), ImGuiCond_FirstUseEver);
    ImGui::Begin("Telemetry Socket");
    {
        const int size_of_graph = 100;

        ImGui::InputTextMultiline("TelsockData", telsock_data.toLocal8Bit().data(), telsock_data.length() * sizeof(char),
                              ImVec2(-FLT_MIN, ImGui::GetWindowHeight() - 34 - size_of_graph), ImGuiInputTextFlags_ReadOnly);

        if(skip_frames++ == 9)
        {
            for(size_t i = 1; i < GRAPH_SIZE; ++i)
                telsock_graph_data[i-1] = telsock_graph_data[i];

            if(telsock_load_size)
            {
                telsock_graph_data[GRAPH_SIZE - 1] = telsock_load_size;
                telsock_load_size = 0;
            }
            else
                telsock_graph_data[GRAPH_SIZE - 1] = telsock_load_size;

          skip_frames = 0;
        }

        ImGui::PlotHistogram("", telsock_graph_data, GRAPH_SIZE,
                            0, "Network Load (bytes)", FLT_MIN, 256, ImVec2(ImGui::GetWindowWidth(), size_of_graph));
    }
    ImGui::End();

    //!@todo Save theme. TCP Socket. Image decoding window.
}

void ImGuiConsole::telsockAppend(const QString& string)
{
    telsock_data.prepend(string + "\n");
    telsock_load_size = string.size() * sizeof(char);
    if(telsock_data.size() > INT_MAX / 2)
    {
        telsock_data.clear();
        telsock_data.append("Socket console was cleared because of buffer overflow. \r\n");
    }
}

void ImGuiConsole::execdsockAppend(const QString& string)
{
    execdsock_data.prepend(string + "\n");
    execdsock_load_size = string.size() * sizeof(char);
    if(execdsock_data.size() > INT_MAX / 2)
    {
        execdsock_data.clear();
        execdsock_data.append("Socket console was cleared because of buffer overflow. \r\n");
    }
}

void ImGuiConsole::feedbacksockAppend(const QString& string)
{
    feedbacksock_data.prepend(string + "\n");
    feedbacksock_load_size = string.size() * sizeof(char);
    if(feedbacksock_data.size() > INT_MAX / 2)
    {
        feedbacksock_data.clear();
        feedbacksock_data.append("Socket console was cleared because of buffer overflow. \r\n");
    }
}

void ImGuiConsole::tcpsockAppend(const QString& string)
{
    tcpsock_data.prepend(string + "\n");
    tcpsock_load_size = string.size() * sizeof(char);
    if(tcpsock_data.size() > INT_MAX / 2)
    {
        tcpsock_data.clear();
        tcpsock_data.append("Socket console was cleared because of buffer overflow. \r\n");
    }
}

void ImGuiConsole::setup()
{
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_MenuBarBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Border
    colors[ImGuiCol_Border] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_BorderShadow] = ImVec4{0.0f, 0.0f, 0.0f, 0.24f};

    // Text
    colors[ImGuiCol_Text] = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
    colors[ImGuiCol_TextDisabled] = ImVec4{0.5f, 0.5f, 0.5f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_CheckMark] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{0.1f, 0.1f, 0.13f, 0.92f};

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{0.44f, 0.37f, 0.61f, 0.54f};
    colors[ImGuiCol_SliderGrabActive] = ImVec4{0.74f, 0.58f, 0.98f, 0.54f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.13f, 0.13, 0.17, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.24, 0.24f, 0.32f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.2f, 0.22f, 0.27f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{0.24f, 0.24f, 0.32f, 1.0f};

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
    colors[ImGuiCol_SeparatorActive] = ImVec4{0.84f, 0.58f, 1.0f, 1.0f};

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{0.74f, 0.58f, 0.98f, 0.29f};
    colors[ImGuiCol_ResizeGripActive] = ImVec4{0.84f, 0.58f, 1.0f, 0.29f};

    colors[ImGuiCol_PlotLines] = ImVec4(0.816, 0.529, 0.439, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.716, 0.329, 0.339, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.816, 0.529, 0.439, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.716, 0.329, 0.339, 1.00f);

    auto &style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;

    auto& io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.LogFilename = NULL;
}
