#include "GUIElement.h"
#include "App.h"
#include "M_Render.h"

#include "M_Window.h"
#include "M_GUI.h"

GUIElement::GUIElement(std::string name, int flags) : rect(0,0,0,0), drawRect(0.f, 0.f, 0.f, 0.f), name(name)
{
	if (flags & DRAGGABLE)
		SetDraggable(true);
	else
		SetDraggable(false);

	if (flags & INTERACTIVE)
		SetInteractive(true);
	else
		SetInteractive(false);

	if (flags & CAN_FOCUS)
		SetCanFocus(true);
	else
		SetCanFocus(false);

	if (flags & ACTIVE)
		SetActive(true);
	else
		SetActive(false);
	
	//FIX this should not be like this...
	if (flags & STANDARD_PRESET)
	{
		SetActive(true);
		SetCanFocus(true);
		SetInteractive(true);
		SetDraggable(false);
	}

}
GUIElement::~GUIElement()
{
	for (std::list<GUIElement*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		RELEASE(*it);
	}
	childs.clear();
}

void GUIElement::CheckInput(const GUIElement * mouseHover, const GUIElement * focus)
{
}
bool GUIElement::CheckMouseOver() const
{
	iPoint mousePosition;
	app->input->GetMousePosition(mousePosition.x, mousePosition.y);
	
	return rect.Contains(mousePosition.x, mousePosition.y);
}
void GUIElement::Center()
{
	int frame_w = (parent) ? parent->GetLocalRect().w/2 - (GetLocalRect().w / 2) : app->render->camera.w/2 - (GetLocalRect().w / 2);
	int frame_h = (parent) ? parent->GetLocalRect().h/2 - (GetLocalRect().h / 2) : app->render->camera.h/2 - (GetLocalRect().h / 2);

	SetLocalPos(frame_w, frame_h);
	SetGlobalPos(0, 0);
}
void GUIElement::CenterX()
{
	int frame_w = (parent) ? parent->GetLocalRect().w : app->render->camera.w;

	SetLocalPos(frame_w / 2 - rect.w / 2, rect.h);
	SetGlobalPos(frame_w / 2 - rect.w / 2, rect.h);
}
void GUIElement::CenterY()
{
	int frame_h = (parent) ? parent->GetLocalRect().h : app->render->camera.h;

	SetLocalPos(rect.w, frame_h / 2 - rect.h / 2);
	SetGlobalPos(rect.w, frame_h / 2 - rect.h / 2);
}
void GUIElement::AddListener(Module * moduleToAdd)
{
	std::list<Module*>::iterator it = std::find(listeners.begin(), listeners.end(), moduleToAdd);
	if (it == listeners.end())
		listeners.push_back(moduleToAdd);
}
void GUIElement::RemoveListener(Module * moduleToRemove)
{
	std::list<Module*>::iterator it = std::find(listeners.begin(), listeners.end(), moduleToRemove);
	if (it != listeners.end())
	{
		listeners.erase(it);
	}	
}
bool GUIElement::Save(pugi::xml_node & node) const
{
	bool ret = true;

	return false;
}

GB_Rectangle<int> GUIElement::GetScreenRect() const
{
	if (parent != nullptr)
	{
		iPoint p = GetScreenPos();
		return{ p.x, p.y, rect.w, rect.h };
	}
	return rect;
}
GB_Rectangle<int> GUIElement::GetLocalRect() const
{
	return rect;
}
iPoint GUIElement::GetScreenPos() const
{
	if (parent != nullptr)
		return parent->GetScreenPos() + iPoint(rect.x, rect.y);
	else
		return iPoint(rect.x, rect.y);
}
iPoint GUIElement::GetLocalPos() const
{
	return localPosition;
}
iPoint GUIElement::GetGlobalPos() const
{
	return iPoint(rect.x, rect.y);
}
iPoint GUIElement::GetSize() const
{
	return iPoint(rect.w, rect.h);
}
bool GUIElement::GetDraggable() const
{
	return status.draggable;
}
bool GUIElement::GetInteractive() const
{
	return status.interactive;
}
bool GUIElement::GetCanFocus() const
{
	return status.canFocus;
}
bool GUIElement::GetActive() const
{
	return status.active;
}
GUIElement * GUIElement::GetParent() const
{
	return parent;
}
const std::list<GUIElement*> GUIElement::GetChilds() const
{
	return childs;
}
gui_types GUIElement::GetType() const
{
	return type;
}
std::list<Module*> GUIElement::GetListeners() const
{
	return listeners;
}
bool GUIElement::GetMouseInside() const
{
	return status.mouseInside;
}
fPoint GUIElement::GetScale() const
{
	return scale;
}
bool GUIElement::GetLClicked() const
{
	return status.lClicked;
}
bool GUIElement::GetRClicked() const
{
	return status.rClicked;
}
ElementStatus GUIElement::GetElementStatus() const
{
	return status;
}
iPoint GUIElement::GetDrawPosition()const
{
	return iPoint(drawRect.x, drawRect.y);
}
GB_Rectangle<float> GUIElement::GetDrawRect()const
{
	return drawRect;
}

