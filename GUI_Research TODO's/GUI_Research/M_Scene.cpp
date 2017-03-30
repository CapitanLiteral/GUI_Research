#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "M_Input.h"
#include "M_Gui.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUILabel.h"
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
	img1 = app->gui->CreateImageFromPreset({ 100, 100, 484, 512 }, "window", "image_animation_transition1");
	img1->AddAnimationOrTransition(MOUSE_LCLICK_DOWN, T_FADE);
	img1->AddAnimationOrTransition(ENABLE, T_FADE);
	app->gui->guiList.push_back(img1);
	GUILabel* l1 = app->gui->CreateLabel({140, 70, 100, 50}, MEDIUM, "label1", "LClick: fade. Q: enable with fade");
	app->gui->guiList.push_back(l1);

	img2 = app->gui->CreateImageFromPreset({ 600, 100, 484, 512 }, "window", "image_animation_transition2");
	img2->AddAnimationOrTransition(MOUSE_RCLICK_DOWN, T_DROP);
	img2->AddAnimationOrTransition(ENABLE, T_DROP);
	app->gui->guiList.push_back(img2);
	GUILabel* l2 = app->gui->CreateLabel({ 640, 70, 100, 50 }, MEDIUM, "label2", "RClick: drop. W: enable with drop");
	app->gui->guiList.push_back(l2);

	img3 = app->gui->CreateImageFromPreset({ 1100, 100, 484, 512 }, "window", "image_animation_transition3");
	img3->AddAnimationOrTransition(MOUSE_ENTERS, SA_SHAKE);
	img3->AddAnimationOrTransition(MOUSE_LEAVES, SA_BOUNCE);
	app->gui->guiList.push_back(img3);
	GUILabel* l3 = app->gui->CreateLabel({ 1140, 70, 100, 50 }, MEDIUM, "label3", "Mouse enter: shake. Mouse leave: bounce");
	app->gui->guiList.push_back(l3);

	img4 = app->gui->CreateImage({230, 700, 230, 71}, {411, 166, 230, 71}, "image_animation_transition4");
	img4->AddAnimationOrTransition(MOUSE_ENTERS, T_MOVE_UP);
	img4->AddAnimationOrTransition(ENABLE, T_MOVE_UP);
	app->gui->guiList.push_back(img4);
	GUILabel* l4 = app->gui->CreateLabel({ 250, 670, 100, 50 }, MEDIUM, "label4", "Mouse enter: move up. E: enable");
	app->gui->guiList.push_back(l4);

	img5 = app->gui->CreateImage({ 640, 700, 230, 71 }, { 411, 166, 230, 71 }, "image_animation_transition5");
	img5->AddAnimationOrTransition(MOUSE_LCLICK_DOWN, T_FLY);
	img5->AddAnimationOrTransition(ENABLE, T_FLY);
	app->gui->guiList.push_back(img5);
	GUILabel* l5 = app->gui->CreateLabel({ 660, 670, 100, 50 }, MEDIUM, "label5", "LClick: fly. R: enable with fly");
	app->gui->guiList.push_back(l5);
	
	img6 = app->gui->CreateImage({ 420, 850, 328, 103 }, {485, 829, 328, 103}, "image_animation_transition6");
	img6->AddAnimationOrTransition(MOUSE_ENTERS, SA_FLASH);
	img6->AddAnimationOrTransition(MOUSE_LEAVES, SA_PULSE);
	app->gui->guiList.push_back(img6); 
	GUILabel* l6 = app->gui->CreateLabel({ 440, 820, 100, 50 }, MEDIUM, "label6", "Mouse enter: flash. Mouse leave: pulse");
	app->gui->guiList.push_back(l6);

	GUILabel* lcb = app->gui->CreateLabel({ 1100, 720, 100, 50 }, MEDIUM, "lcb", "Beizier curves");
	app->gui->debugGuiList.push_back(lcb);

	//1100 720
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
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		if (img4)
			img4->Enable();
	}
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		if (img5)
			img5->Enable();
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