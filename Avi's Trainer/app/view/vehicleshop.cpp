#include "pch.h"
#include "app/feature/vehicle/vehicleshop/vehicleshop.h"
namespace view {
	namespace vehiclespawner {
		using namespace g_feature;



		/*VEHICLE::SET_VEHICLE_MOD_KIT(g_feature::g_player::GetPlayerVehicle(), NULL);
		GUI::buttons::Int("List Vehicle Mods", &i, 0, 24, 1, []() {
			if (g_feature::g_player::IsPlayerInVehicle())
			{
				if (VEHICLE::GET_NUM_VEHICLE_MODS(g_feature::g_player::GetPlayerVehicle(), i) > 0)
				{
					const char* T = VEHICLE::GET_MOD_SLOT_NAME(g_feature::g_player::GetPlayerVehicle(), i);
					if (T != NULL)
						LOG << T << " ID: " << i;
					else
						LOG << "Mod is NULL" << " ID: " << i;

					for (int j = 0; j < VEHICLE::GET_NUM_VEHICLE_MODS(g_feature::g_player::GetPlayerVehicle(), i); j++)
					{
						const char* ModLable = VEHICLE::GET_MOD_TEXT_LABEL(g_feature::g_player::GetPlayerVehicle(), i, j);
						std::string lable = ((std::string)HUD::_GET_LABEL_TEXT(ModLable) + " ID:" + std::to_string(i)).c_str();
						LOG << " - Mod:" << lable;

					}
				}
			}
			});*/
	}
}