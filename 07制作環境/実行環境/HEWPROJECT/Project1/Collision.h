#pragma once
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// マップと四角のゲームオブジェクトとの
// 当たり判定を追加しました。
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
#include"CSquea.h"
#include"CCircle.h"
#include"CGameObject.h"
#include<math.h>

// 前方宣言
class CGameObject;

// 列挙体
// 当たった方向{当たってない、上、下、左、右};
enum CollisionDirection { COLLISION_NULL, COLLISION_UP, COLLISION_DOWN, COLLISION_LEFT, COLLISION_RIGHT };

// 四角のあたり判定
// 戻り値がCollisionDirectionになっているけどbool型でも戻り値の受け取りが出来る
// CollisionDirectionが列挙体なため戻る値は数値だから
CollisionDirection SquareCollision(const CGameObject*, const CGameObject*);

bool DoSquareCollision(const CGameObject* _rect1, const CGameObject* _rect2);

// 点と四角の当たり判定
bool DotSquareCollision(const CFloat3*, const CSquea*);

// 点と円の当たり判定
bool DotCircleCollision(const CFloat3&, const CCircle&);

