/**
 *
 * @file Player.cpp
 *
 * @brief プレイヤーを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/13
 *
 */
#include "pch.h"
#include "Player.h"
#include "Effects.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

#include "Game/MyLibrary/Composite/ModelComposite.h"
#include "Game/Player/Strategy/PlayerStrategy2D.h"
#include "Game/Player/Strategy/PlayerStrategy3D.h"

#include "Game/MyLibrary/Collision/Collision.h"
#include "Game/MyLibrary/Collision/Collider.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/Block/Block.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ（プレイシーン）
 *
 * @param playScene：プレイシーンのポインタ
 * @param spawnPosition：初期位置
 */
Player::Player(PlayScene* playScene, DirectX::SimpleMath::Vector3 spawnPosition)
	: m_playScene(playScene)
	, m_playerStrategy(nullptr)
	, m_modelComposite{}
	, m_collider()
	, m_velocity()
	, m_moveForward()
	, m_moveRight()
	, m_warpPosition()
	, m_spawnPosition(spawnPosition)
	, m_hitDirection(0)
	, m_isHit(false)
	, m_isJump(false)
	, m_onGround(false)
	, m_moveInput(0)
	, m_isFailWarp(false)
	, m_overlapGhost(nullptr)
	, m_camDir()
	, m_animeTimer(0.0f)
	, m_animeSin(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief コンストラクタ（リザルトシーン）
 *
 * @param なし
 */
Player::Player(DirectX::SimpleMath::Vector3 spawnPosition)
	: m_playScene(nullptr)
	, m_playerStrategy(nullptr)
	, m_modelComposite{}
	, m_collider()
	, m_velocity()
	, m_moveForward()
	, m_moveRight()
	, m_warpPosition()
	, m_spawnPosition(spawnPosition)
	, m_hitDirection(0)
	, m_isHit(false)
	, m_isJump(false)
	, m_onGround(false)
	, m_moveInput(0)
	, m_isFailWarp(false)
	, m_overlapGhost(nullptr)
	, m_camDir()
	, m_animeTimer(0.0f)
	, m_animeSin(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
Player::~Player()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void Player::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{	
	// 使用しているシーンで処理を切り替える
	if (m_playScene) PlaySceneInitialize();
	else             ResultSceneInitialize();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void Player::Update()
{
	// 使用しているシーンで更新処理を切り替える
	if (m_playScene) PlaySceneUpdate();
	else             ResultSceneUpdate();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  view        ：ビュー行列
 * @param  projection  ：射影行列
 * @return なし
 */
void Player::Render(
	DirectX::SimpleMath::Matrix view, 
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom)
{
	// モデル描画
	m_modelComposite[ROOT]->Update(GetWorldMatrix());
	m_modelComposite[ROOT]->Render(view, projection, custom);
}


//------------------------------------------------------------------
/**
 * @brief シルエット描画
 *
 * @param  view        ：ビュー行列
 * @param  projection  ：射影行列
 * @return なし
 */
void Player::RenderSilhouette(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	// モデル描画
	m_modelComposite[ROOT]->Update(GetWorldMatrix());
	m_modelComposite[ROOT]->Render(view, projection, custom);
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void Player::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief モデル設定
 *
 * @param  なし
 * @return なし
 */
void Player::ModelSetting()
{
	// 名前空間別名宣言
	using namespace KT::Model;

	// リソースマネージャー取得
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();

	// プレイヤーモデル設定
	m_modelComposite[ROOT]  = std::make_unique<ModelComposite>(nullptr, SimpleMath::Vector3::Zero);
	m_modelComposite[BODY]  = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_BODY), BODY_LOCAL_POSITION);
	m_modelComposite[HEAD]  = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_HEAD), HEAD_LOCAL_POSITION);
	m_modelComposite[ARM_L] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_ARM_L), ARM_L_LOCAL_POSITION);
	m_modelComposite[ARM_R] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_ARM_R), ARM_R_LOCAL_POSITION);
	m_modelComposite[LEG_L] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_LEG_L), LEG_L_LOCAL_POSITION);
	m_modelComposite[LEG_R] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_LEG_R), LEG_R_LOCAL_POSITION);
	// プレイヤーの親子設定
	m_modelComposite[ROOT]->SetChild(m_modelComposite[BODY].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[HEAD].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[ARM_L].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[ARM_R].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[LEG_L].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[LEG_R].get());
	// エフェクト設定
	m_modelComposite[ROOT]->UpdateEffects(
		[](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ライトを適応させる
				lights->SetAmbientLightColor(SimpleMath::Vector3::One);
				lights->SetLightEnabled(0, true);
				lights->SetLightEnabled(1, true);
				lights->SetLightEnabled(2, true);
			}
		}
	);
}

