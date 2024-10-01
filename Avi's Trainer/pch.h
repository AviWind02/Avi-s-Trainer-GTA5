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
#include "Script Hook V/inc/enums.h"
#include "Script Hook V/inc/natives.h"
#include "Script Hook V/inc/types.h"
#include "Script Hook V/inc/main.h"
#include "Script Hook V/inc/nativeCaller.h"

//ImGui
#include "core/renderer/renderer.h"

//Core
#include "core/types/joaat.h"

//GUI
#include "GUI/controls/controls.h"
#include "GUI/buttons/buttons.h"

//Feat
//Global
#include "app/global/math/math.h"//Using App name space not really 'Features'
#include "app/global/player/player.h"
#include "app/global/entity/entity.h"