std::string GUIElement::GetPresetType() const
{
	return presetName;
}

std::string GUIElement::GetName() const
{
	return name;
}

std::list<Module*> GUIElement::GetListeners_noconst()
{
	return listeners;
}

void GUIElement::SetLocalPos(int x, int y)
{
	localPosition.create(x, y);
	//Changes this item position and its childs.
	//if (parent)
	//{
	//	rect.x = x + parent->GetLocalPos().x;
	//	rect.y = y + parent->GetLocalPos().y;
	//}
	//else
	//{
	//	rect.x = x;
	//	rect.y = y;
	//}
	//drawRect.x = rect.x;
	//drawRect.y = rect.y;
	
	//for (std::list<GUIElement*>::iterator it = childs.begin(); it != childs.end(); ++it)
	//	if ((*it)) (*it)->SetLocalPos((*it)->GetLocalPos().x + x, (*it)->GetLocalPos().y + y);
			
}
void GUIElement::SetGlobalPos(int x, int y)
{
	//Changes this item position and its childs.
	if (parent)
	{
		rect.x = parent->GetGlobalPos().x + localPosition.x;
		rect.y = parent->GetGlobalPos().y + localPosition.y;
	}
	else
	{
		rect.x = x + localPosition.x;
		rect.y = y + localPosition.y;
	}
	drawRect.x = rect.x;
	drawRect.y = rect.y;

	for (std::list<GUIElement*>::iterator it = childs.begin(); it != childs.end(); ++it)
		if ((*it)) (*it)->SetGlobalPos(x, y);

}
void GUIElement::SetDraggable(bool _draggable) 
{
	status.draggable = _draggable;
	status.statusChanged = true;
}
void GUIElement::SetInteractive(bool _interactive)
{
	status.interactive = _interactive;
	status.statusChanged = true;
}
void GUIElement::SetCanFocus(bool _focus)
{
	status.canFocus = _focus;
	status.statusChanged = true;
}
void GUIElement::SetActive(bool _active) 
{
	if (_active)
		Enable();
	else
		Disable();
}
void GUIElement::SetParent(GUIElement * _parent) 
{
	if (this->parent == nullptr)
	{
		_parent->childs.push_back(this);
		parent = _parent;
	}
	else if (this->parent != _parent)
	{
		this->parent->childs.remove(this);
		_parent->childs.push_back(this);
		parent = _parent;
	}	
	status.statusChanged = true;
}
void GUIElement::SetType(gui_types _type)
{
	type = _type;
	status.statusChanged = true;
}
void GUIElement::SetRectangle(GB_Rectangle<int> _rect)
{
	//Only modifies this element but doesnt change childs.
	rect = _rect;
	drawRect.Set(_rect.x, _rect.y, _rect.w, _rect.h);
	status.statusChanged = true;
}
void GUIElement::SetRectangle(int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	drawRect.Set(x, y, w, h);
	status.statusChanged = true;
}
void GUIElement::SetMouseInside(bool ins)
{
	if (status.interactive && status.active)
	{
		status.mouseInside = ins;
		status.statusChanged = true;
	}

}
void GUIElement::SetScale(fPoint _scale)
{
	scale = _scale;
	resize(_scale);
	status.statusChanged = true;
}
void GUIElement::SetScale(float _scaleX, float _scaleY)
{
	scale.x = _scaleX;
	scale.y = _scaleY;
	resize(fPoint(_scaleX, _scaleY));
	status.statusChanged = true;
}
void GUIElement::SetLClicked(bool l)
{
	if (status.interactive && status.active)
	{
		status.lClicked = l;
		status.statusChanged = true;
	}
}
void GUIElement::SetRClicked(bool r)
{
	if (status.interactive && status.active)
	{
		status.rClicked = r;
		status.statusChanged = true;
	}
}
void GUIElement::SetStatusChanged(bool changed)
{
	status.statusChanged = changed;
}
void GUIElement::Enable()
{
	if (!status.active)
	{
		if (eventsToReact & ENABLE)
		{
			OnGuiEvent(ENABLE);
		}
		else
		{
			drawRect.Set(rect.x, rect.y, rect.w, rect.h);
		}
		status.active = true; 
		status.statusChanged = true;
		alpha = 255;
	}
}
void GUIElement::Disable()
{
	if (status.active)
	{
		//If we have a reaction to use at disable dont set active to false directly, 
		//send the event and later in the transition set it to false.
		//If there is no reaction just set active to false
		if (eventsToReact & DISABLE)
		{
			OnGuiEvent(DISABLE);
			mustDisable = true;
		}
		else
		{
			status.active = false;
		}
		status.statusChanged = true;
	}
}
void GUIElement::resize(fPoint newScale)
{
	fPoint variation = fPoint(scale.x / newScale.x, scale.y / newScale.y);
	rect.x *= variation.x;
	rect.y *= variation.y;
	drawRect.x *= variation.x;
	drawRect.y *= variation.y;
	status.statusChanged = true;
}
void GUIElement::SetSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
	drawRect.w = w;
	drawRect.h = h;
	status.statusChanged = true;
}
void GUIElement::SetDrawPosition(float x, float y)
{
	drawRect.Move(x, y);

	/*for (std::list<GUIElement*>::iterator it = childs.begin(); it != childs.end(); ++it)
		if ((*it)) (*it)->SetDrawPosition((*it)->drawRect.x + x, (*it)->drawRect.y + y);*/
}