//------------------------------------------------------------------
/**
 * @brief プレイシーンの初期化処理
 *
 * @param  なし
 * @return なし
 */
void Player::PlaySceneInitialize()
{
	// 当たり判定図形作成
	m_collider = std::make_unique<BoxCollider>(GetPosition(), PLAYER_COLLIDER_SIZE, true);
	// ゲームオブジェクト設定
	m_collider->SetGameObject(this);
	// 初期位置設定
	m_spawnPosition.y += m_collider->GetExtents().y;
	SetPosition(m_spawnPosition);
	// 初期機能設定
	m_playerStrategy = std::make_unique<PlayerStrategy3D>(this);
	// モデル設定
	ModelSetting();
}

//------------------------------------------------------------------
/**
 * @brief リザルトシーンの初期化処理
 *
 * @param  なし
 * @return なし
 */
void Player::ResultSceneInitialize()
{
	// 当たり判定図形作成
	m_collider = std::make_unique<BoxCollider>(GetPosition(), PLAYER_COLLIDER_SIZE, true);
	// ゲームオブジェクト設定
	m_collider->SetGameObject(this);
	// 初期位置設定
	m_spawnPosition.y += m_collider->GetExtents().y;
	SetPosition(m_spawnPosition);
	// モデル設定
	ModelSetting();
}

//------------------------------------------------------------------
/**
 * @brief プレイシーンの更新処理
 *
 * @param  なし
 * @return なし
 */
void Player::PlaySceneUpdate()
{
	// 変数リセット
	m_isHit        = false;   // 接触フラグ
	m_isFailWarp   = false;   // ワープ失敗フラグ
	m_overlapGhost = nullptr; // 重なったゴースト床ブロック

	// 機能クラスの更新
	m_playerStrategy->Update();
	// 移動処理
	Move();
	// 重力処理
	Gravity();
	// 速度調整
	AdjustmentVelocity();
	// 当たり判定移動
	m_collider->SetPosition(GetPosition() + m_velocity);
	// 歩きアニメーション
	WalkAnimation();
}

//------------------------------------------------------------------
/**
 * @brief リザルトシーンの更新処理
 *
 * @param  なし
 * @return なし
 */
void Player::ResultSceneUpdate()
{
	// 喜ぶアニメーション
	HappyAnimation();
}

//------------------------------------------------------------------
/**
 * @brief 速度調整
 *
 * @param  なし
 * @return なし
 */
void Player::AdjustmentVelocity()
{
	// 正規化して斜めで加速しないようにする
	SimpleMath::Vector3 velNorm;
	m_velocity.Normalize(velNorm);
	velNorm *= MOVE_SPEED;
	// 縦の移動量はそのまま
	SetVelocity({ velNorm.x, m_velocity.y, velNorm.z });
}

//------------------------------------------------------------------
/**
 * @brief 移動処理
 *
 * @param  なし
 * @return なし
 */
