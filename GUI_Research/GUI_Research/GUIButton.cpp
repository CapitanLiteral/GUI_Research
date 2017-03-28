#include "GUIButton.h"
#include "M_Render.h"
#include "M_GUI.h"

GUIButton::GUIButton(GB_Rectangle<int> _position, 
					 GB_Rectangle<int> _standBySection, 
					 GB_Rectangle<int> _hoverSection, 
					 GB_Rectangle<int> _clickedSection,
					 std::string name,
					 int flags,
					 char* text, label_size _size) : GUIElement(name, flags)
{
	SetType(GUI_BUTTON);
	//SetRectangle(0, 100, 231, 71);
	SetRectangle(_position);
	clickedSection = _clickedSection;
	hoverSection = _hoverSection;
	standBySection = _standBySection;
	SetInteractive(true);
	SetCanFocus(true);

	image = new GUIImage(GetName());
	image->SetParent(this);
	image->SetRectangle(_position);	
	image->SetInteractive(false);
	image->SetCanFocus(false);
	image->SetSection(standBySection);

	label = new GUILabel(GetName());
	label->SetParent(this);
	//label->SetLocalPos(_position.x, _position.y);
	label->SetInteractive(false);
	label->SetCanFocus(false);
	
	SetGlobalPos(_position.x, _position.y);

	if (text != nullptr)
	{
		label->SetText(text, _size);
	}
	label->Center();
}
GUIButton::GUIButton(const GUIButton & btn, std::string name, int flags) : GUIElement(name, flags)
{
	SetType(GUI_BUTTON);
	SetRectangle(btn.GetLocalRect());
	standBySection = btn.standBySection;
	hoverSection = btn.hoverSection;
	clickedSection = btn.clickedSection;
	image = new GUIImage(*btn.image);
	image->SetParent(this);
	image->SetRectangle(btn.image->GetLocalRect());
	label = new GUILabel(*btn.label);
	label->SetParent(this);
	//label->SetRectangle(btn.label->GetLocalRect());
	label->Center();

}
GUIButton::~GUIButton()
{
}
void GUIButton::OnUpdate(const GUIElement * mouseHover, const GUIElement * focus, float dt)
{
	if (GetElementStatus().active)
	{
		if (GetElementStatus().statusChanged)
		{
			if (GetElementStatus().lClicked || GetElementStatus().rClicked)
			{
				image->SetSection(clickedSection);
			}
			else if (mouseHover == this)
			{
				image->SetSection(hoverSection);
			}
			else
			{
				image->SetSection(standBySection);
			}
		}

		//This goes the last 4ever
		SetStatusChanged(false);
	}
}
void GUIButton::Draw() const
{
	image->Draw();
	label->Draw();
}

void GUIButton::SetText(std::string txt, label_size size)
{
	label->SetText(txt.c_str(), size);
}

