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

	// If ModuleEditor is not initialized we store data in a temporal vector until we are able to send data
	if (App->editor->IsInitialized() && temp_console.empty())
	{
		App->editor->ConsoleLog(tmp_string2);
	}
	else if (App->editor->IsInitialized() && !temp_console.empty())
	{
		for (auto it = temp_console.begin(); it < temp_console.end(); ++it)
		{
			App->editor->ConsoleLog(*it);
		}
	}
	else
	{
		temp_console.push_back(tmp_string2);
	}

}