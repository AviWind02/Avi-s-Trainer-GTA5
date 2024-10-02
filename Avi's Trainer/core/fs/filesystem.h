#pragma once
namespace core {
    namespace inihandler {

        void WriteStringToIni(const std::string& value, const std::string& file, const std::string& app, const std::string& key);
        std::string ReadStringFromIni(const std::string& file, const std::string& app, const std::string& key);
        void WriteIntToIni(int value, const std::string& file, const std::string& app, const std::string& key);
        int ReadIntFromIni(const std::string& file, const std::string& app, const std::string& key);
        void WriteFloatToIni(float value, const std::string& file, const std::string& app, const std::string& key);
        float ReadFloatFromIni(const std::string& file, const std::string& app, const std::string& key);
        void WriteBoolToIni(bool value, const std::string& file, const std::string& app, const std::string& key);
        bool ReadBoolFromIni(const std::string& file, const std::string& app, const std::string& key);

    }
}