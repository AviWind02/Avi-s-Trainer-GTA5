#include "pch.h"

namespace feature {
	namespace g_vehicle {

		Vehicle Spawn(const char* vehicleHash, Vector3 pos, float dir) {
			auto hash = rage::joaat(vehicleHash);

			if (!STREAMING::IS_MODEL_VALID(hash) &&
				!STREAMING::IS_MODEL_A_VEHICLE(hash))
				return NULL;
			do
			{
				STREAMING::REQUEST_MODEL(hash);
				WAIT(0);
			} while (!STREAMING::HAS_MODEL_LOADED(hash));


			return VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, dir, true, true, NULL);

		}

		void DeletePlayerVehicle(Ped playerPed) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				Vehicle V = g_player::GetPlayerVehicle(playerPed);
				if (ENTITY::DOES_ENTITY_EXIST(V)) {
					NETWORK::NETWORK_FADE_OUT_ENTITY(V, 1, 0);
					ENTITY::DELETE_ENTITY(&V);
				}
			}
		}

		void AdjustSpawnPositionForAir(const char* vehicleHash, Vector3& spawnPos) {
			auto hash = rage::joaat(vehicleHash);

			if (VEHICLE::IS_THIS_MODEL_A_HELI(hash) || VEHICLE::IS_THIS_MODEL_A_PLANE(hash)) {
				spawnPos.z = 525.f;
			}
		}


		Vector3 GetVehicleCoords() {
			if (PED::IS_PED_IN_ANY_VEHICLE(g_player::GetPlayerPed(), 0)) {
				Vehicle V = g_player::GetPlayerVehicle();
				if (ENTITY::DOES_ENTITY_EXIST(V)) {
					return ENTITY::GET_ENTITY_COORDS(V, false);
				}
			}
		}


		void SetVehicleExtraColors(Vehicle vehicle, bool setPrimaryColor, bool setSecondaryColor, int pickedColorIndex) {
			int currentPrimaryColorIndex, currentSecondaryColorIndex;
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &currentPrimaryColorIndex, &currentSecondaryColorIndex);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, setPrimaryColor ? pickedColorIndex : currentPrimaryColorIndex, setSecondaryColor ? pickedColorIndex : currentSecondaryColorIndex);
		}

		void SetCustomVehicleColor(Vehicle vehicle, bool setCustomPrimaryColor, bool setCustomSecondaryColor, Vector3 customColor) {
			if (setCustomPrimaryColor) {
				VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, customColor.x, customColor.y, customColor.z);
			}
			if (setCustomSecondaryColor) {
				VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, customColor.x, customColor.y, customColor.z);
			}
		}

		void SetVehicleColors(Vehicle vehicle, bool setPrimaryColor, bool setSecondaryColor, int pickedColorIndex) {
			int currentPrimaryColorIndex, currentSecondaryColorIndex;
			VEHICLE::GET_VEHICLE_COLOURS(vehicle, &currentPrimaryColorIndex, &currentSecondaryColorIndex);
			VEHICLE::SET_VEHICLE_COLOURS(vehicle, setPrimaryColor ? pickedColorIndex : currentPrimaryColorIndex, setSecondaryColor ? pickedColorIndex : currentSecondaryColorIndex);
		}

		void GetVehicleExtraColors(Vehicle vehicle, int& primaryColorIndex, int& secondaryColorIndex) {
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &primaryColorIndex, &secondaryColorIndex);
		}

		void GetVehicleColors(Vehicle vehicle, int& primaryColorIndex, int& secondaryColorIndex) {
			VEHICLE::GET_VEHICLE_COLOURS(vehicle, &primaryColorIndex, &secondaryColorIndex);
		}

		void SetNeonLightsColor(Vehicle vehicle, bool enableNeon, int red, int green, int blue) {
			if (enableNeon) {
				for (int i = 0; i < 4; i++) {
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, i, true);
				}
			}
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, red, green, blue);
		}

	}
}