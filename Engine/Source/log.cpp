#pragma once
#include "Globals.h"
#include "Application.h"

static std::vector<char*> temp_console;

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);

	if (App->IsShutingDown())
	{
		return;	// At this point we cannot ensure the editor still running
	}

	// WARNING!! ModuleEditor is responsible for deleting console outputs
	char* editor = new char[sizeof(tmp_string)];
	memcpy(editor, tmp_string, sizeof(tmp_string));

	//If ModuleEditor is not initialized we store data in a temporal vector until we are able to send data
	if (App->editor->IsInitialized() && temp_console.empty())
	{
		App->editor->ConsoleLog(editor);
	}
	else if (App->editor->IsInitialized() && !temp_console.empty())
	{
		for (auto it = temp_console.begin(); it < temp_console.end(); ++it)
		{
			App->editor->ConsoleLog(*it);
		}
		// Once sent is time to clean temporal console outputs
		temp_console.clear();
	}
	else
	{
		temp_console.push_back(editor);
	}
}