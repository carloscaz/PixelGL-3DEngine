#pragma once
#include <string>

enum logCategory
{
    eInfoLog,
    eWarningLog
};
class Log
{
private:
    std::string m_message;
    logCategory m_category;
public:
    Log(std::string& _message, logCategory _category);
    std::string& GetLogContent();
    logCategory GetLogCategory(); 
};
