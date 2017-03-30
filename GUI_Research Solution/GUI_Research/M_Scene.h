#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "Module.h"

struct SDL_Texture;
class GUIImage;

class M_Scene : public Module
{
public:

	M_Scene(bool startEnabled = true);
	virtual ~M_Scene();

	bool Awake(pugi::xml_node& node)override;
	bool Start()override;
	update_status PreUpdate(float dt)override;
	update_status Update(float dt)override;
	update_status PostUpdate(float dt)override;
	bool CleanUp()override;

	void DrawDebug();

	void GuiEvent(GUIElement* element, int64_t state)override;

private:
	SDL_Texture* debug_tex = nullptr;
	GUIImage* img1 = nullptr;
	GUIImage* img2 = nullptr;
	GUIImage* img3 = nullptr;
	GUIImage* img4 = nullptr;
	GUIImage* img5 = nullptr;
	GUIImage* img6 = nullptr;
};

#endif // __j1SCENE_H__