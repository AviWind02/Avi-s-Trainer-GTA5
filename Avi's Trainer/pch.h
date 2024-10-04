#pragma once

//SL
#include <cstdint>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <ranges>
#include <atomic>
#include <future>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <functional>
#include <unordered_map>
#include <stack>
#include <random>
#include <map>
#include <concepts>
#include <variant>
#include <string_view>

//APIs
#include <Windows.h>
#include <shlobj.h>
#include <wrl/client.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <winnt.h>
#include <winternl.h>
#include <sysinfoapi.h>
#include <dxgi.h>
#include <d3d11.h>

//ScriptHookV
#include "vendor/Script Hook V/inc/enums.h"
#include "vendor/Script Hook V/inc/natives.h"
#include "vendor/Script Hook V/inc/types.h"
#include "vendor/Script Hook V/inc/main.h"
#include "vendor/Script Hook V/inc/nativeCaller.h"

//Renderer for ImGui
#include "core/renderer/renderer.h"

//Core
#include "core/types/joaat.h"
#include "core/types/colour.h"
#include "core/logger/logger.h"
#include "core/memory/patterns.h"
#include "core/fs/filesystem.h"

//GUI
#include "GUI/controls/controls.h"
#include "GUI/buttons/buttons.h"

//Feat
//Global
#include "app/global/math/math.h"//Using App name space not really 'Features'
#include "app/global/player/player.h"
#include "app/global/entity/entity.h"
#include "app/global/vehicle/vehicle.h"
#include "app/global/weapon/weapon.h"


using namespace Logger_c;

inline std::string RemovePrefix(const std::string& string, const std::string prefix) {

    if (string.find(prefix) == 0) {
        return string.substr(prefix.length());
    }
    return string;
}

inline std::string ToLowerCase(const std::string& input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

inline bool FileExists(const std::string& filePath)
{
    std::ifstream file(filePath);
    return file.good();
}