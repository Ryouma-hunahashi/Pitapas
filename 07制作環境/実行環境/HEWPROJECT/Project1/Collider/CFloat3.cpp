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
#include "CFloat3.h"

CFloat3::CFloat3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }

const CFloat3 CFloat3::operator+(const CFloat3 _pos) const
{
	return CFloat3(this->x + _pos.x, this->y + _pos.y, this->z + _pos.z);
}

const CFloat3 CFloat3::operator-(const CFloat3 _pos) const
{
	return CFloat3(this->x - _pos.x, this->y - _pos.y, this->z - _pos.z);
}
