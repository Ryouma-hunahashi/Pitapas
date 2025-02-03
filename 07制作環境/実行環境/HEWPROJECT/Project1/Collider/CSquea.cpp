//ーーーーーーーーーーーーーーーーーーーーーーーーーーー
// 当たり判定プログラム
// 2023/12/12時点追加内容
// CRectクラスがDXの方で使えなかったため
// 名前が変更されました。
// マップと四角のゲームオブジェクトとの
// 当たり判定をとるために四辺と四頂点を
// 計算、代入する関数を追加しました。
// 
// 更新者：AT12B 07 岡林佑樹
// 
//ーーーーーーーーーーーーーーーーーーーーーーーーーーー

#include "CSquea.h"

CSquea::CSquea()
{
	VertexPos();
}

void CSquea::VertexPos(void)
{
	Left = this->position.x - this->scale.x/2;
	Right = this->position.x + this->scale.x/2;
	Top = this->position.y + this->scale.y/2;
	Bottom = this->position.y - this->scale.y/2;

	Vertices[0] = { Left,Top };
	Vertices[1] = { Right,Top };
	Vertices[2] = { Right,Bottom };
	Vertices[3] = { Left,Bottom };
}


