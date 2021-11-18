#include "ModuleTexture.h"

static const char* texture_image_path = "..\\Source\\Textures\\lenna_100_dpi.jpg";

ModuleTexture::ModuleTexture()
{
}

bool ModuleTexture::Init()
{
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/* wrong DevIL version */
		return UPDATE_ERROR;
	}
	ilInit();											/* Initialization of DevIL */
	ilGenImages(1, &texid);							    /* Generation of one image name */
	ilBindImage(texid);									/* Binding of image name */
	success = ilLoadImage("texture_image_path");	    /* Loading of image "image.jpg" */

    if (!success)
    {
        return UPDATE_ERROR;
    }
    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every color component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
    if (!success)
    {
        return UPDATE_ERROR;
    }
    glGenTextures(1, &image); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */

    ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data we can release memory used by image. */
    return true;
}

update_status ModuleTexture::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
    glDeleteTextures(1, &image);
    return true;
}
