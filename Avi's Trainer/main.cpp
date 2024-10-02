#include "pch.h"
#include "Script Hook V/inc/main.h"

#include <GUI/menu/menu.h>

#include <app/feature/local/localfeatures.h>
#include <app/feature/vehiclespawner/vehiclespawner.h>


extern void ScriptMain();

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, ScriptMain);// Main Script the handle the Native UI and Controls
		LOG << "Registered Script Main";
		scriptRegisterAdditionalThread(hInstance, feature::local::LocalThread);
		LOG << "Registered Local Thread";
		scriptRegisterAdditionalThread(hInstance, feature::vehiclespawner::LoadVehicleWithInfo);
		LOG << "Registered Vehicle Info Loader Thread";

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