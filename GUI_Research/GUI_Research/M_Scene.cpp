#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "M_Input.h"
#include "M_Gui.h"
#include "GUIElement.h"
#include "GUIImage.h"
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
	img1 = app->gui->CreateImageFromPreset({ 100, 100, 484, 512 }, "window", "image_test_animation_transition1");
	img1->AddAnimationOrTransition(MOUSE_RCLICK_DOWN, T_FADE);
	img1->AddAnimationOrTransition(ENABLE, T_FADE);
	app->gui->guiList.push_back(img1);

	img2 = app->gui->CreateImageFromPreset({ 600, 100, 484, 512 }, "window", "image_test_animation_transition2");
	img2->AddAnimationOrTransition(MOUSE_LCLICK_DOWN, T_MOVE_RIGHT);
	img2->AddAnimationOrTransition(ENABLE, T_MOVE_RIGHT);
	app->gui->guiList.push_back(img2);

	img3 = app->gui->CreateImageFromPreset({ 1200, 100, 484, 512 }, "window", "image_test_animation_transition3");
	img3->AddAnimationOrTransition(MOUSE_ENTERS, SA_SHAKE);
	img3->AddAnimationOrTransition(MOUSE_LEAVES, SA_BOUNCE);
	app->gui->guiList.push_back(img3);

	return true;
}

// Called each loop iteration
update_status M_Scene::PreUpdate(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		if (img1)
			img1->Enable();
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		if (img2)
			img2->Enable();
	}

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


	return UPDATE_CONTINUE;
}

// Called before quitting
bool M_Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void M_Scene::GuiEvent(GUIElement* element, int64_t state) 
{
	
}

void M_Scene::DrawDebug()
{

}