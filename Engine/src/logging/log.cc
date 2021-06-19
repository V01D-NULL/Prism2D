#include "log.h"
#include <iostream>
#include "../external/loguru/loguru.hpp"
#include <stdarg.h>

Log::Log()
{
    //Specify logging options here
    this->m_infoBuff = new char[512];
    this->m_warnBuff = new char[512];
    this->m_errorBuff = new char[512];
    this->m_fatalBuff = new char[512];
}

void Log::info(std::string s, ...)
{
    LOG_SCOPE_FUNCTION(INFO);
    va_list ap;
    va_start(ap, s);
    vsnprintf(this->m_infoBuff, 512, s.c_str(), ap);
    LOG_F(INFO, this->m_infoBuff);
}

void Log::warn(std::string s, ...)
{
    LOG_SCOPE_FUNCTION(WARNING);
    va_list ap;
    va_start(ap, s);
    vsnprintf(this->m_warnBuff, 512, s.c_str(), ap);
    LOG_F(WARNING, this->m_warnBuff);
}

void Log::error(std::string s, ...)
{
    LOG_SCOPE_FUNCTION(ERROR);
    va_list ap;
    va_start(ap, s);
    vsnprintf(this->m_errorBuff, 512, s.c_str(), ap);
    LOG_F(ERROR, this->m_errorBuff);
}

void Log::fatal(std::string s, ...)
{
    LOG_SCOPE_FUNCTION(FATAL);
    va_list ap;
    va_start(ap, s);
    vsnprintf(this->m_fatalBuff, 512, s.c_str(), ap);
    LOG_F(FATAL, this->m_fatalBuff);
}

Log::~Log()
{
    delete[] this->m_infoBuff;
    delete[] this->m_warnBuff;
    delete[] this->m_errorBuff;
    delete[] this->m_fatalBuff;
}