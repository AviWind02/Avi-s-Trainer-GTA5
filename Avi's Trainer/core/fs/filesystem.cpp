#include "pch.h"

namespace core {
    namespace inihandler {

        void WriteStringToIni(const std::string& value, const std::string& file, const std::string& app, const std::string& key) {
            if (!WritePrivateProfileStringA(app.c_str(), key.c_str(), value.c_str(), file.c_str())) {
                LOG_TAG("WARN") << "Failed to write to INI file: " << file << " [Section: " << app << ", Key: " << key << "]";
            }
        }

        std::string ReadStringFromIni(const std::string& file, const std::string& app, const std::string& key) {
            char buf[100];
            GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, sizeof(buf), file.c_str());

            if (std::string(buf) == "NULL") {
                LOG_TAG("WARN") << "Key '" << key << "' or Section '" << app << "' not found in INI file: " << file;
            }

            return std::string(buf);
        }

        void WriteIntToIni(int value, const std::string& file, const std::string& app, const std::string& key) {
            WriteStringToIni(std::to_string(value), file, app, key);
        }

        int ReadIntFromIni(const std::string& file, const std::string& app, const std::string& key) {
            std::string valueStr = ReadStringFromIni(file, app, key);
            try {
                return std::stoi(valueStr);
            }
            catch (const std::invalid_argument& e) {
                LOG_TAG("WARN") << "Failed to convert value to int for Key '" << key << "' in INI file: " << file;
                return 0;
            }
        }

        void WriteFloatToIni(float value, const std::string& file, const std::string& app, const std::string& key) {
            WriteStringToIni(std::to_string(value), file, app, key);
        }

        float ReadFloatFromIni(const std::string& file, const std::string& app, const std::string& key) {
            std::string valueStr = ReadStringFromIni(file, app, key);
            try {
                return std::stof(valueStr);
            }
            catch (const std::invalid_argument& e) {
                LOG_TAG("WARN") << "Failed to convert value to float for Key '" << key << "' in INI file: " << file;
                return 0.0f;
            }
        }

        void WriteBoolToIni(bool value, const std::string& file, const std::string& app, const std::string& key) {
            WriteStringToIni(value ? "true" : "false", file, app, key);
        }

        bool ReadBoolFromIni(const std::string& file, const std::string& app, const std::string& key) {
            std::string value = ReadStringFromIni(file, app, key);
            if (value != "true" && value != "false") {
                LOG_TAG("WARN") << "Invalid boolean value for Key '" << key << "' in INI file: " << file;
            }
            return value == "true";
        }

    }
}