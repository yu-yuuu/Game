/**
 *
 * @file IScene.h
 *
 * @brief シーンを表すインターフェースクラス
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

class IScene
{
//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// デストラクタ
	virtual ~IScene() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;
	// 後処理
	virtual void Finalize() = 0;
	// シーンの切り替え
	virtual void ChangeScene() = 0;
};