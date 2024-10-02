#pragma once

namespace Logger_c
{
    class Logger
    {
    public:
        Logger(const std::string& tag = "INFO");
        ~Logger();

        template <typename T>
        Logger& operator<<(const T& message)
        {
            buffer << message;
            return *this;
        }

    private:
        std::string tag;
        std::ostringstream buffer;
        static std::ofstream logFile;
        static std::mutex logMutex;

        void writeLog();
        std::string getCurrentTime();
    };

    namespace DebugWindow {

        void Render();
        void PushLog(const std::string& log);
        void ClearLogs();
    }

}

#define LOG Logger()
#define LOG_TAG(tag) Logger(tag)

