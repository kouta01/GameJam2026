#pragma once
#include "../../Scenes/SceneBase.h"

class HelpScene : public SceneBase
{
public:
    HelpScene() {}
    ~HelpScene() {}

    void Initialize() override {}
    void Finalize() override {}

    eSceneType Update() override;
    void Draw() const override;

    eSceneType GetNowScene() const override
    {
        return eSceneType::E_HELP;
    }
};