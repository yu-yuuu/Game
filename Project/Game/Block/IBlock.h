/**
 *
 * @file IBlock.h
 *
 * @brief ブロックに使用するインターフェースクラス
 *
 * @author Kato Yuki
 *
 * @date Kato Yuki
 *
 * @note 補足説明、メモ
 *
 */
#pragma once

#include "Game/Block/BlockType.h"

class IBlock
{
//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// デストラクタ
	virtual ~IBlock() = default;
	// ブロック種類の取得
	virtual KT::Block::Type GetType() = 0;
	// ブロック種類の設定
	virtual void SetType(KT::Block::Type type) = 0;
};
