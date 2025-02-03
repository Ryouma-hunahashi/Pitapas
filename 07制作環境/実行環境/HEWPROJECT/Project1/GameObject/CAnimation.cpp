#include "CAnimation.h"

void CAnimation::Update()
{
    // テーブルアニメーション…決められた順番で再生させるためのデータ
    // ※テーブル…何かの目的のために作られたデータの集まり
    int animTable[][80] =
    {
        // 何もアニメーションしないパターン
        { 0, -1 },

        // プレイヤーアニメーション
        {0,1,2,3,4,5,6,7,-1},

        // プレイヤー死亡アニメーション
        {0,1,2,3,4,5,6,7,-3},

        // エフェクト用０～１１まで再生
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -2 },

        // エフェクト用０～１９まで再生
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,-2},

        // 
        {0,1,2,3,4,5, 6,7,8,9,10, 11,12,13,14,15, 16,17,18,19,20, 21,22,23,24,25, 26,27,28,29,30, 31,32,33,34,35, -2},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,-1}
    };

    // 表示させるコマIDを取得
    int animID = animTable[animPattern][(int)animCounter];
    
    // uvサイズを求める
    uv.x = animID % static_cast<int>(split.x) / (split.x);
    uv.y = animID / static_cast<int>(split.x) / (split.y);


    // 再生中かどうか判定
    if (isPlaying)
    {
        // アニメーションのカウンターを進める
        animCounter += animSpeed;

        // 最初に戻る処理
        if (animTable[animPattern][(int)animCounter] == -1)// -1がループの合図
        {
            animCounter = 0.0f;
        }
        // 停止させる処理
        else if (animTable[animPattern][(int)animCounter] == -2)// -2が止める合図
        {
            animCounter = 0.0f;
            isPlaying = false;
        }
        else if (animTable[animPattern][(int)animCounter] == -3) // プレイヤー死亡時に使用
        {
            animCounter = 7;
            isPlaying = false;
        }
    }
}

CDirectX::FLOAT_XY CAnimation::GetUV()
{
    return uv;
}

void CAnimation::SetPattern(int pattern)
{
    animPattern = pattern;
}

void CAnimation::SetAnimCounter(float count)
{
    animCounter = count;
}
