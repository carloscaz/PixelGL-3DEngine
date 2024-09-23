#include "LogsWindow.h"

#include "Log.h"
#include "ImGui/imgui.h"

LogsWindow* LogsWindow::m_instance = nullptr;

LogsWindow::LogsWindow()
{
    
}

//Singleton patern
LogsWindow* LogsWindow::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new LogsWindow();
    }

    return m_instance;
}

void LogsWindow::AddLog(Log* _log)
{
    m_logs.push_back(_log);
}

//Draw ImGui logs window
void LogsWindow::DrawWindow()
{
    ImGui::Begin("Log Window");

    //Button to remove all logs
    ImGui::SameLine();
    if(ImGui::SmallButton("Clear Log"))
    {
        m_logs.clear();
    }
    
    ImGui::BeginChild("Logs", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
    for(Log* log : m_logs)
    {
        //If log is info, color white
        if(log->GetLogCategory() == logCategory::eInfoLog)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,255,255));
        }

        //If log is warning, color yellow
        else if(log->GetLogCategory() == logCategory::eWarningLog)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,0,255));
        }
        ImGui::Text(log->GetLogContent().c_str());
        ImGui::PopStyleColor();
    }

    //Scroll log window
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}
