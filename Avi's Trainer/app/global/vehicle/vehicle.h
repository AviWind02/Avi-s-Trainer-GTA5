#pragma once
namespace g_feature {
    namespace g_vehicle {

        Vehicle Spawn(const char* vehicleHash, Vector3 pos, float dir);

        Vector3 GetVehicleCoords();

        void DeletePlayerVehicle(Ped playerPed);
        void AdjustSpawnPositionForAir(const char* vehicleHash, Vector3& spawnPos);
        void SetVehicleExtraColors(Vehicle vehicle, bool setPrimaryColor, bool setSecondaryColor, int pickedColorIndex);
        void SetCustomVehicleColor(Vehicle vehicle, bool setCustomPrimaryColor, bool setCustomSecondaryColor, Vector3 customColor);
        void SetVehicleColors(Vehicle vehicle, bool setPrimaryColor, bool setSecondaryColor, int pickedColorIndex);
        void GetVehicleExtraColors(Vehicle vehicle, int& primaryColorIndex, int& secondaryColorIndex);
        void GetVehicleColors(Vehicle vehicle, int& primaryColorIndex, int& secondaryColorIndex);
        void SetNeonLightsColor(Vehicle vehicle, bool enableNeon, int red, int green, int blue);
    }
}