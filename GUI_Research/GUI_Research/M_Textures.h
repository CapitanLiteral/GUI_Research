#ifndef __M_TEXTURES_H__
#define __M_TEXTURES_H__

#include "Module.h"
#include <list>

struct SDL_Texture;
struct SDL_Surface;

class M_Textures : public Module
{
public:

	M_Textures(bool startEnabled = true);

	// Destructor
	virtual ~M_Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&)override;

	// Called before the first frame
	bool Start()override;

	// Called before quitting
	bool CleanUp()override;

	// Load Texture
	SDL_Texture* const	Load(const char* path);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

	void DrawDebug()override;

public:

	std::list<SDL_Texture*>	textures;
};


#endif // __M_TEXTURES_H__