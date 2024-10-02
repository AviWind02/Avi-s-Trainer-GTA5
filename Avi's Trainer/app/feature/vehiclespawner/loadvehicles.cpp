#include "pch.h"
#include "vehiclespawner.h"

namespace feature {
    namespace vehiclespawner {

        std::vector<VehicleInfo> g_vehicleList;



        const char* GetVehicleDisplayName(const char* hash)
        {
            Hash vehicleHash = rage::joaat(hash);
            const char* displayName = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicleHash);
            const char* vehicleDisplayName = HUD::_GET_LABEL_TEXT(displayName);

            if (std::string(vehicleDisplayName).find("NULL") != std::string::npos)
            {
                return hash;
            }

            return vehicleDisplayName;
        }

        std::optional<VehicleInfo> FetchVehicleInfo(const std::string& vehicleHash)
        {
            auto hash = rage::joaat(vehicleHash);

            if (!STREAMING::IS_MODEL_VALID(hash))
            {
                return std::nullopt;
            }

            VehicleInfo info;
            info.numSeats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(hash);
            info.vehicleHashName = vehicleHash;
            info.vehicleDisplayName = GetVehicleDisplayName(vehicleHash.c_str());
            info.maxSpeed = VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(hash);
            info.maxBraking = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING(hash);
            info.maxAcceleration = VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(hash);
            info.maxTraction = VEHICLE::GET_VEHICLE_MODEL_MAX_TRACTION(hash);
            info.maxDownforce = VEHICLE::_GET_VEHICLE_MODEL_ESTIMATED_AGILITY(hash);
            info.maxHandBraking = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(hash);
            info.maxHandBraking = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(hash);
            info.vehicleClass = VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(hash);
            return info;
        }

        bool loadVehiclInfo = true;
        void LoadVehicleWithInfo()
        {
            if (loadVehiclInfo)
            {
                std::string vehicleHashListPath = "Avi\\Vehicle\\vehiclehashlist.txt";;
                std::ifstream infile(vehicleHashListPath);

                if (!infile) {
                    LOG << "Failed to open vehicle hash list file: " << vehicleHashListPath;
                    return;
                }

                std::string line;
                int index = 0;
                while (std::getline(infile, line)) {
                    auto vehicleInfoOpt = FetchVehicleInfo(line.c_str());
                    if (vehicleInfoOpt.has_value()) {
                        VehicleInfo vehicleInfo = vehicleInfoOpt.value();
                        g_vehicleList.push_back(vehicleInfo);

                        std::string LoadedInfo = ("Vehicle Loaded: "
                            "Display name: " + std::string(vehicleInfo.vehicleDisplayName) +
                            " | Hash name: " + std::string(vehicleInfo.vehicleHashName) +
                            " | Class index: " + std::to_string(vehicleInfo.vehicleClass) +
                            " | INDEX: " + std::to_string(index));

                        LOG << LoadedInfo;
                        index++;
                    }
                    WAIT(0);
                }
            } loadVehiclInfo = false;
        }
    }
}