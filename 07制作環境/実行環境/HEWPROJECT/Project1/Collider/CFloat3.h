//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// ゲームオブジェクトのステータスを管理するための
// クラスを追加しました。
// ※ここで言うステータス＝位置、大きさ、回転
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once
class CFloat3
{
public:
	float x, y, z;

	CFloat3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

	const CFloat3 operator+(const CFloat3)const; // フロート型３つ同時の足し算
	const CFloat3 operator-(const CFloat3)const; // フロート型３つ同時の引き算

};

