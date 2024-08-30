#pragma once
#include <string>
#include <vector>

#include "GUIWindow.h"

class LogsWindow : public GUIWindow
{
private:
    static LogsWindow* m_instance;
    std::vector<std::string> m_logs;
    LogsWindow();
public:
    static LogsWindow* GetInstance();
    void AddLog(const std::string& _log);
    void DrawWindow() override;
};
