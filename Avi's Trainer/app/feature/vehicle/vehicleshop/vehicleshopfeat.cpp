#include "pch.h"
#include "vehicleshop.h"

namespace feature {
	namespace vehicleshop {

		std::optional<VehicleSpec> Spec;

		std::optional<VehicleSpec> FetchVehicleSpec(Vehicle vehicle)
		{
			VehicleSpec tempSpec;
			tempSpec.maxSpeed = VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle);
			tempSpec.maxBraking = VEHICLE::GET_VEHICLE_MAX_BRAKING(vehicle);
			tempSpec.maxAcceleration = VEHICLE::GET_VEHICLE_ACCELERATION(vehicle);
			tempSpec.maxTraction = VEHICLE::GET_VEHICLE_MAX_TRACTION(vehicle);
			Spec = tempSpec; 
			return Spec;
		}
	}
}