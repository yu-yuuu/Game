/**
 *
 * @file Player.h
 *
 * @brief プレイヤーを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/13
 *
 */
#pragma once

#include "Model.h"

#include "Game/MyLibrary/GameObject/GameObject.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/Scene/PlayScene.h"

class IPlayerStrategy;
class Collider;
class BoxCollider;
class ModelComposite;

class Player : public GameObject
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:
	
	// プレイヤーモデルのパーツ
	enum ModelParts 
	{
		HEAD,  // 頭
		ROOT,  // ルート
		BODY,  // 体
		ARM_L, // 左腕
		ARM_R, // 右腕
		LEG_L, // 左足
		LEG_R, // 右足

		COUNT, // パーツの数
	};

//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 移動速度
	const float MOVE_SPEED = 0.1f;
	// ジャンプ力
	const float JUMP_POWER = 0.1f;
	// 重力
	const float GRAVITY = 0.004f;
	// アニメーション進行速度
	const float ANIME_TIMER = 0.2f;
	// 歩行アニメーション
	const float WALK_ANIME_ATTENUATION    = 0.7f;  // 終了時の減衰割合
	const float WALK_ANIME_ADJUSTMENT_ARM = 0.5f;  // アニメーションの大きさ調整値（ 腕 ）
	const float WALK_ANIME_ADJUSTMENT_LEG = 0.25f; // アニメーションの大きさ調整値（ 脚 ）
	// 喜びアニメーション
	const float HAPPY_ANIME_ADJUSTMENT_SPEED = 0.5f; // アニメーションの速度調整値
	const float HAPPY_ANIME_ADJUSTMENT_ARM   = 3.5f; // アニメーションの大きさ調整値（ 腕 ）
	const float HAPPY_ANIME_ADJUSTMENT_JUMP  = 0.5f; // アニメーションの大きさ調整値（ジャンプ）
	// リスポーンさせる高さ
	const float RESPAWN_HEIGHT = -5.0f;
	// 2D見下ろし時にリスポーンさせる速度
	const float RESPAWN_VELOCITY = -0.5f;
	// プレイヤーのコライダーサイズ
	const DirectX::SimpleMath::Vector3 PLAYER_COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.275f, 0.725f, 0.25f);
	// モデルのローカル座標
	const DirectX::SimpleMath::Vector3 BODY_LOCAL_POSITION  = DirectX::SimpleMath::Vector3( 0.0f,     0.0f,  0.0f);
	const DirectX::SimpleMath::Vector3 HEAD_LOCAL_POSITION  = DirectX::SimpleMath::Vector3( 0.0f,     0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 ARM_L_LOCAL_POSITION = DirectX::SimpleMath::Vector3(-0.2125f,  0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 ARM_R_LOCAL_POSITION = DirectX::SimpleMath::Vector3( 0.2125f,  0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 LEG_L_LOCAL_POSITION = DirectX::SimpleMath::Vector3(-0.0875f, -0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 LEG_R_LOCAL_POSITION = DirectX::SimpleMath::Vector3( 0.0875f, -0.25f, 0.0f);

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイシーン
	PlayScene* m_playScene;
	// プレイヤー機能
	std::unique_ptr<IPlayerStrategy> m_playerStrategy;
	// プレイヤーモデル
	std::unique_ptr<ModelComposite> m_modelComposite[ModelParts::COUNT];
	// 当たり判定
	std::unique_ptr<BoxCollider> m_collider;

	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 前方移動方向ベクトル
	DirectX::SimpleMath::Vector3 m_moveForward;
	// 右向き移動方向ベクトル
	DirectX::SimpleMath::Vector3 m_moveRight;
	// ワープポイント
	DirectX::SimpleMath::Vector3 m_warpPosition;
	// リスポーン地点
	DirectX::SimpleMath::Vector3 m_spawnPosition;

	// 当たった方向
	int m_hitDirection;
	// オブジェクトに当たったか
	bool m_isHit;
	// ジャンプしたか
	bool m_isJump;
	// 地面についているか
	bool m_onGround;
	// 移動入力フラグ
	int m_moveInput;
	// ワープ失敗
	bool m_isFailWarp;

	// 2D横視点時に重なったゴースト系のブロック
	GameObject* m_overlapGhost;
	// カメラの向き
	DirectX::SimpleMath::Vector3 m_camDir;
	// モデルアニメーション用タイマー
	float m_animeTimer;
	// アニメーション用サインカーブ
	float m_animeSin;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ(プレイシーン)
	Player(PlayScene* playScene, DirectX::SimpleMath::Vector3 spawnPosition);
	// コンストラクタ(リザルトシーン)
	Player(DirectX::SimpleMath::Vector3 spawnPosition);
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;
	// 更新
	void Update() override;
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) override;
	// シルエット描画
	void RenderSilhouette(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr);
	// 後処理
	void Finalize() override;

	// モデル設定
	void ModelSetting();
	
	// プレイシーンの初期化処理
	void PlaySceneInitialize();
	// リザルトシーンの初期化処理
	void ResultSceneInitialize();
	// プレイシーンの更新処理
	void PlaySceneUpdate();
	// リザルトシーンの更新処理
	void ResultSceneUpdate();
	
	// 速度調整
	void AdjustmentVelocity();
	// 移動処理
	void Move();
	// ジャンプ処理
	void Jump();
	// 重力処理
	void Gravity();
	// ワープ処理
	void Warp(bool isSwitchFail);
	// 奈落への落下確認
	bool FallAbyssCheck();
	// 復活処理
	void Respawn();
	// 停止処理
	void Stop();
	// 指定方向を向く
	void TurnHeading(const DirectX::SimpleMath::Vector3& direction);
	
	// 衝突時処理
	void OnCollision(GameObject* gameObject) override;
	// 衝突応答
	void CollisionResponse(const int& hitDir, BoxCollider* playerBox, BoxCollider* objBox);
	// 当たり判定後の更新処理
	void CollisionAfterUpdate();
	// プレイヤーにゴースト系ブロックが重なっているかを確認する
	bool CheckOverLapGhostBlock(BoxCollider* blockBox);

	// 次元切り替え
	void ChangeDimension(KT::GameParam::Dimension dimension,
		bool isSwitchFail = false);
	// 移動方向ベクトル作成
	void CreateMoveDirection(
		const DirectX::SimpleMath::Vector3& dir,
		const DirectX::SimpleMath::Vector3& up);

	// 歩行アニメーション
	void WalkAnimation();
	// 喜びアニメーション
	void HappyAnimation();

	// シーンポインタ取得
	PlayScene* GetScene() const;
	// 当たり判定取得
	Collider* GetCollider() const;
	BoxCollider* GetBoxCollider() const;

	// 位置の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// 速度の取得
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	// 速度の設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	void SetVelocity(const float& x, const float& y, const float& z);
	// 移動方向ベクトル取得
	const DirectX::SimpleMath::Vector3& GetMoveDirection(const bool& isRight = false) const;
	// スポーン位置設定
	void SetSpawnPosition(const DirectX::SimpleMath::Vector3& spawnPosition);

	// ジャンプが可能か
	bool IsJump();
	// ジャンプフラグ設定
	void SetJumpFlag(bool isJump);
	// 地面の上にいるか
	bool OnGround() const;
	// ワープが失敗したか
	bool IsFailWarp() const;
	// 移動入力フラグ設定
	void SetMoveInputFlag(const int& moveInput);

	// カメラ向き取得
	const DirectX::SimpleMath::Vector3& GetCameraDirection() const;
};