#include "pch.h"

#include "GUI/menu/menu.h"


#include "app/view/view.h"
#include "app/feature/local/localfeatures.h"
#include "app/feature/vehiclespawner/vehiclespawner.h"

#include "core/pool/pool.h"
#include "core/memory/nativememory.h"

void MenuUI()
{
	srand(GetTickCount64());
	while (true)
	{
		core::pool::PoolDebugNative();
		GUI::menu::Title();
		GUI::controls::ControlTick();
		GUI::controls::DisableControls();
		switch (GUI::controls::currentSubMenu)
		{
		case pages::mainmenu_page:
		{
			GUI::menu::SetSubTitle("Main Menu");
			GUI::buttons::Sub("Local", pages::local_page);
			GUI::buttons::Sub("Vehicle Spawner", pages::VehicleSpawner_page);
			GUI::buttons::Sub("Setting", pages::setting_page);
		}
		break;


		case pages::local_page:view::local::View(); break;
		case pages::VehicleSpawner_page:feature::vehiclespawner::VehicleSpawnView(); break;
		case pages::VehicleSpawner_Picked_page:feature::vehiclespawner::PickedVehicleView(); break;


			
		
		case pages::setting_page:GUI::menu::DebugMenuView(); break;

		}
		GUI::menu::End();
		WAIT(0);
	}
}

void ScriptMain()
{
	core::memory::nativememory::InitOffsets();
	MenuUI();
}

