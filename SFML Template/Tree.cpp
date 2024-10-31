#include "stdafx.h"
#include "Tree.h"
#include "Branch.h"
#include "EffectLog.h"
#include "Scene.h"

Tree::Tree(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
}

Tree::~Tree()
{
	Release();
}

Sides Tree::RandomSide() const
{
	int rand = Utils::RandomRange(0, 2);
	if (rand > 1)
		return Sides::None;
	return (Sides)rand;
}

void Tree::Init()
{
	Release();

	tree.setTexture(TEXTURE_MGR.Get(treeTexId), true);
	Utils::SetOrigin(tree, Origins::BC);

	branchTexId = VAR.BranchTexId;
	sf::Vector2f orginBranch;
	orginBranch.x = tree.getLocalBounds().width * -0.5f;
	sf::Texture& branchTex = TEXTURE_MGR.Get(branchTexId);
	orginBranch.y = branchTex.getSize().y * 0.5f;

	for (int i = 0; i < branchCount; ++i)
	{
		Branch* branch = new Branch(branchTexId);
		branch->SetOrigin(orginBranch);
		branch->Init();
		branch->SetSide(RandomSide());
		branches.push_back(branch);
	}
}

void Tree::Release()
{
	for (auto logEffect : logEffects)
	{
		effectLogPool.Return(logEffect);
		SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect);
	}
	logEffects.clear();

	for (auto branch : branches)
	{
		branch->Release();
		delete branch;
	}
	branches.clear();
}


void Tree::Reset()
{
	tree.setTexture(TEXTURE_MGR.Get(treeTexId), true);
	for (auto branch : branches)
	{
		if (VAR.SelectedPlayMode == PlayMode::Multi) {
			if (branch->GetSide() == Sides::Left) {
				branch->SetScale({ -0.7f, 1.f });
			}
			else if (branch->GetSide() == Sides::Right) {
				branch->SetScale({ 0.7f, 1.f });
			}
		}
		branch->Reset();
	}
	UpdateBranchPos();
	auto lastBranch = branches.front();
	lastBranch->SetSide(Sides::None);
}

void Tree::Update(float dt)
{
	for (auto branch : branches)
	{
		branch->Update(dt);
	}

	auto it = logEffects.begin();
	while (it != logEffects.end())
	{
		auto logEffect = *it;
		if (!logEffect->IsActive())
		{
			effectLogPool.Return(logEffect);
			SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect);
			it = logEffects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	for (auto branch : branches)
	{
		if (branch->IsActive())
		{
			branch->Draw(window);
		}
	}
	window.draw(tree);
}

void Tree::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	tree.setPosition(position);
	UpdateBranchPos();
}

void Tree::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	tree.setScale(this->scale);
}

void Tree::SetModSize(sf::Vector2f size)
{
	ModLogSize = size;
}

void Tree::SetBranchTexid(const std::string& texid)
{
	branchTexId = texid;
	for (auto branch : branches)
		branch->ChangeTexture(branchTexId);
}

void Tree::ClearEffectLog()
{
	for (auto log : logEffects)
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(log);
		effectLogPool.Return(log);
	}
	logEffects.clear();
}

Sides Tree::Chop(Sides side)
{
	if (side != Sides::None)
	{
		EffectLog* effect = effectLogPool.Take();
		SCENE_MGR.GetCurrentScene()->AddGo(effect);
		effect->SetOrigin(Origins::BC);
		effect->SetScale(ModLogSize);
		effect->SetPosition(position);
		if (VAR.SelectedPlayMode == PlayMode::Multi)
			effect->Fire({ side == Sides::Right ? -500.f : 500.f, -700.f });
		else
			effect->Fire({ side == Sides::Right ? -1000.f : 1000.f, -1000.f });
		
		logEffects.push_back(effect);
	}

	Branch* temp = branches.front();
	branches.pop_front();
	temp->SetSide(RandomSide());
	branches.push_back(temp);
	UpdateBranchPos();
	return branches.front()->GetSide();
}

void Tree::UpdateBranchPos()
{
	sf::Vector2f pos = position;
	for (auto branch : branches)
	{
		pos.y -= brachOffsetY;
		branch->SetPosition(pos);
	}
}

