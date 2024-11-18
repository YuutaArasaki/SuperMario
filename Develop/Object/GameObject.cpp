#include "GameObject.h"

void GameObject::Initialize()
{

}

void GameObject::Update(float delta_second)
{

}

void GameObject::Draw(const Vector2D& screen_offset) const
{

}

void GameObject::Finalize()
{

}

void GameObject::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& GameObject::GetLocation() const
{
	return location;
}

void GameObject::SetLocation(const Vector2D location)
{

}

const Collision& GameObject::GetCollision() const
{
	return collision;
}

const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

const bool GameObject::GetMobility() const
{
	return is_mobility;
}
