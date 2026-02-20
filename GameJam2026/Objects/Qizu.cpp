#include "Qizu.h"
#include "DxLib.h"

Qizu::Qizu()
{
	current = 0;
	selectIndex = 0;
	answered = false;
}

void Qizu::Load()
{
	char filename[64];

	for (int i = 0; i < QUESTION_MAX; i++)
	{
		sprintf_s(filename, "Question1.png", i);
		questionImg[i] = LoadGraph(filename);

		sprintf_s(filename, "Hint1.png", i);
		hintImg[i] = LoadGraph(filename);

		sprintf_s(filename, "Choice1.png", i);
		choiceImg[i][0] = LoadGraph(filename);

		sprintf_s(filename, "Choice1.png", i);
		choiceImg[i][1] = LoadGraph(filename);

		answer[i] = 1;
	}
}

void Qizu::Update()
{
    if (current >= QUESTION_MAX) return;

    int pad = GetJoypadInputState(DX_INPUT_PAD1);
    static int oldPad = 0;

    if (!answered)
    {
        if ((pad & PAD_INPUT_LEFT) && !(oldPad & PAD_INPUT_LEFT))
            selectIndex = 0;

        if ((pad & PAD_INPUT_RIGHT) && !(oldPad & PAD_INPUT_RIGHT))
            selectIndex = 1;

        if ((pad & PAD_INPUT_1) && !(oldPad & PAD_INPUT_1))
        {
            answered = true;
        }
    }
    else
    {
        if ((pad & PAD_INPUT_1) && !(oldPad & PAD_INPUT_1))
        {
            current++;
            selectIndex = 0;
            answered = false;
        }
    }

    oldPad = pad;
}

void Qizu::Draw()
{

    DrawGraph(0, 0, questionImg[current], TRUE);

    DrawGraph(0, 0, hintImg[current], TRUE);

    for (int i = 0; i < 2; i++)
    {
        int x = 100 + i * 100;
        int y = 50;

        DrawGraph(x, y, choiceImg[current][i], TRUE);
    }

    if (answer)
    {
        if (selectIndex == answer[current])
            DrawString(50, 50, "³", GetColor(255, 0, 0));
        else
            DrawString(50, 50, "•s", GetColor(0, 0, 255));

        DrawString(50, 50, "Aƒ{ƒ^ƒ“‚ÅŽŸ‚Ö", GetColor(255, 255, 255));
    }
}