void Player::Move()
{
	// 速度受け取り用
	SimpleMath::Vector3 velocity;

	// 奥
	if (m_moveInput & KT::GameParam::InputDirection::FORWARD) velocity += m_moveForward * Player::MOVE_SPEED;
	// 手前
	if (m_moveInput & KT::GameParam::InputDirection::BACK)    velocity -= m_moveForward * Player::MOVE_SPEED;
	// 右
	if (m_moveInput & KT::GameParam::InputDirection::RIGHT)   velocity += m_moveRight * Player::MOVE_SPEED;
	// 左
	if (m_moveInput & KT::GameParam::InputDirection::LEFT)    velocity -= m_moveRight * Player::MOVE_SPEED;

	// 入力があるときは処理を行う
	if (m_moveInput != 0)
	{
		// フラグ初期化
		m_moveInput = 0;
		// プレイヤーを移動方向に向かせる
		TurnHeading(velocity);
	}

	// 速度設定
	SimpleMath::Vector3 vel = GetVelocity();
	SetVelocity(velocity.x, vel.y, velocity.z);
}

//------------------------------------------------------------------
/**
 * @brief ジャンプ処理
 *
 * @param  なし
 * @return なし
 */
void Player::Jump()
{
	// ジャンプが可能か
	if (!IsJump()) return;

	// ジャンプ力を速度に加える
 	m_velocity.y += JUMP_POWER;
	// フラグを立てる
	m_isJump = true;
	// SEを流す
	GameResource::GetInstance()->GetResourceManager()->
		PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_JUMP);
}

//------------------------------------------------------------------
/**
 * @brief 重力処理
 *
 * @param  なし
 * @return なし
 */
void Player::Gravity()
{
	m_velocity.y -= GRAVITY;
}

//------------------------------------------------------------------
/**
 * @brief ワープ処理
 *
 * @param  isSwitchFail：切替に失敗しているか
 * @return なし
 */
void Player::Warp(bool isSwitchFail)
{
	// 現在の位置取得
	DirectX::SimpleMath::Vector3 position = GetPosition();
	// ワープ移動する方向を0にする
	position *= KT::MyUtility::InverseFlag(m_camDir);
	// ワープ移動する方向のみに
	m_warpPosition *= KT::MyUtility::AbsVector(m_camDir);

	// ワープポイントと重なっていたブロックの
	// 視点方向の位置のずれを計算	
	if (!isSwitchFail && m_overlapGhost != nullptr)
	{
		SimpleMath::Vector3 offsetWarpPoint = m_warpPosition * KT::MyUtility::AbsVector(m_camDir);
		SimpleMath::Vector3 offsetBlock     = m_overlapGhost->GetPosition() * KT::MyUtility::AbsVector(m_camDir);

		if ((offsetWarpPoint - offsetBlock).LengthSquared() <= std::numeric_limits<float>::epsilon())
		{
			m_warpPosition += -m_camDir * SimpleMath::Vector3::One;
			m_isFailWarp = true;
		}
		else
		{
			m_isFailWarp = false;
		}
	}
	// 位置を設定
	SetPosition(position + m_warpPosition);
	// ワープポイントリセット
	m_warpPosition = GetPosition();
}

//------------------------------------------------------------------
/**
 * @brief 奈落への落下確認
 *
 * @param  なし
 * @return bool：奈落に落下したか
 */
bool Player::FallAbyssCheck()
{
	// 2D見下ろしの時
	if (m_playScene->Is2D() && m_playScene->IsTopDown())
	{
		// 当たっていなかったら落下判定
		return !m_isHit;
	}
	// 3D, 2D横視点の時
	else
	{
		// 一定高さより下なら落下判定
		return GetPosition().y < RESPAWN_HEIGHT;
	}
}

//------------------------------------------------------------------
/**
 * @brief 復活処理
 *
 * @param  なし
 * @return なし
 */
void Player::Respawn()
{
	// 2Dなら3Dへ切り替える
	if(m_playScene->Is2D())
	{
		m_onGround = true;
		m_playScene->ChangeDimension(false);
	}

	// 復活位置設定
	SetPosition(m_spawnPosition);
	// プレイヤーを停止させる
	Stop();
}

