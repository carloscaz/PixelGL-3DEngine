#include "Log.h"

Log::Log(std::string& _message, logCategory _category) :
    m_message(_message),
    m_category(_category)
{}

std::string& Log::GetLogContent()
{
    return m_message;
}

logCategory Log::GetLogCategory()
{
    return m_category;
}
