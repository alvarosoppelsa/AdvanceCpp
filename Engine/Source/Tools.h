#pragma once

#include "GL/glew.h"
#include "windows.h"
#include "string.h"
#include <direct.h> // _getcwd
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace Tools
{
	inline void OpenLink(const char* link)
	{
		ShellExecute(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
	}

	static void APIENTRY OpenGlCallbackFunction(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	) {
		(void)source; (void)type; (void)id;
		(void)severity; (void)length; (void)userParam;
		fprintf(stderr, "%s\n", message);
		if (severity == GL_DEBUG_SEVERITY_HIGH) {
			ENGINE_LOG("Aborting...\n");
			abort();
		}
	}
}
