#include "pch.h"
#include "GUI/menu/menu.h"
#include "GUI/buttons/buttons.h"
#include "app/view/view.h"
#include "app/feature/local/localfeatures.h"

int testInt;
float testFloat;
bool toggle;
int StringArray;
std::vector<std::string> testV
{
	"Name",
	"Name2"
};

void run()
{	

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
	srand(GetTickCount64());
	run();
}
