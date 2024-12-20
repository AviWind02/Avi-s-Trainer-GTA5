#include "pch.h"

#include "GUI/menu/menu.h"


#include "app/view/view.h"

#include "core/pool/pool.h"
#include "core/memory/nativememory.h"
#include "feature/local/localfeatures.h"

int i;

void MenuUI()
{
	srand(GetTickCount64());
	while (true)
	{
		core::pool::PoolDebugNative();
		GUI::menu::Title();
		GUI::controls::ControlTick();
		GUI::controls::DisableControls();
		switch (GUI::controls::currentSubMenu){
			case pages::mainmenu_page:{
				GUI::menu::SetSubTitle("Main Menu");
				GUI::buttons::Sub("Local Player", pages::local_page);
				GUI::buttons::Sub("Vehicle Spawner", pages::VehicleSpawner_page);
				GUI::buttons::Sub("Vehicle Shop", pages::VehicleShop_page);
				GUI::buttons::Sub("Ammu-Nation store", pages::WeaponClub_page);
				GUI::buttons::Sub("Weapon Stuff", pages::weapon_page);
				GUI::buttons::Sub("Setting", pages::setting_page);
			}break;


			case pages::local_page:view::local::View(); break;
			case pages::weapon_page:view::weapon::View(); break;

			case pages::VehicleSpawner_page:view::vehiclespawner::VehicleSpawnView(); break;
			case pages::VehicleSpawner_Picked_page:view::vehiclespawner::PickedVehicleView(); break;
			
			case pages::VehicleShop_page: view::vehicleshop::VehicleModifications(); break;
			case pages::VehicleShop_PickedMod_page: view::vehicleshop::VehicleSelectedModifications(); break;

			case pages::WeaponClub_page:view::weaponclub::WeaponClubListClassView(); break;
			case pages::WeaponClub_Picked_Group_page:view::weaponclub::WeaponClubListWeaponView(); break;
			case pages::WeaponClub_Picked_Gun_page:view::weaponclub::WeaponClubListWeaponItemView(); break;
				

				
			case pages::setting_page:GUI::menu::DebugMenuView(); break;

		}
		GUI::menu::End();
		WAIT(0);
	}
}

void ScriptMain()//Main script to UI and other small things to run
{
	core::memory::nativememory::InitOffsets();
	MenuUI();
}

