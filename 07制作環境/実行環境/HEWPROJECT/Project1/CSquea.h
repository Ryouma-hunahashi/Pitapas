//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// マップと四角のゲームオブジェクトとの
// 当たり判定をとるために四辺と四頂点を
// 計算、代入する関数とメンバ変数を追加しました。
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once

#define SCALESIZE 1.0f
#include"CFloat3.h"
class CSquea
{
public:
	CFloat3 position = {0,0,0};
	CFloat3 rotate = {0,0,0};
	CFloat3 scale = {1,1,1};

	// 四辺の座標
	float Left;
	float Right;
	float Top;
	float Bottom;

	// 四角の四頂点
	CFloat3 Vertices[4] =
	{
	  { Left,  Top, 0},	// 左上
	  { Right, Top, 0},	// 右上
	  { Left,  Bottom, 0},	// 左下
	  { Right, Bottom, 0}	// 右下
	};

	// コンストラクタ
	// 四辺の座標を求め保存する
	CSquea();
	void VertexPos(void);

	
};

