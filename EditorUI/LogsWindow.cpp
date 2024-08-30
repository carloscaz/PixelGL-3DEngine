#include "LogsWindow.h"

#include "ImGui/imgui.h"

LogsWindow* LogsWindow::m_instance = nullptr;

LogsWindow::LogsWindow()
{
    m_logs.push_back("LogTest1");
}

LogsWindow* LogsWindow::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new LogsWindow();
    }

    return m_instance;
}

void LogsWindow::AddLog(const std::string& _log)
{
    m_logs.push_back(_log);
}

void LogsWindow::DrawWindow()
{
    ImGui::Begin("Log Window");
    ImGui::SameLine();
    if(ImGui::SmallButton("Clear Log"))
    {
        m_logs.clear();
    }

    ImGui::BeginChild("Logs", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
    for(const std::string& string : m_logs)
    {
        ImGui::Text(string.c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}
