#include "pch.h"
#include "GUI/menu/menu.h"
#include "GUI/buttons/buttons.h"

int testInt;
float testFloat;
bool toggle;
int StringArray;
std::vector<std::string> testV
{
	"Name",
	"Name2"
};

void main()
{	

	while (true)
	{
		GUI::menu::Title();
		GUI::controls::ControlTick();
		GUI::controls::DisableControls();
		///////////////////

		GUI::buttons::Option("Basic Option");
		GUI::buttons::Int("Basic Int Option", &testInt, 0, 100, 5);
		GUI::buttons::Float("Basic Float Option", &testFloat, 0, 10, .5f);
		GUI::buttons::Toggle("Basic Toggle", &toggle);
		GUI::buttons::StringArray("String Array", StringArray, testV);

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