void GUIElement::SetPresetType(std::string str)
{
	presetName = str;
}
void GUIElement::SetName(std::string str)
{
	name = str;
}
void GUIElement::SetOnLClickUp(gui_events _event)
{
	status.statusChanged = true;
	status.onLClickUp = _event;
}
void GUIElement::SetOnLClickDown(gui_events _event)
{
	status.statusChanged = true;
	status.onLClickDown = _event;
}
void GUIElement::SetOnRClickUp(gui_events _event)
{
	status.statusChanged = true;
	status.onRClickUp = _event;
}
void GUIElement::SetOnRClickDown(gui_events _event)
{
	status.statusChanged = true;
	status.onRClickDown = _event;
}
void GUIElement::SetOnGainFocus(gui_events _event)
{
	status.statusChanged = true;
	status.onGainFocus = _event;
}
void GUIElement::SetOnLooseFocus(gui_events _event)
{
	status.statusChanged = true;
	status.onLooseFocus = _event;
}
void GUIElement::SetOnMouseEnters(gui_events _event)
{
	status.statusChanged = true;
	status.onMouseEnters = _event;
}
void GUIElement::SetOnMouseLeaves(gui_events _event)
{
	status.statusChanged = true;
	status.onMouseLeaves = _event;
}


//------------------------------

void GUIElement::AddAnimationOrTransition(gui_events eventToReact, staticAnim_or_transition animOrTransition)
{
	//TODO 1: Insert in the map the pair of event and animation you recieve. Remeber before inserting checking if that event has been already added, if it has replace the animatio set before for the new one.
	
	
	std::map<gui_events, staticAnim_or_transition>::iterator it = transAndAnimations.find(eventToReact);
	if (it != transAndAnimations.end())
	{
		//If we find that that event has already been told to react we overide it.
		it->second = animOrTransition;
	}
	else
	{
		//If we doont find that event reaction setted already we just set it.
		transAndAnimations.insert(std::pair<gui_events, staticAnim_or_transition>(eventToReact, animOrTransition));
		this->eventsToReact = (gui_events)(this->eventsToReact | eventToReact);
	}
	//----
}
void GUIElement::RemoveAnimationOrTransitionReaction(gui_events eventToReact)
{
	if (this->eventsToReact & eventToReact)
	{
		std::map<gui_events, staticAnim_or_transition>::iterator it = transAndAnimations.find(eventToReact);
		if (it != transAndAnimations.end())
		{
			transAndAnimations.erase(it);
			this->eventsToReact = (gui_events)(this->eventsToReact & ~eventToReact);
		}
	}
}
void GUIElement::GetAllAnimationAndTransitions(std::vector<std::pair<gui_events, staticAnim_or_transition>>& animsAndTrans)
{
	std::map<gui_events, staticAnim_or_transition>::iterator it = transAndAnimations.begin();
	for (; it != transAndAnimations.end(); ++it)
	{
		animsAndTrans.push_back((*it));
	}
}
bool GUIElement::HasEventReactionSet(gui_events eventToReact)
{
	return (eventsToReact & eventToReact);
}
staticAnim_or_transition GUIElement::GetAnimOrTransitionForEvent(gui_events eventToReact)
{
	if (this->eventsToReact & eventToReact)
	{
		std::map<gui_events, staticAnim_or_transition>::iterator it = transAndAnimations.find(eventToReact);
		if (it != transAndAnimations.end())
		{
			return it->second;
		}
	}

	return SAT_NONE;
}