//------------------------------------------------------------------
/**
 * @brief 停止処理
 *
 * @param  なし
 * @return なし
 */
void Player::Stop()
{
	m_velocity = SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief 衝突時処理
 *
 * @param  gameObject：当たったオブジェクト
 * @return なし
 */
void Player::OnCollision(GameObject* gameObject)
{
	// ブロックを取得
	Block* block = dynamic_cast<Block*>(gameObject);
	// 種類を取得
	KT::Block::Type type = block->GetType();
	// ブロックの判定ボックス取得
	BoxCollider* blockBox = dynamic_cast<BoxCollider*>(block->GetCollider());
	// プレイヤーのボックスコライダー取得
	BoxCollider* playerBox = dynamic_cast<BoxCollider*>(m_collider.get());
	// 押し返し処理を行うか
	bool isExecute = true;

	// 2Dで床ブロック
	if (m_playScene->Is2D() && type == KT::Block::Type::GHOST_FLOOR)
	{
		// 見下ろし視点
		if (m_playScene->IsTopDown())
		{
			// 重力を打ち消す
			SimpleMath::Vector3 pos = GetPosition();
			SimpleMath::Vector3 colPos = playerBox->GetPosition();
			colPos.y = pos.y;
			playerBox->SetPosition(colPos);
			m_velocity.y = 0.0f;
			// ワープポイント設定
			m_warpPosition = gameObject->GetPosition();
			m_warpPosition.y += (playerBox->GetExtents().y + blockBox->GetExtents().y);
			// 接触フラグを立てる
			m_isHit = true;
			// 押し返し処理を行わない
			isExecute = false;
			// 最終的な位置を設定
			SetPosition(playerBox->GetPosition());
		}
		// 横視点
		else
		{
			// プレイヤーの下の位置を取得
			SimpleMath::Vector3 min, max;
			playerBox->GetCorners(min, max);
			float playerBottom = min.y;
			// ブロックの上に位置を取得
			blockBox->GetCorners(min, max);
			float blockTop = max.y;

			// プレイヤーがブロックの上部より一定範囲内の高さにいる &&
			// プレイヤーが下降中　でないとき
			if (!(std::fabsf(playerBottom - blockTop) <= KT::GameParam::GHOST_FLOOR_CHECK_HEIGHT && m_velocity.y < 0.0f))
			{
				// プレイヤーに重なっているか確認
				if (CheckOverLapGhostBlock(blockBox))
				{
					m_overlapGhost = gameObject;
				}
				// 押し返し処理を行わない
				isExecute = false;
			}
		}
	}
	// 2Dでゴーストブロック
	else if (m_playScene->Is2D() && type == KT::Block::Type::GHOST)
	{
		// プレイヤーに重なっているか確認
		if (CheckOverLapGhostBlock(blockBox))
		{
			m_overlapGhost = gameObject;
		}
		// 押し返し処理を行わない
		isExecute = false;
	}
	// ゴールブロックの時
	else if (type == KT::Block::Type::GOAL)
	{
		// プレイヤー停止
		Stop();
		// プレイシーンのゴール処理を実行
		m_playScene->ArrivalGoal();
	}

	// 押し返し処理
	if (isExecute)
	{
		// 接触フラグを立てる
		m_isHit = true;
		// 当たった方向を割り出す
		int hitDir = Collision::GetHitDirection(m_playScene->Is2D(), m_camDir, *playerBox, *blockBox);
		// 押し返し処理
		CollisionResponse(hitDir, playerBox, blockBox);
		// 最終的な位置を設定
		SetPosition(playerBox->GetPosition());
		// 当たった方向による処理
		if (hitDir & Collision::Bottom)
		{
			// 地面の上にいる
			m_onGround = true;
			// ジャンプフラグを折る
			m_isJump = false;
			// ワープポイントの設定
			m_warpPosition = blockBox->GetPosition();
			m_warpPosition.y += (playerBox->GetExtents() + blockBox->GetExtents()).y;
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief 衝突応答
 *
 * @param  hitDir   ：当たった方向
 * @param  playerBox：プレイヤーの当たり判定ボックス
 * @param  objBox   ：オブジェクトの当たり判定ボックス
 * @return なし
 */
void Player::CollisionResponse(const int& hitDir, BoxCollider* playerBox, BoxCollider* objBox)
{
	// 押し返す量を計算する
	SimpleMath::Vector3 push = playerBox->GetExtents() + objBox->GetExtents();
	// プレイヤーの当たり判定位置
	SimpleMath::Vector3 playerPos = playerBox->GetPosition();
	// 当たったオブジェクトの当たり判定位置
	SimpleMath::Vector3 objPos = objBox->GetPosition();
	
	// 押し返し処理
	switch (hitDir)
	{
	// 上に当たった
	case Collision::Top:    playerPos.y = objPos.y - push.y; m_velocity.y = 0.0f; break;
	// 下に当たった
	case Collision::Bottom: playerPos.y = objPos.y + push.y; m_velocity.y = 0.0f; break;
	// 右に当たった
	case Collision::Right:  playerPos.x = objPos.x - push.x; m_velocity.x = 0.0f; break;
	// 左に当たった
	case Collision::Left:   playerPos.x = objPos.x + push.x; m_velocity.x = 0.0f; break;
	// 正面（奥）に当たった
	case Collision::Front:  playerPos.z = objPos.z + push.z; m_velocity.z = 0.0f; break;
	// 後ろに当たった
	case Collision::Back:   playerPos.z = objPos.z - push.z; m_velocity.z = 0.0f; break;
	default: break;
	}
	// 押し出した位置を設定
	playerBox->SetPosition(playerPos);
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定後の更新処理
 *
 * @param  なし
 * @return なし
 */
void Player::CollisionAfterUpdate()
{
	// オブジェクトに接触していない
	if (!m_isHit)
	{
		// 地面に触れていない
		m_onGround = false;
		// 速度を加える
		SetPosition(GetPosition() + m_velocity);
	}
	// 奈落へ落下していたら復活させる
	if (FallAbyssCheck()) Respawn();
}

//------------------------------------------------------------------
/**
 * @brief プレイヤーにゴースト系ブロックが重なっているかを確認する
 *
 * @param  blockBox：プレイヤーに当たったブロックのコライダー
 * @return true ：重なっている
 * @return false：重なっていない
 */
bool Player::CheckOverLapGhostBlock(BoxCollider* blockBox)
{
	// ブロックの半径を取得
	SimpleMath::Vector3 range = blockBox->GetExtents();
	// プレイヤーとブロックの距離を計算する
	SimpleMath::Vector3 dist = GetPosition() - blockBox->GetPosition();
	// 使用する方向のみにする
	range *= KT::MyUtility::InverseFlag(m_camDir);
	dist *= KT::MyUtility::InverseFlag(m_camDir);
	// プレイヤーがブロックの半径内に居るか判定
	return KT::MyUtility::AbsVector(dist).LengthSquared() < (range).LengthSquared();
}

//------------------------------------------------------------------
/**
 * @brief 次元切り替え
 *
 * @param  dimension      ：現在の次元
 * @param  isSwitchFail   ：切り替え失敗時か
 * @return なし
 */
void Player::ChangeDimension(
	KT::GameParam::Dimension dimension,
	bool isSwitchFail)
{
	// 2Dへ切り替え
	if (dimension == KT::GameParam::Dimension::_3D)
	{
		m_playerStrategy.reset(new PlayerStrategy2D(this));
	}
	// 3Dへ切り替え
	else
	{
		m_playerStrategy.reset(new PlayerStrategy3D(this));
		// ワープ処理
		Warp(isSwitchFail);
	}
}

//------------------------------------------------------------------
/**
 * @brief 移動方向ベクトル作成
 *
 * @param  dir ：カメラの方向ベクトル
 * @param  up ：カメラの頭の向き
 * @return なし
 */
void Player::CreateMoveDirection(
	const DirectX::SimpleMath::Vector3& dir,
	const DirectX::SimpleMath::Vector3& up)
{
	// カメラの向きを受け取る
	m_camDir = dir;
	// カメラへのベクトルとカメラの頭の向きから右向きベクトルを作成する
	SimpleMath::Vector3 cross = dir.Cross(up);
	cross.Normalize(m_moveRight);
	// 右向きベクトルを90度左に回し前方ベクトルを作成する
	m_moveForward = SimpleMath::Vector3(m_moveRight.z, 0.0f, -m_moveRight.x);
	// 誤差を消す
	m_moveForward = KT::MyUtility::ModVector(m_moveForward);
	m_moveRight   = KT::MyUtility::ModVector(m_moveRight);
}

//------------------------------------------------------------------
/**
 * @brief 歩きアニメーション
 *
 * @param  なし
 * @return なし
 */
void Player::WalkAnimation()
{
	// 横の移動量取得
	float movement = std::fabsf(m_velocity.x) + std::fabsf(m_velocity.z);

	// 移動しているか確認
	if (movement > std::numeric_limits<float>::epsilon())
	{
		// アニメーションタイマー進行
		m_animeTimer += ANIME_TIMER;
		// アニメーション用サインカーブ更新
		m_animeSin = std::sinf(m_animeTimer);
	}
	else
	{
		// 操作していない時は徐々に0に近づける
		m_animeSin *= WALK_ANIME_ATTENUATION;
		// ほぼゼロならゼロに
		if (std::fabsf(m_animeSin) <= std::numeric_limits<float>::epsilon()) m_animeSin = 0.0f;
	}
	// 歩きアニメーション
	m_modelComposite[ARM_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX( m_animeSin * WALK_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[ARM_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(-m_animeSin * WALK_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[LEG_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(-m_animeSin * WALK_ANIME_ADJUSTMENT_LEG));
	m_modelComposite[LEG_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX( m_animeSin * WALK_ANIME_ADJUSTMENT_LEG));
}

//------------------------------------------------------------------
/**
 * @brief 喜びアニメーション
 *
 * @param  なし
 * @return なし
 */
void Player::HappyAnimation()
{
	// アニメーションタイマー進行
	m_animeTimer += ANIME_TIMER;
	// アニメーション用サインカーブ更新
	m_animeSin = std::sinf(m_animeTimer * HAPPY_ANIME_ADJUSTMENT_SPEED);
	m_animeSin = std::max(m_animeSin, 0.0f);
	// 腕を振る
	m_modelComposite[ARM_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(m_animeSin * HAPPY_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[ARM_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(m_animeSin * HAPPY_ANIME_ADJUSTMENT_ARM));
	// ジャンプ
	m_modelComposite[ROOT]->SetTransformMatrix(SimpleMath::Matrix::CreateTranslation(0.0f, m_animeSin * HAPPY_ANIME_ADJUSTMENT_JUMP, 0.0f));
}

//------------------------------------------------------------------
/**
 * @brief シーンポインタ取得
 *
 * @param  なし
 * @return TestScene*：シーンへのポインタ
 */
PlayScene* Player::GetScene() const
{
	return m_playScene;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定取得
 *
 * @param なし
 * @return Collider*：当たり判定へのポインタ
 */
Collider* Player::GetCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定箱取得
 *
 * @param なし
 * @return BoxCollider*：当たり判定箱へのポインタ
 */
BoxCollider* Player::GetBoxCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief 位置の設定
 *
 * @param  position：設定する位置
 * @return なし
 */
void Player::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	GameObject::SetPosition(position);
	m_collider->SetPosition(position);
}

//------------------------------------------------------------------
/**
 * @brief 速度の取得
 *
 * @param  なし
 * @return Vector3：速度
 */
const DirectX::SimpleMath::Vector3& Player::GetVelocity() const
{
	return m_velocity;
}

//------------------------------------------------------------------
/**
 * @brief 速度の設定（Vector3 ver）
 *
 * @param  velocity：設定する速度
 * @return なし
 */
void Player::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
}

//------------------------------------------------------------------
/**
 * @brief 速度の設定（float ver）
 *
 * @param  x：設定する速度X
 * @param  y：設定する速度Y
 * @param  z：設定する速度Z
 * @return なし
 */
void Player::SetVelocity(const float& x, const float& y, const float& z)
{
	SetVelocity(SimpleMath::Vector3(x, y, z));
}

//------------------------------------------------------------------
/**
 * @brief 指定方向を向く
 *
 * @param  direction：向きたい方向
 * @return なし
 */
void Player::TurnHeading(const DirectX::SimpleMath::Vector3& direction)
{
	SimpleMath::Quaternion rot;
	SimpleMath::Vector3 rotVel = direction;

	// 上下方向には向かないので0にする
	rotVel.y = 0.0f;

	rot = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, rotVel);
	SetRotation(rot);
}

//------------------------------------------------------------------
/**
 * @brief 移動方向ベクトル取得
 *
 * @param  isRight：右向きの方向ベクトルを受け取るかどうか
 * @return Vector3：前方ベクトル
 */
const DirectX::SimpleMath::Vector3& Player::GetMoveDirection(const bool& isRight) const
{
	// 右向きベクトル
	if (isRight) return m_moveRight;

	// 前方ベクトル
	return m_moveForward;
}

//------------------------------------------------------------------
/**
 * @brief スポーン位置の設定
 *
 * @param  spawnPosition：設定するスポーン位置
 * @return なし
 */
void Player::SetSpawnPosition(const DirectX::SimpleMath::Vector3& spawnPosition)
{
	m_spawnPosition = spawnPosition;
}

//------------------------------------------------------------------
/**
 * @brief ジャンプが可能か
 *
 * @param  なし
 * @return true：ジャンプ出来る
 * @return true：ジャンプ出来ない
 */
bool Player::IsJump()
{
	// 地面の上にいるか
	if (!m_onGround) return false;
	// すでにジャンプしているか
	if (m_isJump) return false;
	// 2Dの見下ろし視点か
	if (m_playScene->Is2D() && m_playScene->IsTopDown()) return false;
	// ジャンプ可能
	return true;
}

//------------------------------------------------------------------
/**
 * @brief ジャンプフラグ設定
 *
 * @param  isJump：設定するジャンプフラグ
 * @return なし
 */
void Player::SetJumpFlag(bool isJump)
{
	m_isJump = isJump;
}

//------------------------------------------------------------------
/**
 * @brief 地面の上にいるか
 *
 * @param なし
 * @return true：地面の上にいる
 * @return true：空中
 */
bool Player::OnGround() const
{
	return m_onGround;
}

//------------------------------------------------------------------
/**
 * @brief ワープに失敗したか
 *
 * @param  なし
 * @return true：失敗
 * @return true：成功
 */
bool Player::IsFailWarp() const
{
	return m_isFailWarp;
}

//------------------------------------------------------------------
/**
 * @brief 移動フラグ設定
 *
 * @param  moveInput：設定する移動入力フラグ
 * @return なし
 */
void Player::SetMoveInputFlag(const int& moveInput)
{
	m_moveInput |= moveInput;
}

//------------------------------------------------------------------
/**
 * @brief カメラの向き取得
 *
 * @param  なし
 * @return Vector3：カメラの向き
 */
const DirectX::SimpleMath::Vector3& Player::GetCameraDirection() const
{
	return m_camDir;
}