#pragma once

#include <string>
#include "../external/loguru/loguru.hpp"

class Log
{
    public:
        Log();
        ~Log();

    public:
        void info(std::string s, ...);
        void warn(std::string s, ...);
        void error(std::string s, ...);
        void fatal(std::string s, ...);

    private:
        char *m_infoBuff;
        char *m_warnBuff;
        char *m_errorBuff;
        char *m_fatalBuff;
};