void GUIElement::OnGuiEvent(int64_t eventToReact)
{
	//TODO 2: Search in the map for the event recieved. If found get the animation linked and determine if its a transition or an animation using SAT_SEPARATOR, 
	//then set currentStaticAnimation or currentTransition. Also set doingAnimation or doingTransition to false. 
	//NOTE: The parameter recived is a int64_t but you can use it as a staticAnim_or_transition.
	//On transition case we asume that all transitions are used to enable or disable the element so after setting the current transition check the active 
	//status of the element (status.active == true). If the element is active we want to disable it at the end of this transition so mark as true the mustDiable flag.

	if (this->eventsToReact & eventToReact)
	{
		std::map<gui_events, staticAnim_or_transition>::iterator it = transAndAnimations.find((gui_events)eventToReact);
		if (it != transAndAnimations.end())
		{
			staticAnim_or_transition tmp = it->second;
			if (tmp < SAT_SEPARATOR)
			{
				if (currentStaticAnimation == SAT_NONE)
				{
					currentStaticAnimation = tmp;
					doingAnimation = false;
				}
			}
			else if (tmp > SAT_SEPARATOR)
			{
				if (currentTransition == SAT_NONE)
				{
					currentTransition = tmp;
					doingTransition = false;
					//Will asume all transitions enable/disable.
					if (status.active) mustDisable = true;
				}
			}
		}
	}
	//-------
}

void GUIElement::Update(const GUIElement* mouseHover, const GUIElement* focus, float dt)
{
	//When updateing first do the element particular update overrided in each subtype.
	OnUpdate(mouseHover, focus, dt);

	//Then process the animations and transitions.
	if (currentStaticAnimation != SAT_NONE)
	{
		//Do here the animation according the active one.

		switch (currentStaticAnimation)
		{
		case SA_FLASH:
			FlashSA(dt);
			break;
		case SA_SHAKE:
			ShakeSA(dt);
			break;
		case SA_PULSE:
			PulseSA(dt);
			break;
		case SA_BOUNCE:
			BounceSA(dt);
			break;
		}
		
	}

	if (currentTransition != SAT_NONE)
	{
		//DO here the transition logic according the one active.

		switch (currentTransition)
		{
		case T_FADE:
			FadeT(dt);
			break;
		case T_DROP:
			DropT(dt);
			break;
		case T_FLY:
			FlyT(dt);
			break;
		case T_SLIDE:
			SlideT(dt);
			break;
		case T_MOVE_RIGHT:
			MoveRightT(dt);
			break;
		case T_MOVE_LEFT:
			MoveLeftT(dt);
			break;
		case T_MOVE_UP:
			MoveUpT(dt);
			break;
		case T_MOVE_DOWN:
			MoveDownT(dt);
			break;
		}
	}
	if (GetDraggable() && GetLClicked())
	{
		iPoint p;
		app->input->GetMousePosition(p.x, p.y);
		SetGlobalPos(p.x, p.y);
	}

}

