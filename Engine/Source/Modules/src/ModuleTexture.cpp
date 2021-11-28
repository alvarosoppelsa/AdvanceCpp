
#define NOMINMAX

#include "ModuleTexture.h"
#include "Application.h"

#include "ModuleProgram.h"
#include "IL/ilu.h"

static const char* texture_image_path = "..\\Source\\Textures\\lenna_100_dpi.jpg";

ModuleTexture::ModuleTexture()
	: finished(0)
	, success(false)
	, image(0)
	, texid(0)
{
}

bool ModuleTexture::Init()
{
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/* wrong DevIL version */
		return false;
	}
	ilInit();											/* Initialization of DevIL */
	ilGenImages(1, &texid);							    /* Generation of one image name */
	ilBindImage(texid);									/* Binding of image name */
	success = ilLoadImage(texture_image_path);	        /* Loading of image "image.jpg" */

    if (success != IL_TRUE)
    {
        return false;
    }
    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every color component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
    if (success != IL_TRUE)
    {
        return false;
    }

    // Flip texture if upside down
    ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   /* We will use linear interpolation for minifying filter */

    // Texture specification 
	glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        ilGetInteger(IL_IMAGE_BPP), 
        ilGetInteger(IL_IMAGE_WIDTH), 
        ilGetInteger(IL_IMAGE_HEIGHT), 
        0, 
        ilGetInteger(IL_IMAGE_FORMAT), 
        GL_UNSIGNED_BYTE, 
        ilGetData()); 

    ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data we can release memory used by image. */
    return true;
}

update_status ModuleTexture::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glUniform1i(glGetUniformLocation(App->program->ProgramId, "mytexture"), 0);
    return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
    glDeleteTextures(1, &image);
    return true;
}
