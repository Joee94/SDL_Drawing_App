#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>
#include <SDL_image.h>
#include <SDL.h>

/// This class stores a texture image which you can draw where you want!
class Sprite
{
public:

	Sprite();
	~Sprite();

	/// Loads a .bmp file, returns true on success or false on failure
	bool LoadFromBMP( std::string filename, SDL_Renderer *renderer );

	/// Specify the position of the top-left corner of the sprite
	/// Width and height are the image's original
	void Draw( int positionX, int positionY, SDL_Renderer *renderer );

protected:

	/// This variable will be our handle for the texture
	SDL_Texture *_texture;

};
#endif
