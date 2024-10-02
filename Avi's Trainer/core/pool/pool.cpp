#include "pch.h"
#include "pool.h"
#include <vendor/imgui/imgui.h>

namespace core {
    namespace pool {

        std::vector<Vehicle> GetAllVehicles() {
            const int ARR_SIZE = 1024;
            Vehicle vehicles[ARR_SIZE];
            int count = worldGetAllVehicles(vehicles, ARR_SIZE);
            std::vector<Vehicle> vehicleList(vehicles, vehicles + count);
            return vehicleList;
        }

        int GetVehicleCount() {
            const int ARR_SIZE = 1024;
            Vehicle vehicles[ARR_SIZE];
            return worldGetAllVehicles(vehicles, ARR_SIZE);
        }

        std::vector<Ped> GetAllPeds() {
            const int ARR_SIZE = 1024;
            Ped peds[ARR_SIZE];
            int count = worldGetAllPeds(peds, ARR_SIZE);
            std::vector<Ped> pedList(peds, peds + count);
            return pedList;
        }

        int GetPedCount() {
            const int ARR_SIZE = 1024;
            Ped peds[ARR_SIZE];
            return worldGetAllPeds(peds, ARR_SIZE);
        }

        std::vector<Object> GetAllObjects() {
            const int ARR_SIZE = 1024;
            Object objects[ARR_SIZE];
            int count = worldGetAllObjects(objects, ARR_SIZE);
            std::vector<Object> objectList(objects, objects + count);
            return objectList;
        }

        int GetObjectCount() {
            const int ARR_SIZE = 1024;
            Object objects[ARR_SIZE];
            return worldGetAllObjects(objects, ARR_SIZE);
        }

        int vehiclePool, pedPool, objPool;

        void PoolDebugNative()
        {
            vehiclePool = GetVehicleCount();
            pedPool = GetPedCount();
            objPool = GetObjectCount();
        }


        void PoolDebugMenu()
        {
            ImGui::Begin("Game Pool");
            ImGui::Separator();
            ImGui::Text("Vehicle Pool: %d", vehiclePool);
            ImGui::Text("Ped Pool: %d", pedPool);
            ImGui::Text("Object Pool: %d", objPool);
            ImGui::End();
        }
    }
}
