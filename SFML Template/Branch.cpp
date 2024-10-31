#include "stdafx.h"
#include "Branch.h"

Branch::Branch(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}	

void Branch::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::Left:
		SetActive(true);
		if(VAR.SelectedPlayMode == PlayMode::Multi)
			SetScale({ -0.7f, 1.f });
		else
			SetScale({ -1.f, 1.f });
		break;
	case Sides::Right:
		SetActive(true);
		if (VAR.SelectedPlayMode == PlayMode::Multi)
			SetScale({ 0.7f, 1.f });
		else
			SetScale({ 1.f, 1.f });
		break;
	default:
		SetActive(false);
		break;
	}
}
