#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"
#include <DxLib.h>

GameObjectBase::GameObjectBase()
    : owner_scene(nullptr),
    location(0.0f, 0.0f),
    image(-1),
    z_layer(0),
    mobility(eMobilityType::Stationary),
    flip_flag(false)
{
}

GameObjectBase::~GameObjectBase() {}

void GameObjectBase::Initialize() {}
void GameObjectBase::Update(float delta_second) {}
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
    if (image != -1) {
        Vector2D draw_pos = location + screen_offset;
        DrawGraph(static_cast<int>(draw_pos.x), static_cast<int>(draw_pos.y), image, TRUE);
    }
}
void GameObjectBase::Finalize() {}

void GameObjectBase::SetOwnerScene(SceneBase* scene) { owner_scene = scene; }
const Vector2D& GameObjectBase::GetLocation() const { return location; }
void GameObjectBase::SetLocation(const Vector2D& loc) { location = loc; }
int GameObjectBase::GetZLayer() const { return z_layer; }
eMobilityType GameObjectBase::GetMobility() const { return mobility; }