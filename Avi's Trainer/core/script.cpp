#include "pch.h"
#include "GUI/menu/menu.h"
#include "GUI/buttons/buttons.h"
#include "app/view/view.h"
#include "app/feature/local/localfeatures.h"
#include "core/memory/nativememory.h"

void MenuUI()
{
	srand(GetTickCount64());
	while (true)
	{
		GUI::menu::Title();
		GUI::controls::ControlTick();
		GUI::controls::DisableControls();
		view::local::View();
		GUI::menu::End();
		WAIT(0);
	}
}

void ScriptMain()
{
	core::memory::nativememory::InitOffsets();
	MenuUI();
}
