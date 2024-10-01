#include "pch.h"

void main()
{	

	while (true)
	{
		GUI::controls::DisableControls();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
