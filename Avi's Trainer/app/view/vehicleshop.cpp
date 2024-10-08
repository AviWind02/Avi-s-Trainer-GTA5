#include "pch.h"
#include "app/feature/vehicle/vehicleshop/vehicleshop.h"
namespace view {
	namespace vehicleshop {
		using namespace g_feature;

		bool hasTheoriginalModifiableModsChanged;
		static int modificationsTypeID;
		int originalModifiableMods; // Store the original modification

		void StoreOriginalModifications(int modifications) {
			originalModifiableMods = VEHICLE::GET_VEHICLE_MOD(g_feature::g_player::GetPlayerVehicle(), modifications);
		}

		void SelectVehicleModifiableMods(int modifiableMods, bool view)
		{
			VEHICLE::SET_VEHICLE_MOD(g_player::GetPlayerVehicle(), modificationsTypeID, modifiableMods, false);
			if (!view)
				originalModifiableMods = modifiableMods;
		}

		void RevertToOriginalModifications()
		{
			VEHICLE::SET_VEHICLE_MOD(g_player::GetPlayerVehicle(), modificationsTypeID, originalModifiableMods, false);
			hasTheoriginalModifiableModsChanged = false;
		}

		void SelectedVehicleModifiableMods(int modifiableMods)
		{
			if (originalModifiableMods == modifiableMods)
				GUI::menu::SetSpriteOnOption("commonmenu", "shop_garage_icon_a");
			if (GUI::controls::currentOption == GUI::controls::optionCount)//On hover set the mod to make it viewable
				SelectVehicleModifiableMods(modifiableMods, true);
		}

		void VehicleModifications() {

			std::string fallbackName = "mod";

			if (!g_player::IsPlayerInVehicle()) {
				GUI::buttons::Option("You need to be in a vehicle.");
				return;
			}
			

			for (int modifications = 0; modifications < 48; modifications++) {
			/*	if (modifications >= 11 && modifications <= 24)
					continue;*/

				if (VEHICLE::GET_NUM_VEHICLE_MODS(g_feature::g_player::GetPlayerVehicle(), modifications) > 0)
				{
					const char* modSlotName = VEHICLE::GET_MOD_SLOT_NAME(g_feature::g_player::GetPlayerVehicle(), modifications);

					if (modSlotName == nullptr)
					{
						fallbackName = feature::vehicleshop::GetVehicleModName(modifications).c_str();
						modSlotName = fallbackName.c_str();
					}
					else
						if (IsAllCaps(modSlotName))
							modSlotName = HUD::_GET_LABEL_TEXT(modSlotName);

					if (hasTheoriginalModifiableModsChanged)
						RevertToOriginalModifications();

					GUI::buttons::Sub(modSlotName, pages::VehicleShop_PickedMod_page, [&]() {
						StoreOriginalModifications(modifications);
						modificationsTypeID = modifications;
					});
				}
			}
		}

		void VehicleSelctedModifications() {
			std::string fallbackName = "mod";


			const int numberOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(g_feature::g_player::GetPlayerVehicle(), modificationsTypeID);

			GUI::buttons::Option("None", []() { 
				SelectVehicleModifiableMods(-1, false); 
				hasTheoriginalModifiableModsChanged = true; 
			});
			SelectedVehicleModifiableMods(-1);


			for (int modifiableMods = 0; modifiableMods < numberOfVehicleMods; modifiableMods++) {
				const char* vehicleModLabel = VEHICLE::GET_MOD_TEXT_LABEL(g_feature::g_player::GetPlayerVehicle(), modificationsTypeID, modifiableMods);
				const char* vehicleModName = HUD::_GET_LABEL_TEXT(vehicleModLabel);
				if (vehicleModLabel == nullptr)
				{
					fallbackName = (feature::vehicleshop::GetVehicleModName(modificationsTypeID) + " Level " + std::to_string(modifiableMods));
					vehicleModName = fallbackName.c_str();
				}
				GUI::buttons::Option(vehicleModName, [modifiableMods]() { 
					SelectVehicleModifiableMods(modifiableMods, false); 
					hasTheoriginalModifiableModsChanged = true; 
				});
				SelectedVehicleModifiableMods(modifiableMods);
			}
		}
	}
}
