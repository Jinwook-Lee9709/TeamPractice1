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
		SetScale({ -0.7f, 1.f });
		break;
	case Sides::Right:
		SetActive(true);
		SetScale({ 0.7f , 1.f });
		break;
	default:
		SetActive(false);
		break;
	}
}
