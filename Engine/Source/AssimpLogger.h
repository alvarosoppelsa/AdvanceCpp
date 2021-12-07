#pragma once
//#include <assimp/Importer.hpp>
//#include <AssimpLogger.h>
#include <assimp/LogStream.hpp>
//#include <assimp/Logger.hpp>
#include "Globals.h"

using namespace Assimp;

// Example stream
class AssimpLogger :
    public LogStream
{
public:
    // Constructor
    AssimpLogger()
    {
    }

    // Destructor
    ~AssimpLogger()
    {
    }

    // Using our own logger
	void write(const char* message)
    {
        ENGINE_LOG("AssimpLogger says: %s", message);
    }
};
