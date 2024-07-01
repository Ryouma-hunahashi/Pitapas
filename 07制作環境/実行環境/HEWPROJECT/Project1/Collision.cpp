//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// マップと四角のゲームオブジェクトとの
// 当たり判定を追加しました。
// 前回状態で見つかったバグをいくつか直しました。
// CRectクラスを使っていた部分がCSqueaクラスに
// 置き換わっています。（中の処理に変化はなし）
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー

#include "Collision.h"
#include "CGameObject.h"

// マクロ定義
// マップチップ一つあたりのサイズ
#define CHIP_SIZE_X		(1)
#define CHIP_SIZE_Y		(1)

// 四角のあたり判定(当たった方向)
CollisionDirection SquareCollision(const CGameObject* _rect1, const CGameObject* _rect2)
{
	//for (int i = 0; i < 4; i++)
	//{
	//	// 一つ目のオブジェクトのベクトルを取得する
	//	CFloat3 VAn = _rect1->transform->Vertices[(i + 1 % 4)] - _rect1->transform->Vertices[i];

	//	for (int j = 0; j < 4; j++)
	//	{
	//		// 二つ目のオブジェクトのベクトルを取得する
	//		CFloat3 VBn = _rect2->transform->Vertices[(j + 1 % 4)] - _rect2->transform->Vertices[j];

	//		// 二つのオブジェクトの外積を求める
	//		float crossTorect = VAn.x * VBn.y - VAn.y * VBn.x;

	//		// 0であれば平行であるため次に行く
	//		if (crossTorect == 0)continue;

	//		// 2線の始点から終点のベクトルを求める
	//		CFloat3 crossVec = _rect2->transform->Vertices[j] - _rect1->transform->Vertices[i];
	//		// 始点同士のベクトルと各辺のベクトルの外積を計算する
	//		float crossVtoV1 = crossVec.x * VAn.y - crossVec.y * VAn.x;
	//		float crossVtoV2 = crossVec.x * VBn.y - crossVec.y * VBn.x;

	//		// 交差判定
	//		float cross1 = crossVtoV2 / crossTorect;
	//		float cross2 = crossVtoV1 / crossTorect;

	//		// 誤差を容認する
	//		const float eos = 0.00001f;

	//		// 交差していなければ、次の判定へ
	//		if (cross1 + eos < 0 || cross1 - eos>1 || cross2 + eos < 0 || cross2 - eos>1)
	//			continue;

	//		// 全て合致していなければ交差している
	//		return COLLISION_UP;

	//	}
	//}






	float dis_x = fabsf(_rect1->transform->position.x - _rect2->transform->position.x);
	float dis_y = fabsf(_rect1->transform->position.y - _rect2->transform->position.y);

	float size_x = fabsf(_rect1->transform->scale.x + _rect2->transform->scale.x) / 2;
	float size_y = fabsf(_rect1->transform->scale.y + _rect2->transform->scale.y) / 2;

	if (dis_x < size_x)
	{
		if (dis_y < size_y)
		{
			float o_x = size_x - dis_x;
			float o_y = size_y - dis_y;

			if (o_x < o_y)
			{
				return (_rect1->transform->position.x < _rect2->transform->position.x) ? COLLISION_LEFT : COLLISION_RIGHT;
			}
			else
			{
				return (_rect1->transform->position.y < _rect2->transform->position.y) ? COLLISION_DOWN : COLLISION_UP;
			}
		}
	}
	return COLLISION_NULL;

	// 二つのオブジェクトの距離を測る
	CFloat3 distance(fabsf(_rect1->transform->position.x - _rect2->transform->position.x), fabsf(_rect1->transform->position.y - _rect2->transform->position.y));

	// 二つのオブジェクトサイズの合計値
	CFloat3 sizeSum((fabsf(_rect1->transform->scale.x) + fabsf(_rect2->transform->scale.x))/2.0f, (fabsf(_rect1->transform->scale.y) + fabsf(_rect2->transform->scale.y))/2.0f);

	float disSqLength = distance.x * distance.x + distance.y * distance.y;
	float sizeSqLength = sizeSum.x * sizeSum.x + sizeSum.y * sizeSum.y;

	// 距離がサイズよりも小さければ
	if (disSqLength <= sizeSqLength)
	{
		// ベクトルを計算
		CFloat3 vector = _rect1->transform->position - _rect2->transform->position;
		// Yの絶対値のほうが大きければ
		if (fabsf(vector.x) <= fabsf(vector.y))
		{
			// ＋なら上を返す
			if (vector.y > 0)
			{
				//std::cout << "上に当たったよ" << std::endl;
				return CollisionDirection::COLLISION_UP;
			}
			else
			{
				// ーなら下を返す
				//std::cout << "下に当たったよ" << std::endl;
				return CollisionDirection::COLLISION_DOWN;
			}
		}
		// Xの絶対値の方が大きければ
		else
		{
			// ＋なら右を返す
			if (vector.x > 0)
			{
				//std::cout << "右に当たったよ" << std::endl;
				return CollisionDirection::COLLISION_RIGHT;
			}
			else
			{
				// ーなら左を返す
				//std::cout << "左に当たったよ" << std::endl;
				return CollisionDirection::COLLISION_LEFT;
			}
		}

	}

	// どこにも当たっていない場合
	//std::cout << "当たってないよ" << std::endl;
	return COLLISION_NULL;
}

