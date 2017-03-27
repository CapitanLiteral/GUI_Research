#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "M_Input.h"
#include "M_Textures.h"
#include "M_Audio.h"
#include "M_Render.h"
#include "M_Window.h"
#include "M_Gui.h"
#include "M_Scene.h"

#include "GB_Rectangle.h"

M_Scene::M_Scene(bool startEnabled) : Module(startEnabled)
{
	name.assign("scene");
}

// Destructor
M_Scene::~M_Scene()
{}

// Called before render is available
bool M_Scene::Awake(pugi::xml_node& node)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool M_Scene::Start()
{
	debug_tex = app->tex->Load("data/textures/test.png");
	

	return true;
}

// Called each loop iteration
update_status M_Scene::PreUpdate(float dt)
{
	/*
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y -= 50 * dt;
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y += 50 * dt;
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x -= 50 * dt;
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x += 50 * dt;
	*/

	return UPDATE_CONTINUE;
}

// Called each loop iteration
update_status M_Scene::Update(float dt)
{


	return UPDATE_CONTINUE;
}

// Called each loop iteration
update_status M_Scene::PostUpdate(float dt)
{
	/*
	uint w, h;
	app->tex->GetSize(debug_tex, w, h);
	app->render->Blit(debug_tex, &GB_Rectangle<int>( 100, 100, w, h ).GetSDLrect(), nullptr);
	*/

	return UPDATE_CONTINUE;
}

// Called before quitting
bool M_Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void M_Scene::GuiEvent(GUIElement* element, gui_events state) 
{
	
}

void M_Scene::DrawDebug()
{

}