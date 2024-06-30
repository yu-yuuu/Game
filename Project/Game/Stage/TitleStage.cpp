/**
 *
 * @file TitleStage.cpp
 *
 * @brief タイトルシーンステージを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "TitleStage.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/TitleScene.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param titleScene ：タイトルシーンのポインタ
 * @param stageNumber：ステージ番号
 * @param size       ：ステージサイズ
 */
TitleStage::TitleStage(TitleScene* titleScene, int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	, m_titleScene(titleScene)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
TitleStage::~TitleStage()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void TitleStage::Initialize()
{
	// ステージマネージャー取得
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();

	// タイトルシーン用ステージを取得
	KT::Stage::Size stageSize = stageManager->GetStageSize(GetStageNumber());
	KT::Stage::StageData stage = stageManager->CreateStage3D(GetStageNumber());

	// 文字ブロックのライト設定
	for (std::unique_ptr<Block>& block : stage)
	{
		if (
			block->GetType() == KT::Block::Type::GAME_START    ||
			block->GetType() == KT::Block::Type::GAME_START_A  ||
			block->GetType() == KT::Block::Type::GAME_START_SO ||
			block->GetType() == KT::Block::Type::GAME_START_BU ||
			block->GetType() == KT::Block::Type::GAME_END      ||
			block->GetType() == KT::Block::Type::GAME_END_O    ||
			block->GetType() == KT::Block::Type::GAME_END_WA   ||
			block->GetType() == KT::Block::Type::GAME_END_RU 
			)
		{
			block->Initialize([](IEffect* effect)
				{
					IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);

					if (lights)
					{
						// ライトの影響をなくす
						lights->SetAmbientLightColor(SimpleMath::Vector3::Zero);
						lights->SetLightEnabled(0, false);
						lights->SetLightEnabled(1, false);
						lights->SetLightEnabled(2, false);
					}

					BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
					{
						// 自己発光させる
						basicEffect->SetEmissiveColor(SimpleMath::Vector3::One);
					}
				}
			);
		}
	}
	// ステージデータ設定
	SetStageData(std::move(stage));
	// ステージの初期化
	Stage::Initialize();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void TitleStage::Update()
{
	// ステップタイマー取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();

	// 選択状態でないなら終了
	if (m_titleScene->GetTitleState() != TitleScene::TitleState::MODE_SELECT)
		return;

	// sinで点滅
	float brightness = std::sinf(static_cast<float>(stepTimer->GetTotalSeconds()) * FLASH_SPEED);
	// 0.75 ～ 1 の範囲に収める
	brightness = brightness * SELECT_BUTTON_BRIGHTNESS_MIN + SELECT_BUTTON_BRIGHTNESS_MAX;

	// タイトルシーンのモード取得
	TitleScene::NextMode mode = m_titleScene->GetMode();
	// ステージ取得
	KT::Stage::StageData* stage = GetStageData();
	// ボタンの色
	SimpleMath::Vector3 col;

	for (std::unique_ptr<Block>& block : *stage)
	{
		// 色を設定
		col = SimpleMath::Vector3(brightness, brightness, brightness);

		// 選択されていないなら暗くする
		if (mode == TitleScene::NextMode::PLAY)
		{
			if (block->GetType() == KT::Block::Type::GAME_END ||
				block->GetType() == KT::Block::Type::GAME_END_O ||
				block->GetType() == KT::Block::Type::GAME_END_WA ||
				block->GetType() == KT::Block::Type::GAME_END_RU)
			{
				col = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
			}
		}
		else if (mode == TitleScene::NextMode::EXIT)
		{
			if (block->GetType() == KT::Block::Type::GAME_START ||
				block->GetType() == KT::Block::Type::GAME_START_A ||
				block->GetType() == KT::Block::Type::GAME_START_SO ||
				block->GetType() == KT::Block::Type::GAME_START_BU )
			{
				col = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
			}
		}

		// 色を適用させる
		if (
			block->GetType() == KT::Block::Type::GAME_START ||
			block->GetType() == KT::Block::Type::GAME_START_A ||
			block->GetType() == KT::Block::Type::GAME_START_SO ||
			block->GetType() == KT::Block::Type::GAME_START_BU ||
			block->GetType() == KT::Block::Type::GAME_END ||
			block->GetType() == KT::Block::Type::GAME_END_O ||
			block->GetType() == KT::Block::Type::GAME_END_WA ||
			block->GetType() == KT::Block::Type::GAME_END_RU
			)
		{
			block->GetModel()->UpdateEffects([&](IEffect* effect)
				{
					BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
					{
						// 自己発光させる
						basicEffect->SetEmissiveColor(col);
					}
				}
			);
		}
	}
}