bool DoSquareCollision(const CGameObject* _rect1, const CGameObject* _rect2)
{
	for (int i = 0; i < 4; i++)
	{
		// 一つ目のオブジェクトのベクトルを取得する
		CFloat3 VAn = _rect1->transform->Vertices[(i + 1) % 4] - _rect1->transform->Vertices[i];

		for (int j = 0; j < 4; j++)
		{
			// 二つ目のオブジェクトのベクトルを取得する
			CFloat3 VBn = _rect2->transform->Vertices[(j + 1)% 4] - _rect2->transform->Vertices[j];

			// 二つのオブジェクトの外積を求める
			float crossTorect = VAn.x * VBn.y - VAn.y * VBn.x;

			// 0であれば平行であるため次に行く
			if (crossTorect == 0)continue;

			// 2線の始点から終点のベクトルを求める
			CFloat3 crossVec = _rect2->transform->Vertices[j] - _rect1->transform->Vertices[i];
			// 始点同士のベクトルと各辺のベクトルの外積を計算する
			float crossVtoV1 = crossVec.x * VAn.y - crossVec.y * VAn.x;
			float crossVtoV2 = crossVec.x * VBn.y - crossVec.y * VBn.x;

			// 交差判定
			float cross1 = crossVtoV2 / crossTorect;
			float cross2 = crossVtoV1 / crossTorect;

			// 誤差を容認する
			const float eps = 0.001f;

			// 交差していなければ、次の判定へ
			if (cross1 + eps < 0 || cross1 - eps > 1 || cross2 + eps < 0 || cross2 - eps > 1)
				continue;

			// 全て合致していなければ交差している
			return true;

		}
	}

	return false;
}


// 点と四角の当たり判定
// 使用例はカーソルとオブジェクトの当たり判定等
// 点の位置（座標）とオブジェクト（位置、大きさ）を引数として受け取り
// 当たっているかの判定をbool型（true,false）で返す
bool DotSquareCollision(const CFloat3* _dot, const CSquea* _rect)
{
	// 点の位置が四角の中に入っているか？
	// （右端より点の位置が左かつ、左端より点の位置が右かつ、
	// 　上端より点の位置が下かつ、下端より点の位置が上ならtrueを返す）
	return (_rect->position.x + _rect->scale.x/2 > _dot->x && 
			_rect->position.x - _rect->scale.x/2 < _dot->x&&
			_rect->position.y + _rect->scale.y/2 > _dot->y && 
			_rect->position.y - _rect->scale.y/2 < _dot->y);
}

// 点と円の当たり判定
bool DotCircleCollision(const CFloat3& _dot, const CCircle& _circle)
{
	// 距離を計算
	CFloat3 distance = _dot - _circle.position;

	// 距離を二乗する
	float dtc = distance.x * distance.x + distance.y * distance.y;

	// 距離が円の半径より小さければture
	return (dtc <= _circle.radius);

}

