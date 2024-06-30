/**
 *
 * @file SkyDome.cpp
 *
 * @brief �X�J�C�h�[����\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/7
 *
 */
#include "pch.h"
#include "SkyDome.h"
#include "Effects.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param position�F�X�J�C�h�[���̒��S�ʒu
 */
SkyDome::SkyDome(DirectX::SimpleMath::Vector3 position)
	: m_position(position)
	, m_rotation()
	, m_rotationSpeed(0.0f)
{
	// ���\�[�X�}�l�[�W���[�擾
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	
	// ���f�����󂯎��
	m_model = resourceManager->GetModel(KT::Model::SKY_DOME);

	// �X�J�C�h�[���̃��C�g�ݒ�
	m_model->UpdateEffects([](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);

			if (lights)
			{
				// ���C�g�̉e�����Ȃ���
				lights->SetAmbientLightColor(SimpleMath::Vector3::Zero);
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// ���Ȕ���������
				basicEffect->SetEmissiveColor(SimpleMath::Vector3::One);
			}
		}
	);
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
SkyDome::~SkyDome()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SkyDome::Update()
{
	// ��]���x���ݒ肳��Ă��邩
	if (std::fabsf(m_rotationSpeed) <= std::numeric_limits<float>::epsilon()) return;
	// ��]���|����
	m_rotation *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_rotationSpeed);
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// �e�탊�\�[�X�擾
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// �X�J�C�h�[���̕`��
	SimpleMath::Matrix skyWorld = SimpleMath::Matrix::CreateFromQuaternion(m_rotation) *
		SimpleMath::Matrix::CreateTranslation(m_position);
	m_model->Draw(context, *commonStates, skyWorld, view, projection);
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̐ݒ�
 *
 * @param position�F�ݒ肷��ʒu
 * @return �Ȃ�
 */
void SkyDome::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

//------------------------------------------------------------------
/**
 * @brief ��]���x�̐ݒ�
 *
 * @param  rotationSpeed�F�ݒ肷���]���x
 * @return �Ȃ�
 */
void SkyDome::SetRotationSpeed(const float& rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}