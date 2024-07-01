//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// 円形のゲームオブジェクトのステータスを管理するための
// クラスを追加しました。
// ※ここで言うステータス＝位置、大きさ、回転、半径
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once
#include"CFloat3.h"
class CCircle
{
public:
	CFloat3 position;
	CFloat3 rotate;
	CFloat3 scale;
	float radius = 0.1f;
};