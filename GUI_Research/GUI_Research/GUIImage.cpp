#include "GUIImage.h"
#include "M_Render.h"
#include "M_GUI.h"

GUIImage::GUIImage(std::string name, int flags) : GUIElement(name, flags)
{
	SetType(GUI_IMAGE);
	atlas = app->gui->GetAtlas();
	//texture = nullptr;
}
GUIImage::GUIImage(const GUIImage & img, std::string name, int flags) : GUIElement(name, flags)
{
	SetType(GUI_IMAGE);
	atlas = app->gui->GetAtlas();
	SetRectangle(img.GetLocalRect());
	section = img.section;
}
GUIImage::~GUIImage()
{
}

void GUIImage::OnUpdate(const GUIElement * mouseHover, const GUIElement * focus, float dt)
{
}
void GUIImage::Draw() const
{
	app->render->Blit(atlas, &GetDrawRect().GetSDLrect(), &GetSection().GetSDLrect(),alpha);
}
GB_Rectangle<int> GUIImage::GetSection() const
{
	return section;
}
void GUIImage::SetSection(GB_Rectangle<int> _section)
{
	section = _section;
}
void GUIImage::SetSection(int _sectionX, int _sectionY, int _sectionW, int _sectionH)
{
	section.x = _sectionX;
	section.y = _sectionY;
	section.w = _sectionW;
	section.h = _sectionH;
}
