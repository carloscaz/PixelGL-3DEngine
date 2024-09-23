#pragma once
#include <string>
#include <vector>

#include "GUIWindow.h"

class Log;
//ImGui window for logs of the engine
class LogsWindow : public GUIWindow
{
private:
    static LogsWindow* m_instance;
    std::vector<Log*> m_logs;
    LogsWindow();
public:
    static LogsWindow* GetInstance();
    void AddLog(Log* _log);
    void DrawWindow() override;
};
