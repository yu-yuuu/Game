/**
 *
 * @file Player.h
 *
 * @brief �v���C���[��\���N���X�̃w�b�_�[�t�@�C��
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
// �񋓑�
//----------------------------------------------
public:
	
	// �v���C���[���f���̃p�[�c
	enum ModelParts 
	{
		HEAD,  // ��
		ROOT,  // ���[�g
		BODY,  // ��
		ARM_L, // ���r
		ARM_R, // �E�r
		LEG_L, // ����
		LEG_R, // �E��

		COUNT, // �p�[�c�̐�
	};

//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �ړ����x
	const float MOVE_SPEED = 0.1f;
	// �W�����v��
	const float JUMP_POWER = 0.1f;
	// �d��
	const float GRAVITY = 0.004f;
	// �A�j���[�V�����i�s���x
	const float ANIME_TIMER = 0.2f;
	// ���s�A�j���[�V����
	const float WALK_ANIME_ATTENUATION    = 0.7f;  // �I�����̌�������
	const float WALK_ANIME_ADJUSTMENT_ARM = 0.5f;  // �A�j���[�V�����̑傫�������l�i �r �j
	const float WALK_ANIME_ADJUSTMENT_LEG = 0.25f; // �A�j���[�V�����̑傫�������l�i �r �j
	// ��уA�j���[�V����
	const float HAPPY_ANIME_ADJUSTMENT_SPEED = 0.5f; // �A�j���[�V�����̑��x�����l
	const float HAPPY_ANIME_ADJUSTMENT_ARM   = 3.5f; // �A�j���[�V�����̑傫�������l�i �r �j
	const float HAPPY_ANIME_ADJUSTMENT_JUMP  = 0.5f; // �A�j���[�V�����̑傫�������l�i�W�����v�j
	// ���X�|�[�������鍂��
	const float RESPAWN_HEIGHT = -5.0f;
	// 2D�����낵���Ƀ��X�|�[�������鑬�x
	const float RESPAWN_VELOCITY = -0.5f;
	// �v���C���[�̃R���C�_�[�T�C�Y
	const DirectX::SimpleMath::Vector3 PLAYER_COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.275f, 0.725f, 0.25f);
	// ���f���̃��[�J�����W
	const DirectX::SimpleMath::Vector3 BODY_LOCAL_POSITION  = DirectX::SimpleMath::Vector3( 0.0f,     0.0f,  0.0f);
	const DirectX::SimpleMath::Vector3 HEAD_LOCAL_POSITION  = DirectX::SimpleMath::Vector3( 0.0f,     0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 ARM_L_LOCAL_POSITION = DirectX::SimpleMath::Vector3(-0.2125f,  0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 ARM_R_LOCAL_POSITION = DirectX::SimpleMath::Vector3( 0.2125f,  0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 LEG_L_LOCAL_POSITION = DirectX::SimpleMath::Vector3(-0.0875f, -0.25f, 0.0f);
	const DirectX::SimpleMath::Vector3 LEG_R_LOCAL_POSITION = DirectX::SimpleMath::Vector3( 0.0875f, -0.25f, 0.0f);

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C�V�[��
	PlayScene* m_playScene;
	// �v���C���[�@�\
	std::unique_ptr<IPlayerStrategy> m_playerStrategy;
	// �v���C���[���f��
	std::unique_ptr<ModelComposite> m_modelComposite[ModelParts::COUNT];
	// �����蔻��
	std::unique_ptr<BoxCollider> m_collider;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �O���ړ������x�N�g��
	DirectX::SimpleMath::Vector3 m_moveForward;
	// �E�����ړ������x�N�g��
	DirectX::SimpleMath::Vector3 m_moveRight;
	// ���[�v�|�C���g
	DirectX::SimpleMath::Vector3 m_warpPosition;
	// ���X�|�[���n�_
	DirectX::SimpleMath::Vector3 m_spawnPosition;

	// ������������
	int m_hitDirection;
	// �I�u�W�F�N�g�ɓ���������
	bool m_isHit;
	// �W�����v������
	bool m_isJump;
	// �n�ʂɂ��Ă��邩
	bool m_onGround;
	// �ړ����̓t���O
	int m_moveInput;
	// ���[�v���s
	bool m_isFailWarp;

	// 2D�����_���ɏd�Ȃ����S�[�X�g�n�̃u���b�N
	GameObject* m_overlapGhost;
	// �J�����̌���
	DirectX::SimpleMath::Vector3 m_camDir;
	// ���f���A�j���[�V�����p�^�C�}�[
	float m_animeTimer;
	// �A�j���[�V�����p�T�C���J�[�u
	float m_animeSin;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^(�v���C�V�[��)
	Player(PlayScene* playScene, DirectX::SimpleMath::Vector3 spawnPosition);
	// �R���X�g���N�^(���U���g�V�[��)
	Player(DirectX::SimpleMath::Vector3 spawnPosition);
	// �f�X�g���N�^
	~Player();

	// ������
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;
	// �X�V
	void Update() override;
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) override;
	// �V���G�b�g�`��
	void RenderSilhouette(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr);
	// �㏈��
	void Finalize() override;

	// ���f���ݒ�
	void ModelSetting();
	
	// �v���C�V�[���̏���������
	void PlaySceneInitialize();
	// ���U���g�V�[���̏���������
	void ResultSceneInitialize();
	// �v���C�V�[���̍X�V����
	void PlaySceneUpdate();
	// ���U���g�V�[���̍X�V����
	void ResultSceneUpdate();
	
	// ���x����
	void AdjustmentVelocity();
	// �ړ�����
	void Move();
	// �W�����v����
	void Jump();
	// �d�͏���
	void Gravity();
	// ���[�v����
	void Warp(bool isSwitchFail);
	// �ޗ��ւ̗����m�F
	bool FallAbyssCheck();
	// ��������
	void Respawn();
	// ��~����
	void Stop();
	// �w�����������
	void TurnHeading(const DirectX::SimpleMath::Vector3& direction);
	
	// �Փˎ�����
	void OnCollision(GameObject* gameObject) override;
	// �Փˉ���
	void CollisionResponse(const int& hitDir, BoxCollider* playerBox, BoxCollider* objBox);
	// �����蔻���̍X�V����
	void CollisionAfterUpdate();
	// �v���C���[�ɃS�[�X�g�n�u���b�N���d�Ȃ��Ă��邩���m�F����
	bool CheckOverLapGhostBlock(BoxCollider* blockBox);

	// �����؂�ւ�
	void ChangeDimension(KT::GameParam::Dimension dimension,
		bool isSwitchFail = false);
	// �ړ������x�N�g���쐬
	void CreateMoveDirection(
		const DirectX::SimpleMath::Vector3& dir,
		const DirectX::SimpleMath::Vector3& up);

	// ���s�A�j���[�V����
	void WalkAnimation();
	// ��уA�j���[�V����
	void HappyAnimation();

	// �V�[���|�C���^�擾
	PlayScene* GetScene() const;
	// �����蔻��擾
	Collider* GetCollider() const;
	BoxCollider* GetBoxCollider() const;

	// �ʒu�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// ���x�̎擾
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	// ���x�̐ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	void SetVelocity(const float& x, const float& y, const float& z);
	// �ړ������x�N�g���擾
	const DirectX::SimpleMath::Vector3& GetMoveDirection(const bool& isRight = false) const;
	// �X�|�[���ʒu�ݒ�
	void SetSpawnPosition(const DirectX::SimpleMath::Vector3& spawnPosition);

	// �W�����v���\��
	bool IsJump();
	// �W�����v�t���O�ݒ�
	void SetJumpFlag(bool isJump);
	// �n�ʂ̏�ɂ��邩
	bool OnGround() const;
	// ���[�v�����s������
	bool IsFailWarp() const;
	// �ړ����̓t���O�ݒ�
	void SetMoveInputFlag(const int& moveInput);

	// �J���������擾
	const DirectX::SimpleMath::Vector3& GetCameraDirection() const;
};