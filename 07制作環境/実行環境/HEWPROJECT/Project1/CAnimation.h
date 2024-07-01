#pragma once

#include "CDirectX.h"

// アニメーション機能のクラス
class CAnimation
{

public:
	// 列挙型
	// アニメーションパターン名
	enum PATTERN
	{
		NO_ANIMATION,
		PLAYER = 1,
		PLAYER_DEAD =2,
		FX_0_11 = 3,  // エフェクト用０～１１再生
		FX_0_19 = 4,  // エフェクト用０～１９再生
		FX_54_0 = 5,
		FX_0_54 = 6,
	};

private:
	// メンバー変数
	CDirectX::FLOAT_XY uv; // アニメーションのUV移動量を保存
	CDirectX::FLOAT_XY split;


	float animCounter = 0.0f; // アニメテーブルのカウンター

	// 再生するパターンIDを持つ変数
	int animPattern = 5;

public:
	// 再生速度を設定する
	float animSpeed = 0.1f; // 再生速度

	// 現在再生中かを表す変数
	bool isPlaying = true;


public:
	CAnimation(float x, float y) { split.x = x, split.y = y; }

	// メンバー関数
	void Update();

	// 再生するアニメーションを変更する

	// UV移動量を取得する
	CDirectX::FLOAT_XY GetUV();

	// 再生するパターンを変える
	void SetPattern(int pattern);

	void SetAnimCounter(float count);
};

