#include "pch.h"
#include "logger.h"
#include <vendor/imgui/imgui.h>

//Just had GPT to make this, love that thing man.

namespace Logger_c
{
    std::ofstream Logger::logFile("Avi\\Avi.log");
    std::mutex Logger::logMutex;

    Logger::Logger(const std::string& tag) : tag(tag)
    {
        // Optional: any initialization if needed
    }

    Logger::~Logger()
    {
        writeLog();
    }

    void Logger::writeLog()
    {
        std::lock_guard<std::mutex> lock(logMutex);

        std::string timestamp = getCurrentTime();
        std::string message = buffer.str();

        // Log to console
        std::cout << "[" << timestamp << "] [" << tag << "] " << message << std::endl;

        // Log to file
        if (logFile.is_open()) {
            logFile << "[" << timestamp << "] [" << tag << "] " << message << std::endl;
            logFile.flush();
        }
        else {
            std::cerr << "Error: Log file is not open!" << std::endl;
        }

        DebugWindow::PushLog("[" + timestamp + "] [" + tag + "] " + message);
    }

    std::string Logger::getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        struct tm localTime;

        localtime_s(&localTime, &now);

        std::ostringstream ss;
        ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    namespace {
        std::deque<std::string> logMessages;
        std::mutex logMutex;
        bool autoScroll = true;
    }

    namespace DebugWindow {

        void PushLog(const std::string& log) {
            std::lock_guard<std::mutex> lock(logMutex);
            logMessages.push_back(log);
        }

        void ClearLogs() {
            std::lock_guard<std::mutex> lock(logMutex);
            logMessages.clear();
        }

        void Render() {
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);

            ImGui::Begin("Debug Window", nullptr);

            if (ImGui::Button("Clear Logs")) {
                ClearLogs();
            }

            ImGui::SameLine();
            ImGui::Checkbox("Auto Scroll", &autoScroll);

            ImGui::BeginChild("LogOutput", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

            std::lock_guard<std::mutex> lock(logMutex);

            for (const auto& msg : logMessages) {
                ImGui::TextUnformatted(msg.c_str());
            }

            if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }

            ImGui::EndChild();
            ImGui::End();
        }
    }


} 
