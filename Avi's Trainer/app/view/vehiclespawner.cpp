#include "pch.h"
#include "app/feature/vehicle/vehiclespawner/vehiclespawner.h"
namespace view {
    namespace vehiclespawner {
        using namespace g_feature;

        bool deleteLastVehicleOnSpawn = true;
        bool wrapPlayerInVehicleOnSpawn = true;
        bool wrapPlayerVehicleInAirOnSpawn = true;

        float vehicleSpawnDis = 5.f;

        Vehicle spawnvehicle(const char* vehicleHash) {
            Player player = g_player::GetPlayerPed();
            Vector3 playerLoc = g_player::GetCoordsInFrontOfPlayer(player, vehicleSpawnDis);
            if (deleteLastVehicleOnSpawn)  g_vehicle::DeletePlayerVehicle(player);
            if (wrapPlayerVehicleInAirOnSpawn) g_vehicle::AdjustSpawnPositionForAir(vehicleHash, playerLoc);
            Vehicle vehicle = g_vehicle::Spawn(vehicleHash, playerLoc, g_player::GetPlayerDir());
            if (wrapPlayerInVehicleOnSpawn)  g_player::SeatPlayerInVehicle(player, vehicle);
            return vehicle;
        }

        int selectedClass = 0;
        const int maxLength = 32;
        char userInput[maxLength] = { 0 };

        void VehicleSpawnView() {//Left this view here for now Move into View folder later
            GUI::menu::SetSubTitle("Vehicle Spawner Menu");


            GUI::buttons::Toggle("Delete Last vehicle", &deleteLastVehicleOnSpawn);
            GUI::buttons::Toggle("Wrap Player into Vehcice", &wrapPlayerInVehicleOnSpawn);
            GUI::buttons::Toggle("Spawn Air vehicles in the Air", &wrapPlayerVehicleInAirOnSpawn);
            
            GUI::buttons::Break(NULL, "Vehicle Classes");

            if (GUI::buttons::Sub("All Vehicles", pages::VehicleSpawner_Picked_page)) {
                selectedClass = 23;
            }

            for (int i = 0; i < feature::vehiclespawner::g_vehicleCategories.size(); ++i) {
                if (GUI::buttons::Sub(feature::vehiclespawner::g_vehicleCategories[i].c_str(), pages::VehicleSpawner_Picked_page)) {
                    selectedClass = i;
                }
            }
        }

        void PickedVehicleView() {

            GUI::menu::SetSubTitle(feature::vehiclespawner::g_vehicleCategories[selectedClass].c_str());

             static bool BLANK = false;
             if (selectedClass == 23) {
                 GUI::buttons::OptionInput("Search Vehicle: ", userInput, maxLength, &BLANK);
             }

             for (const auto& vehicle : feature::vehiclespawner::g_vehicleList) {
                 if (selectedClass == 23) {
                     std::string vehicleNameLower = vehicle.vehicleDisplayName;
                     std::string userInputLower = userInput;
                     std::transform(vehicleNameLower.begin(), vehicleNameLower.end(), vehicleNameLower.begin(), ::tolower);
                     std::transform(userInputLower.begin(), userInputLower.end(), userInputLower.begin(), ::tolower);

                     if (userInputLower.empty() || vehicleNameLower.find(userInputLower) != std::string::npos) {
                         if (GUI::buttons::Option(vehicle.vehicleDisplayName.c_str())) {
                             spawnvehicle(vehicle.vehicleHashName.c_str());
                         }
                     }
                 }
                 else if (vehicle.vehicleClass == selectedClass) {
                     if (GUI::buttons::Option(vehicle.vehicleDisplayName.c_str())) {
                        spawnvehicle(vehicle.vehicleHashName.c_str());
                     }
                 }
             }
        }

    }
}