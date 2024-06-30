/**
 *
 * @file Player.cpp
 *
 * @brief �v���C���[��\���N���X�̃\�[�X�t�@�C��
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
 * @brief �R���X�g���N�^�i�v���C�V�[���j
 *
 * @param playScene�F�v���C�V�[���̃|�C���^
 * @param spawnPosition�F�����ʒu
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
 * @brief �R���X�g���N�^�i���U���g�V�[���j
 *
 * @param �Ȃ�
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
 * @brief �f�X�g���N�^
 */
Player::~Player()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{	
	// �g�p���Ă���V�[���ŏ�����؂�ւ���
	if (m_playScene) PlaySceneInitialize();
	else             ResultSceneInitialize();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Update()
{
	// �g�p���Ă���V�[���ōX�V������؂�ւ���
	if (m_playScene) PlaySceneUpdate();
	else             ResultSceneUpdate();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view        �F�r���[�s��
 * @param  projection  �F�ˉe�s��
 * @return �Ȃ�
 */
void Player::Render(
	DirectX::SimpleMath::Matrix view, 
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom)
{
	// ���f���`��
	m_modelComposite[ROOT]->Update(GetWorldMatrix());
	m_modelComposite[ROOT]->Render(view, projection, custom);
}


//------------------------------------------------------------------
/**
 * @brief �V���G�b�g�`��
 *
 * @param  view        �F�r���[�s��
 * @param  projection  �F�ˉe�s��
 * @return �Ȃ�
 */
void Player::RenderSilhouette(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	// ���f���`��
	m_modelComposite[ROOT]->Update(GetWorldMatrix());
	m_modelComposite[ROOT]->Render(view, projection, custom);
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief ���f���ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::ModelSetting()
{
	// ���O��ԕʖ��錾
	using namespace KT::Model;

	// ���\�[�X�}�l�[�W���[�擾
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();

	// �v���C���[���f���ݒ�
	m_modelComposite[ROOT]  = std::make_unique<ModelComposite>(nullptr, SimpleMath::Vector3::Zero);
	m_modelComposite[BODY]  = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_BODY), BODY_LOCAL_POSITION);
	m_modelComposite[HEAD]  = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_HEAD), HEAD_LOCAL_POSITION);
	m_modelComposite[ARM_L] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_ARM_L), ARM_L_LOCAL_POSITION);
	m_modelComposite[ARM_R] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_ARM_R), ARM_R_LOCAL_POSITION);
	m_modelComposite[LEG_L] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_LEG_L), LEG_L_LOCAL_POSITION);
	m_modelComposite[LEG_R] = std::make_unique<ModelComposite>(resourceManager->GetModel(PLAYER_LEG_R), LEG_R_LOCAL_POSITION);
	// �v���C���[�̐e�q�ݒ�
	m_modelComposite[ROOT]->SetChild(m_modelComposite[BODY].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[HEAD].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[ARM_L].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[ARM_R].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[LEG_L].get());
	m_modelComposite[BODY]->SetChild(m_modelComposite[LEG_R].get());
	// �G�t�F�N�g�ݒ�
	m_modelComposite[ROOT]->UpdateEffects(
		[](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ���C�g��K��������
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
 * @brief �v���C�V�[���̏���������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::PlaySceneInitialize()
{
	// �����蔻��}�`�쐬
	m_collider = std::make_unique<BoxCollider>(GetPosition(), PLAYER_COLLIDER_SIZE, true);
	// �Q�[���I�u�W�F�N�g�ݒ�
	m_collider->SetGameObject(this);
	// �����ʒu�ݒ�
	m_spawnPosition.y += m_collider->GetExtents().y;
	SetPosition(m_spawnPosition);
	// �����@�\�ݒ�
	m_playerStrategy = std::make_unique<PlayerStrategy3D>(this);
	// ���f���ݒ�
	ModelSetting();
}

//------------------------------------------------------------------
/**
 * @brief ���U���g�V�[���̏���������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::ResultSceneInitialize()
{
	// �����蔻��}�`�쐬
	m_collider = std::make_unique<BoxCollider>(GetPosition(), PLAYER_COLLIDER_SIZE, true);
	// �Q�[���I�u�W�F�N�g�ݒ�
	m_collider->SetGameObject(this);
	// �����ʒu�ݒ�
	m_spawnPosition.y += m_collider->GetExtents().y;
	SetPosition(m_spawnPosition);
	// ���f���ݒ�
	ModelSetting();
}

//------------------------------------------------------------------
/**
 * @brief �v���C�V�[���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::PlaySceneUpdate()
{
	// �ϐ����Z�b�g
	m_isHit        = false;   // �ڐG�t���O
	m_isFailWarp   = false;   // ���[�v���s�t���O
	m_overlapGhost = nullptr; // �d�Ȃ����S�[�X�g���u���b�N

	// �@�\�N���X�̍X�V
	m_playerStrategy->Update();
	// �ړ�����
	Move();
	// �d�͏���
	Gravity();
	// ���x����
	AdjustmentVelocity();
	// �����蔻��ړ�
	m_collider->SetPosition(GetPosition() + m_velocity);
	// �����A�j���[�V����
	WalkAnimation();
}

//------------------------------------------------------------------
/**
 * @brief ���U���g�V�[���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::ResultSceneUpdate()
{
	// ��ԃA�j���[�V����
	HappyAnimation();
}

//------------------------------------------------------------------
/**
 * @brief ���x����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::AdjustmentVelocity()
{
	// ���K�����Ď΂߂ŉ������Ȃ��悤�ɂ���
	SimpleMath::Vector3 velNorm;
	m_velocity.Normalize(velNorm);
	velNorm *= MOVE_SPEED;
	// �c�̈ړ��ʂ͂��̂܂�
	SetVelocity({ velNorm.x, m_velocity.y, velNorm.z });
}

//------------------------------------------------------------------
/**
 * @brief �ړ�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Move()
{
	// ���x�󂯎��p
	SimpleMath::Vector3 velocity;

	// ��
	if (m_moveInput & KT::GameParam::InputDirection::FORWARD) velocity += m_moveForward * Player::MOVE_SPEED;
	// ��O
	if (m_moveInput & KT::GameParam::InputDirection::BACK)    velocity -= m_moveForward * Player::MOVE_SPEED;
	// �E
	if (m_moveInput & KT::GameParam::InputDirection::RIGHT)   velocity += m_moveRight * Player::MOVE_SPEED;
	// ��
	if (m_moveInput & KT::GameParam::InputDirection::LEFT)    velocity -= m_moveRight * Player::MOVE_SPEED;

	// ���͂�����Ƃ��͏������s��
	if (m_moveInput != 0)
	{
		// �t���O������
		m_moveInput = 0;
		// �v���C���[���ړ������Ɍ�������
		TurnHeading(velocity);
	}

	// ���x�ݒ�
	SimpleMath::Vector3 vel = GetVelocity();
	SetVelocity(velocity.x, vel.y, velocity.z);
}

//------------------------------------------------------------------
/**
 * @brief �W�����v����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Jump()
{
	// �W�����v���\��
	if (!IsJump()) return;

	// �W�����v�͂𑬓x�ɉ�����
 	m_velocity.y += JUMP_POWER;
	// �t���O�𗧂Ă�
	m_isJump = true;
	// SE�𗬂�
	GameResource::GetInstance()->GetResourceManager()->
		PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_JUMP);
}

//------------------------------------------------------------------
/**
 * @brief �d�͏���
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Gravity()
{
	m_velocity.y -= GRAVITY;
}

//------------------------------------------------------------------
/**
 * @brief ���[�v����
 *
 * @param  isSwitchFail�F�ؑւɎ��s���Ă��邩
 * @return �Ȃ�
 */
void Player::Warp(bool isSwitchFail)
{
	// ���݂̈ʒu�擾
	DirectX::SimpleMath::Vector3 position = GetPosition();
	// ���[�v�ړ����������0�ɂ���
	position *= KT::MyUtility::InverseFlag(m_camDir);
	// ���[�v�ړ���������݂̂�
	m_warpPosition *= KT::MyUtility::AbsVector(m_camDir);

	// ���[�v�|�C���g�Əd�Ȃ��Ă����u���b�N��
	// ���_�����̈ʒu�̂�����v�Z	
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
	// �ʒu��ݒ�
	SetPosition(position + m_warpPosition);
	// ���[�v�|�C���g���Z�b�g
	m_warpPosition = GetPosition();
}

//------------------------------------------------------------------
/**
 * @brief �ޗ��ւ̗����m�F
 *
 * @param  �Ȃ�
 * @return bool�F�ޗ��ɗ���������
 */
bool Player::FallAbyssCheck()
{
	// 2D�����낵�̎�
	if (m_playScene->Is2D() && m_playScene->IsTopDown())
	{
		// �������Ă��Ȃ������痎������
		return !m_isHit;
	}
	// 3D, 2D�����_�̎�
	else
	{
		// ��荂����艺�Ȃ痎������
		return GetPosition().y < RESPAWN_HEIGHT;
	}
}

//------------------------------------------------------------------
/**
 * @brief ��������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Respawn()
{
	// 2D�Ȃ�3D�֐؂�ւ���
	if(m_playScene->Is2D())
	{
		m_onGround = true;
		m_playScene->ChangeDimension(false);
	}

	// �����ʒu�ݒ�
	SetPosition(m_spawnPosition);
	// �v���C���[���~������
	Stop();
}

//------------------------------------------------------------------
/**
 * @brief ��~����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::Stop()
{
	m_velocity = SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief �Փˎ�����
 *
 * @param  gameObject�F���������I�u�W�F�N�g
 * @return �Ȃ�
 */
void Player::OnCollision(GameObject* gameObject)
{
	// �u���b�N���擾
	Block* block = dynamic_cast<Block*>(gameObject);
	// ��ނ��擾
	KT::Block::Type type = block->GetType();
	// �u���b�N�̔���{�b�N�X�擾
	BoxCollider* blockBox = dynamic_cast<BoxCollider*>(block->GetCollider());
	// �v���C���[�̃{�b�N�X�R���C�_�[�擾
	BoxCollider* playerBox = dynamic_cast<BoxCollider*>(m_collider.get());
	// �����Ԃ��������s����
	bool isExecute = true;

	// 2D�ŏ��u���b�N
	if (m_playScene->Is2D() && type == KT::Block::Type::GHOST_FLOOR)
	{
		// �����낵���_
		if (m_playScene->IsTopDown())
		{
			// �d�͂�ł�����
			SimpleMath::Vector3 pos = GetPosition();
			SimpleMath::Vector3 colPos = playerBox->GetPosition();
			colPos.y = pos.y;
			playerBox->SetPosition(colPos);
			m_velocity.y = 0.0f;
			// ���[�v�|�C���g�ݒ�
			m_warpPosition = gameObject->GetPosition();
			m_warpPosition.y += (playerBox->GetExtents().y + blockBox->GetExtents().y);
			// �ڐG�t���O�𗧂Ă�
			m_isHit = true;
			// �����Ԃ��������s��Ȃ�
			isExecute = false;
			// �ŏI�I�Ȉʒu��ݒ�
			SetPosition(playerBox->GetPosition());
		}
		// �����_
		else
		{
			// �v���C���[�̉��̈ʒu���擾
			SimpleMath::Vector3 min, max;
			playerBox->GetCorners(min, max);
			float playerBottom = min.y;
			// �u���b�N�̏�Ɉʒu���擾
			blockBox->GetCorners(min, max);
			float blockTop = max.y;

			// �v���C���[���u���b�N�̏㕔�����͈͓��̍����ɂ��� &&
			// �v���C���[�����~���@�łȂ��Ƃ�
			if (!(std::fabsf(playerBottom - blockTop) <= KT::GameParam::GHOST_FLOOR_CHECK_HEIGHT && m_velocity.y < 0.0f))
			{
				// �v���C���[�ɏd�Ȃ��Ă��邩�m�F
				if (CheckOverLapGhostBlock(blockBox))
				{
					m_overlapGhost = gameObject;
				}
				// �����Ԃ��������s��Ȃ�
				isExecute = false;
			}
		}
	}
	// 2D�ŃS�[�X�g�u���b�N
	else if (m_playScene->Is2D() && type == KT::Block::Type::GHOST)
	{
		// �v���C���[�ɏd�Ȃ��Ă��邩�m�F
		if (CheckOverLapGhostBlock(blockBox))
		{
			m_overlapGhost = gameObject;
		}
		// �����Ԃ��������s��Ȃ�
		isExecute = false;
	}
	// �S�[���u���b�N�̎�
	else if (type == KT::Block::Type::GOAL)
	{
		// �v���C���[��~
		Stop();
		// �v���C�V�[���̃S�[�����������s
		m_playScene->ArrivalGoal();
	}

	// �����Ԃ�����
	if (isExecute)
	{
		// �ڐG�t���O�𗧂Ă�
		m_isHit = true;
		// ������������������o��
		int hitDir = Collision::GetHitDirection(m_playScene->Is2D(), m_camDir, *playerBox, *blockBox);
		// �����Ԃ�����
		CollisionResponse(hitDir, playerBox, blockBox);
		// �ŏI�I�Ȉʒu��ݒ�
		SetPosition(playerBox->GetPosition());
		// �������������ɂ�鏈��
		if (hitDir & Collision::Bottom)
		{
			// �n�ʂ̏�ɂ���
			m_onGround = true;
			// �W�����v�t���O��܂�
			m_isJump = false;
			// ���[�v�|�C���g�̐ݒ�
			m_warpPosition = blockBox->GetPosition();
			m_warpPosition.y += (playerBox->GetExtents() + blockBox->GetExtents()).y;
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief �Փˉ���
 *
 * @param  hitDir   �F������������
 * @param  playerBox�F�v���C���[�̓����蔻��{�b�N�X
 * @param  objBox   �F�I�u�W�F�N�g�̓����蔻��{�b�N�X
 * @return �Ȃ�
 */
void Player::CollisionResponse(const int& hitDir, BoxCollider* playerBox, BoxCollider* objBox)
{
	// �����Ԃ��ʂ��v�Z����
	SimpleMath::Vector3 push = playerBox->GetExtents() + objBox->GetExtents();
	// �v���C���[�̓����蔻��ʒu
	SimpleMath::Vector3 playerPos = playerBox->GetPosition();
	// ���������I�u�W�F�N�g�̓����蔻��ʒu
	SimpleMath::Vector3 objPos = objBox->GetPosition();
	
	// �����Ԃ�����
	switch (hitDir)
	{
	// ��ɓ�������
	case Collision::Top:    playerPos.y = objPos.y - push.y; m_velocity.y = 0.0f; break;
	// ���ɓ�������
	case Collision::Bottom: playerPos.y = objPos.y + push.y; m_velocity.y = 0.0f; break;
	// �E�ɓ�������
	case Collision::Right:  playerPos.x = objPos.x - push.x; m_velocity.x = 0.0f; break;
	// ���ɓ�������
	case Collision::Left:   playerPos.x = objPos.x + push.x; m_velocity.x = 0.0f; break;
	// ���ʁi���j�ɓ�������
	case Collision::Front:  playerPos.z = objPos.z + push.z; m_velocity.z = 0.0f; break;
	// ���ɓ�������
	case Collision::Back:   playerPos.z = objPos.z - push.z; m_velocity.z = 0.0f; break;
	default: break;
	}
	// �����o�����ʒu��ݒ�
	playerBox->SetPosition(playerPos);
}

//------------------------------------------------------------------
/**
 * @brief �����蔻���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::CollisionAfterUpdate()
{
	// �I�u�W�F�N�g�ɐڐG���Ă��Ȃ�
	if (!m_isHit)
	{
		// �n�ʂɐG��Ă��Ȃ�
		m_onGround = false;
		// ���x��������
		SetPosition(GetPosition() + m_velocity);
	}
	// �ޗ��֗������Ă����畜��������
	if (FallAbyssCheck()) Respawn();
}

//------------------------------------------------------------------
/**
 * @brief �v���C���[�ɃS�[�X�g�n�u���b�N���d�Ȃ��Ă��邩���m�F����
 *
 * @param  blockBox�F�v���C���[�ɓ��������u���b�N�̃R���C�_�[
 * @return true �F�d�Ȃ��Ă���
 * @return false�F�d�Ȃ��Ă��Ȃ�
 */
bool Player::CheckOverLapGhostBlock(BoxCollider* blockBox)
{
	// �u���b�N�̔��a���擾
	SimpleMath::Vector3 range = blockBox->GetExtents();
	// �v���C���[�ƃu���b�N�̋������v�Z����
	SimpleMath::Vector3 dist = GetPosition() - blockBox->GetPosition();
	// �g�p��������݂̂ɂ���
	range *= KT::MyUtility::InverseFlag(m_camDir);
	dist *= KT::MyUtility::InverseFlag(m_camDir);
	// �v���C���[���u���b�N�̔��a���ɋ��邩����
	return KT::MyUtility::AbsVector(dist).LengthSquared() < (range).LengthSquared();
}

//------------------------------------------------------------------
/**
 * @brief �����؂�ւ�
 *
 * @param  dimension      �F���݂̎���
 * @param  isSwitchFail   �F�؂�ւ����s����
 * @return �Ȃ�
 */
void Player::ChangeDimension(
	KT::GameParam::Dimension dimension,
	bool isSwitchFail)
{
	// 2D�֐؂�ւ�
	if (dimension == KT::GameParam::Dimension::_3D)
	{
		m_playerStrategy.reset(new PlayerStrategy2D(this));
	}
	// 3D�֐؂�ւ�
	else
	{
		m_playerStrategy.reset(new PlayerStrategy3D(this));
		// ���[�v����
		Warp(isSwitchFail);
	}
}

//------------------------------------------------------------------
/**
 * @brief �ړ������x�N�g���쐬
 *
 * @param  dir �F�J�����̕����x�N�g��
 * @param  up �F�J�����̓��̌���
 * @return �Ȃ�
 */
void Player::CreateMoveDirection(
	const DirectX::SimpleMath::Vector3& dir,
	const DirectX::SimpleMath::Vector3& up)
{
	// �J�����̌������󂯎��
	m_camDir = dir;
	// �J�����ւ̃x�N�g���ƃJ�����̓��̌�������E�����x�N�g�����쐬����
	SimpleMath::Vector3 cross = dir.Cross(up);
	cross.Normalize(m_moveRight);
	// �E�����x�N�g����90�x���ɉ񂵑O���x�N�g�����쐬����
	m_moveForward = SimpleMath::Vector3(m_moveRight.z, 0.0f, -m_moveRight.x);
	// �덷������
	m_moveForward = KT::MyUtility::ModVector(m_moveForward);
	m_moveRight   = KT::MyUtility::ModVector(m_moveRight);
}

//------------------------------------------------------------------
/**
 * @brief �����A�j���[�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::WalkAnimation()
{
	// ���̈ړ��ʎ擾
	float movement = std::fabsf(m_velocity.x) + std::fabsf(m_velocity.z);

	// �ړ����Ă��邩�m�F
	if (movement > std::numeric_limits<float>::epsilon())
	{
		// �A�j���[�V�����^�C�}�[�i�s
		m_animeTimer += ANIME_TIMER;
		// �A�j���[�V�����p�T�C���J�[�u�X�V
		m_animeSin = std::sinf(m_animeTimer);
	}
	else
	{
		// ���삵�Ă��Ȃ����͏��X��0�ɋ߂Â���
		m_animeSin *= WALK_ANIME_ATTENUATION;
		// �قڃ[���Ȃ�[����
		if (std::fabsf(m_animeSin) <= std::numeric_limits<float>::epsilon()) m_animeSin = 0.0f;
	}
	// �����A�j���[�V����
	m_modelComposite[ARM_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX( m_animeSin * WALK_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[ARM_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(-m_animeSin * WALK_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[LEG_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(-m_animeSin * WALK_ANIME_ADJUSTMENT_LEG));
	m_modelComposite[LEG_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX( m_animeSin * WALK_ANIME_ADJUSTMENT_LEG));
}

//------------------------------------------------------------------
/**
 * @brief ��уA�j���[�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Player::HappyAnimation()
{
	// �A�j���[�V�����^�C�}�[�i�s
	m_animeTimer += ANIME_TIMER;
	// �A�j���[�V�����p�T�C���J�[�u�X�V
	m_animeSin = std::sinf(m_animeTimer * HAPPY_ANIME_ADJUSTMENT_SPEED);
	m_animeSin = std::max(m_animeSin, 0.0f);
	// �r��U��
	m_modelComposite[ARM_L]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(m_animeSin * HAPPY_ANIME_ADJUSTMENT_ARM));
	m_modelComposite[ARM_R]->SetTransformMatrix(SimpleMath::Matrix::CreateRotationX(m_animeSin * HAPPY_ANIME_ADJUSTMENT_ARM));
	// �W�����v
	m_modelComposite[ROOT]->SetTransformMatrix(SimpleMath::Matrix::CreateTranslation(0.0f, m_animeSin * HAPPY_ANIME_ADJUSTMENT_JUMP, 0.0f));
}

//------------------------------------------------------------------
/**
 * @brief �V�[���|�C���^�擾
 *
 * @param  �Ȃ�
 * @return TestScene*�F�V�[���ւ̃|�C���^
 */
PlayScene* Player::GetScene() const
{
	return m_playScene;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��擾
 *
 * @param �Ȃ�
 * @return Collider*�F�����蔻��ւ̃|�C���^
 */
Collider* Player::GetCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief �����蔻�蔠�擾
 *
 * @param �Ȃ�
 * @return BoxCollider*�F�����蔻�蔠�ւ̃|�C���^
 */
BoxCollider* Player::GetBoxCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̐ݒ�
 *
 * @param  position�F�ݒ肷��ʒu
 * @return �Ȃ�
 */
void Player::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	GameObject::SetPosition(position);
	m_collider->SetPosition(position);
}

//------------------------------------------------------------------
/**
 * @brief ���x�̎擾
 *
 * @param  �Ȃ�
 * @return Vector3�F���x
 */
const DirectX::SimpleMath::Vector3& Player::GetVelocity() const
{
	return m_velocity;
}

//------------------------------------------------------------------
/**
 * @brief ���x�̐ݒ�iVector3 ver�j
 *
 * @param  velocity�F�ݒ肷�鑬�x
 * @return �Ȃ�
 */
void Player::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
}

//------------------------------------------------------------------
/**
 * @brief ���x�̐ݒ�ifloat ver�j
 *
 * @param  x�F�ݒ肷�鑬�xX
 * @param  y�F�ݒ肷�鑬�xY
 * @param  z�F�ݒ肷�鑬�xZ
 * @return �Ȃ�
 */
void Player::SetVelocity(const float& x, const float& y, const float& z)
{
	SetVelocity(SimpleMath::Vector3(x, y, z));
}

//------------------------------------------------------------------
/**
 * @brief �w�����������
 *
 * @param  direction�F������������
 * @return �Ȃ�
 */
void Player::TurnHeading(const DirectX::SimpleMath::Vector3& direction)
{
	SimpleMath::Quaternion rot;
	SimpleMath::Vector3 rotVel = direction;

	// �㉺�����ɂ͌����Ȃ��̂�0�ɂ���
	rotVel.y = 0.0f;

	rot = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, rotVel);
	SetRotation(rot);
}

//------------------------------------------------------------------
/**
 * @brief �ړ������x�N�g���擾
 *
 * @param  isRight�F�E�����̕����x�N�g�����󂯎�邩�ǂ���
 * @return Vector3�F�O���x�N�g��
 */
const DirectX::SimpleMath::Vector3& Player::GetMoveDirection(const bool& isRight) const
{
	// �E�����x�N�g��
	if (isRight) return m_moveRight;

	// �O���x�N�g��
	return m_moveForward;
}

//------------------------------------------------------------------
/**
 * @brief �X�|�[���ʒu�̐ݒ�
 *
 * @param  spawnPosition�F�ݒ肷��X�|�[���ʒu
 * @return �Ȃ�
 */
void Player::SetSpawnPosition(const DirectX::SimpleMath::Vector3& spawnPosition)
{
	m_spawnPosition = spawnPosition;
}

//------------------------------------------------------------------
/**
 * @brief �W�����v���\��
 *
 * @param  �Ȃ�
 * @return true�F�W�����v�o����
 * @return true�F�W�����v�o���Ȃ�
 */
bool Player::IsJump()
{
	// �n�ʂ̏�ɂ��邩
	if (!m_onGround) return false;
	// ���łɃW�����v���Ă��邩
	if (m_isJump) return false;
	// 2D�̌����낵���_��
	if (m_playScene->Is2D() && m_playScene->IsTopDown()) return false;
	// �W�����v�\
	return true;
}

//------------------------------------------------------------------
/**
 * @brief �W�����v�t���O�ݒ�
 *
 * @param  isJump�F�ݒ肷��W�����v�t���O
 * @return �Ȃ�
 */
void Player::SetJumpFlag(bool isJump)
{
	m_isJump = isJump;
}

//------------------------------------------------------------------
/**
 * @brief �n�ʂ̏�ɂ��邩
 *
 * @param �Ȃ�
 * @return true�F�n�ʂ̏�ɂ���
 * @return true�F��
 */
bool Player::OnGround() const
{
	return m_onGround;
}

//------------------------------------------------------------------
/**
 * @brief ���[�v�Ɏ��s������
 *
 * @param  �Ȃ�
 * @return true�F���s
 * @return true�F����
 */
bool Player::IsFailWarp() const
{
	return m_isFailWarp;
}

//------------------------------------------------------------------
/**
 * @brief �ړ��t���O�ݒ�
 *
 * @param  moveInput�F�ݒ肷��ړ����̓t���O
 * @return �Ȃ�
 */
void Player::SetMoveInputFlag(const int& moveInput)
{
	m_moveInput |= moveInput;
}

//------------------------------------------------------------------
/**
 * @brief �J�����̌����擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�J�����̌���
 */
const DirectX::SimpleMath::Vector3& Player::GetCameraDirection() const
{
	return m_camDir;
}