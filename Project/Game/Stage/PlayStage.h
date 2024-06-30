/**
 *
 * @file PlayStage.h
 *
 * @brief プレイシーンで使用するステージのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#pragma once

#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"
#include "Game/Scene/PlayScene.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"


class PlayStage : public Stage
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステージデータ
	//KT::Stage::StageData m_stage;
	// 2Dステージに切り替えたか
	bool m_isChange2D;
	// カメラが向いている方向
	DirectX::SimpleMath::Vector3 m_cameraDirection;
	// 切り替え時の次元
	KT::GameParam::Dimension m_dimension;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	PlayStage(int stageNumber, KT::Stage::Size size);
	// デストラクタ
	~PlayStage();

	// 初期化
	void Initialize();
	// 更新
	void Update(bool IsSwitching);
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		std::function<void()> custom = nullptr
	);

	// 次元切り替え
	void ChangeDimension(
		KT::GameParam::Dimension dimension,
		const DirectX::SimpleMath::Vector3& cameraDirection
	);
	// スタートブロックの位置取得
	const DirectX::SimpleMath::Vector3& GetStartPosition();
	// ゴールブロックの位置取得
	const DirectX::SimpleMath::Vector3& GetGoalPosition();
	// 当たり判定を取るブロックを取得
	std::vector<Collider*> GetCollisionStage();
	// 2Dに切り替えてよいか
	bool IsChange2DStage(bool IsSwitching);
	// 3Dに切り替えてよいか
	bool IsChange3DStage(bool IsSwitching);

};