void GUIElement::FlashSA(float dt)
{
	if (!doingAnimation)
	{
		animTimer.Start();
		currentAnimTim = 0;
		doingAnimation = true;
	}

	currentAnimTim = animTimer.Read();

	animTime = 500;
	float change_alpha = app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_SHAKE);

	change_alpha = CLAMP01(change_alpha);

	if (currentAnimTim < animTime)
	{
		alpha = 255 * (1-change_alpha);
	}
	else
	{
		alpha = 255;
		currentStaticAnimation = SAT_NONE;
		doingAnimation = false;
	}
}
void GUIElement::ShakeSA(float dt)
{
	//TODO 5: Now an animation.

	if (!doingAnimation)
	{
		//----
		animTimer.Start();
		currentAnimTim = 0;
		doingAnimation = true;
		//----
		animTime = 500;
	}

	//Update the time counter every frame (currentAnimeTime)
	//----
	currentAnimTim = animTimer.Read();
	//-----

	if (currentAnimTim < animTime)
	{
		//Set drawRect.x to rect.x - 25 * the value you get from the curve. use a SHAKE curve.
		drawRect.x = rect.x - 25 * app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_SHAKE);
	}
	else
	{
		//When the animation is over reset the drawRect position using the rect and make sure you left the currentAnimation variable to none.
		SetDrawPosition(rect.x, rect.y);
		currentStaticAnimation = SAT_NONE;
		doingAnimation = false;
	}
}
void GUIElement::PulseSA(float dt)
{
	if (!doingAnimation)
	{
		animTimer.Start();
		currentAnimTim = 0;
		doingAnimation = true;
		animTime = 500;
	}
	currentAnimTim = animTimer.Read();

	float time = (float)currentAnimTim / animTime;
	float change_alpha = app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_SLOW_MIDDLE);

	change_alpha = CLAMP01(change_alpha);

	if (currentAnimTim <= animTime/2)
	{
		alpha = 255 * (1 - change_alpha);
	}
	else if (time > animTime/2)
	{
		alpha = 255 * (change_alpha);
	}

	if (time >= 1)
	{
		alpha = 255;
		currentStaticAnimation = SAT_NONE;
		doingAnimation = false;
	}
}
void GUIElement::BounceSA(float dt)
{
	if (!doingAnimation)
	{
		animTimer.Start();
		currentAnimTim = 0;
		doingAnimation = true;
		animTime = 500;
	}
	currentAnimTim = animTimer.Read();

	if (currentAnimTim < animTime)
	{
		drawRect.y = rect.y - 25 * app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_SHAKE);
	}
	else
	{
		SetDrawPosition(rect.x, rect.y);
		currentStaticAnimation = SAT_NONE;
		doingAnimation = false;
	}
}

