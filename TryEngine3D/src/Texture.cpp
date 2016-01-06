#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>

const RTTI Texture::TYPE("Texture", &Component::TYPE);


Texture::Texture():	glTexObject(0),ressourceName("None"),textureMemory(0){
}


void Texture::load(const string& name){
	ressourceName = name;
	glTexObject = loadTexture(name.data(),false);
}

Texture::~Texture(){
	if(this->glTexObject)
		glDeleteTextures(1,&glTexObject);

	if(this->textureMemory)
		SDL_FreeSurface(textureMemory);
}

void Texture::bindTexture()const{
	if(glTexObject)
		glBindTexture(GL_TEXTURE_2D,glTexObject);
}

GLuint Texture::getTexId() const{
	return glTexObject;
}

Vec4f Texture::getPixel(int u, int v)const{
	if(u <= textureMemory->w && v <= textureMemory->h){
		//float* pixel = (float*)textureMemory->pixels + u + textureMemory->pitch * v;
		//return Vec4f(pixel[0],pixel[1],pixel[2],pixel[3]);

		int bpp = textureMemory->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *pixel8 = (Uint8 *)textureMemory->pixels + u * textureMemory->pitch + v * bpp;
		Uint16 *pixel16;
		Uint32 *pixel32;

		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;

		switch(bpp) {
			case 1:
				
				return Vec4f((float)pixel8[0],(float)pixel8[1],(float)pixel8[2],(float)pixel8[3]);
				break;

			case 2:
				pixel16 = (Uint16*)pixel8;
				return Vec4f((float)pixel16[0],(float)pixel16[1],(float)pixel16[2],(float)pixel16[3]);
				break;

			case 4:
				pixel32 = (Uint32*)pixel8;
				SDL_GetRGBA(*pixel32, textureMemory->format, &r, &g, &b, &a);
				return Vec4f((float)r,(float)g,(float)b,(float)a);
				break;

			default:
				return Vec4f(0);       /* shouldn't happen, but avoids warnings */
		}
	}
	return Vec4f(0);
}
Vec4f Texture::getPixel(float u, float v)const{
	return Vec4f(0);
}


GLuint Texture::loadTexture(const char * filename,bool useMipMap)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;

    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        return 0;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_PixelFormat format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

	textureMemory = flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    if (useMipMap)
    {

        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, textureMemory->w,
                          textureMemory->h, GL_RGBA,GL_UNSIGNED_BYTE,
                          textureMemory->pixels);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);

    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, textureMemory->w,
                     textureMemory->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                     textureMemory->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}

SDL_Surface * Texture::flipSurface(SDL_Surface * surface)
{
    int current_line,pitch;
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w,surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask,
                                   surface->format->Gmask,
                                   surface->format->Bmask,
                                   surface->format->Amask);



    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);

    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++)
    {
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
               &((unsigned char* )surface->pixels)[(surface->h - 1  -
                                                    current_line)*pitch],
               pitch);
    }

    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}