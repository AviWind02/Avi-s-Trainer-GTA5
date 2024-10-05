#include "pch.h"

#include <GUI/menu/menu.h>

#include "app/feature/local/localfeatures.hpp"
#include "app/feature/vehiclespawner/vehiclespawner.h"
#include "app/feature/weapons/weaponclub/weaponclub.h"


extern void ScriptMain();

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, ScriptMain);// Main Script the handle the Native UI and Controls
		LOG << "Registered Script Main";
		scriptRegisterAdditionalThread(hInstance, app::feature::local::LocalThread);
		LOG << "Registered Local Thread";
		scriptRegisterAdditionalThread(hInstance, feature::vehiclespawner::LoadVehicleWithInfo);
		LOG << "Registered Vehicle Info Loader Thread";
		scriptRegisterAdditionalThread(hInstance, feature::weapon::weaponclub::LoadWeaponWithInfo);
		LOG << "Registered Weapon Info Loader Thread";
        presentCallbackRegister((PresentCallback)core::renderer::OnPresent);
		break;
	case DLL_PROCESS_DETACH:
		scriptUnregister(hInstance);
        presentCallbackUnregister((PresentCallback)core::renderer::OnPresent);
		core::renderer::ShutdownImGui();
		break;
	}		
	return TRUE;
}