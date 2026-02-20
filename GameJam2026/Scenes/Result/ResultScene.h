#pragma once
#include "DxLib.h"

class ResultScene
{
public:
    ResultScene();

    void Initialize(int score, int correct);
    void Update();
    void Draw() const;
    void Finalize();

private:
    int background_;
    int bgm_;
    int se_;

    int score_;
    int correct_;
};