void GUIElement::FadeT(float dt)
{
	//TODO 3: Let's do the first transition, fade.
	if (!doingTransition)
	{
		//If doingTransition is false it means it's the first time FadeT is called so we must set the starting variables. 
		//We must reset the timer and the transition time counter (currentTransTime), now doingTransition is true and if mustDisable is false it means we are using fade to move alpha from 0 to 255 so make sure the alpha is 0. 
		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
		if (!mustDisable) alpha = 0;
		//----
	}

	currentTransTime = transTimer.Read();

	if (currentTransTime < transDuration)
	{
		//If time is less than duration trnsition is still on so get the alpha variation using curves. Use a slow midle curve type. The vaule you get from the curve will be the alpha variation for this frame.
		//After you get that variation you must clamp it from 0 to 1 (Check CLAMP01 define).
		float change_alpha = CLAMP01(app->gui->cBeizier->GetActualX(transDuration, currentTransTime, CB_SLOW_MIDDLE));
		//-----
		alpha = 255 * ((mustDisable) ? (1 - change_alpha) : (change_alpha));
	}
	else
	{
		//If time is greater than the duration the transition is over so now set currentTransition to none and set active to false if needed.
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}

	//When you are done compile and check the first image in the scene. it should disapear with a fade when you click on it and appear when you press Q.
}
void GUIElement::DropT(float dt)
{
	//TODO 4: Let's do an animation using scales!
	//The structure of the method is the same as fade but now will use curves a bit different.
	if (!doingTransition)
	{
		if (mustDisable)
		{
			//There are two iPoint variables called transOrigin and transDestination. Use them to set the goal of the transition and the origin. 
			//In this case the origin is the current scale stored in rect and the goal is to reduce it untill is 0 in Y direction. Store that information in those variables.
			transOrigin.create(rect.w, rect.h);
			transDestination.create(rect.w * 0.2, rect.h * 0.2);
		}
		else
		{
			//If we are on an enable case swap origin and the goal.
			transOrigin.create(drawRect.w, drawRect.h);
			transDestination.create(rect.w, rect.h);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();

	if (currentTransTime <= transDuration)
	{
		if (mustDisable)
		{
			//Set drawRect.h to transorigin.y + the value you get from the curve. Use GetActualPoint with a slow middle curve.
			drawRect.h = transOrigin.y + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, transDuration, currentTransTime, CB_SLOW_MIDDLE);
		}
		else
		{
			//Set drawRect.h to transorigin.y - the value you get from the curve. Use GetActualPoint with a slow middle curve.
			drawRect.h = transOrigin.y - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, transDuration, currentTransTime, CB_SLOW_MIDDLE);
		}
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		else
		{
			drawRect.h = rect.h;
		}
		return;
	}

}
void GUIElement::FlyT(float dt)
{
	if (!doingTransition)
	{
		if (mustDisable)
		{
			transOrigin.create(rect.x, rect.y);
			int screenRXBorderPos = app->win->GetWindowSize().x;
			transDestination.create(screenRXBorderPos, rect.y);
		}
		else
		{
			transOrigin.create(drawRect.x, drawRect.y);
			transDestination.create(rect.x, rect.y);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();
	if (currentTransTime <= 500)
	{
		if (mustDisable)
			drawRect.x = transOrigin.x - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 500, currentTransTime, CB_FLY);
		else
			drawRect.x = transOrigin.x + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 500, currentTransTime, CB_FLY);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}
}
void GUIElement::SlideT(float dt)
{
	if (!doingTransition)
	{
		transTimer.Start();
		currentAnimTim = 0;
		doingTransition = true;
	}
	currentAnimTim = transTimer.Read();

	animTime = 500;
	float time = (float)currentAnimTim / animTime;

	if (currentAnimTim < animTime)
	{
		if (mustDisable)
		{
			drawRect.h = rect.h - rect.h*app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_LINEAL);
		}
		else drawRect.h = rect.x + rect.h*app->gui->cBeizier->GetActualX(animTime, currentAnimTim, CB_LINEAL);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		doingTransition = false;

		if (mustDisable)
		{
			drawRect.h = 0;
			status.active = false;
			mustDisable = false;
		}
		else drawRect.h = rect.h;
		return;
	}

}
void GUIElement::MoveRightT(float dt)
{
	if (!doingTransition)
	{
		if (mustDisable)
		{
			transOrigin.create(rect.x, rect.y);
			int screenRXBorderPos = app->win->GetWindowSize().x;
			transDestination.create(screenRXBorderPos - rect.w, rect.y);
		}
		else
		{
			transOrigin.create(drawRect.x, drawRect.y);
			transDestination.create(rect.x, rect.y);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();
	if (currentTransTime <= 1000)
	{
		if(mustDisable)
			drawRect.x = transOrigin.x - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
		else
			drawRect.x = transOrigin.x + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}
}
void GUIElement::MoveLeftT(float dt)
{
	if (!doingTransition)
	{
		if (mustDisable)
		{
			transOrigin.create(rect.x, rect.y);
			transDestination.create(0, rect.y);
		}
		else
		{
			transOrigin.create(drawRect.x, drawRect.y);
			transDestination.create(rect.x, rect.y);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();
	if (currentTransTime <= 1000)
	{
		if (mustDisable)
			drawRect.x = transOrigin.x + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
		else
			drawRect.x = transOrigin.x - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}
}
void GUIElement::MoveUpT(float dt)
{
	if (!doingTransition)
	{
		if (mustDisable)
		{
			transOrigin.create(rect.x, rect.y);
			transDestination.create(rect.x, 0);
		}
		else
		{
			transOrigin.create(drawRect.x, drawRect.y);
			transDestination.create(rect.x, rect.y);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();
	if (currentTransTime <= 1000)
	{
		if (mustDisable)
			drawRect.y = transOrigin.y + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
		else
			drawRect.y = transOrigin.y - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}
}
void GUIElement::MoveDownT(float dt)
{
	if (!doingTransition)
	{
		if (mustDisable)
		{
			transOrigin.create(rect.x, rect.y);
			int screenBYBorderPos = app->win->GetWindowSize().y;
			transDestination.create(rect.x, screenBYBorderPos - rect.h);
		}
		else
		{
			transOrigin.create(drawRect.x, drawRect.y);
			transDestination.create(rect.x, rect.y);
		}

		transTimer.Start();
		currentTransTime = 0;
		doingTransition = true;
	}

	currentTransTime = transTimer.Read();
	if (currentTransTime <= 1000)
	{
		if (mustDisable)
			drawRect.y = transOrigin.y - app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
		else
			drawRect.y = transOrigin.y + app->gui->cBeizier->GetActualPoint(transOrigin, transDestination, 1000, currentTransTime, CB_EASE_INOUT_BACK);
	}
	else
	{
		currentTransTime = 0;
		currentTransition = SAT_NONE;
		if (mustDisable)
		{
			status.active = false;
			mustDisable = false;
		}
		return;
	}
}