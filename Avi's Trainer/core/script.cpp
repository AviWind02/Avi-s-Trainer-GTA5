#include "pch.h"
#include "GUI/menu/menu.h"

void main()
{	

	while (true)
	{
		GUI::menu::Title();
		GUI::controls::ControlTick();
		GUI::controls::DisableControls();
		///////////////////


		GUI::menu::SetOption("Test", "Test", "");
		GUI::menu::SetSpriteOnOption("commonmenu", "arrowright", { 0.015f, 0.025f }, 1.f, { 255, 255, 255, 255 });
		GUI::menu::SetOption("Test", "Test", "");
		GUI::menu::SetSpriteOnOption("commonmenu", "common_medal", { 0.015f, 0.025f }, 1.f, { 255, 255, 255, 255 });
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "");
		GUI::menu::SetSpriteOnOption("commonmenu", "common_medal", { 0.015f, 0.025f }, 1.f, { 255, 255, 255, 255 });
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetOption("Test", "Test", "Test");
		GUI::menu::SetSpriteOnOption("commonmenu", "common_medal", { 0.015f, 0.025f }, 1.f, { 255, 255, 255, 255 });

		///////////////////

		GUI::menu::End();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
