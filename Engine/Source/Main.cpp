#include <cstdlib>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"

enum main_states
{
	MAIN_CREATION,  
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			App = new Application();
			ENGINE_LOG("Application Created --------------");
			state = MAIN_START;
			break;

		case MAIN_START:

			ENGINE_LOG("Application Init --------------");
			if (App->Init() == false)
			{
				ENGINE_LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				ENGINE_LOG("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				ENGINE_LOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			ENGINE_LOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				ENGINE_LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}

	delete App;
	ENGINE_LOG("Bye :)\n");
	return main_return;
}
