#pragma once
namespace core {
    namespace pool {

        std::vector<Vehicle> GetAllVehicles();
        int GetVehicleCount();

        std::vector<Ped> GetAllPeds();
        int GetPedCount();

        std::vector<Object> GetAllObjects();
        int GetObjectCount();

        void PoolDebugMenu();
        void PoolDebugNative();
    }
}
