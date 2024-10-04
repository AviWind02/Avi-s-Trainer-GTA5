#pragma once

namespace feature {
	namespace vehiclespawner
	{
		inline const std::vector<std::string> g_vehicleCategories = {
            "Compact Cars",
            "Sedan Cars",
            "SUVs",
            "Coupe Cars",
            "Muscle Cars",
            "Classic Sports Cars",
            "Sports Cars",
            "Super Cars",
            "Motorcycles",
            "Off-Road Vehicles",
            "Industrial Vehicles",
            "Utility Vehicles",
            "Vans",
            "Bicycles",
            "Boats",
            "Helicopters",
            "Airplanes",
            "Service Vehicles",
            "Emergency Vehicles",
            "Military Vehicles",
            "Commercial Vehicles",
            "Trains",
            "Open-Wheel Race Cars",
            "All-Vehicles"
		};

        struct VehicleInfo
        {
            std::string vehicleDisplayName;
            int numSeats;
            float maxSpeed;
            float maxBraking;
            float maxAcceleration;
            float maxTraction;
            float maxDownforce;
            float maxHandBraking;
            int vehicleClass;
            std::string vehicleHashName;
        };
        
        extern bool loadVehiclInfo;
        // Need to set loadVehiclInfo to re load them
        void LoadVehicleWithInfo();
        extern std::vector<VehicleInfo> g_vehicleList;

        void PickedVehicleView();
        void VehicleSpawnView();
	}
}