/**
 *
 * @file CameraStateTracking3D.h
 *
 * @brief 3D�ǐՃJ�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateTracking3D : public ICameraState
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �Q�[���J����
	GameCamera* m_gameCamera;
	// �����낵�֑ؑO�̉�]
	DirectX::SimpleMath::Quaternion m_beforeRotation;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateTracking3D(GameCamera* gameCamera);
	// �f�X�g���N�^
	~CameraStateTracking3D();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;
	
	// �����؂�ւ��ݒ�
	void ChangeDimensionSetting();
	// �J��������]�����ėǂ����m�F
	bool CheckRotation();
	// �J������]�ݒ�
	void RotationSetting();
	// ���n���J�����֐؂�ւ��ėǂ����m�F
	bool CheckChangeOverLooking();
	// ���n���J�����ؑ֐ݒ�
	void ChangeOverLookingSetting();
	// �J�����ʒu�擾
	const DirectX::SimpleMath::Vector3& GetEyePosition() const;
	// �����낵�֑ؑO�̉�]�擾
	const DirectX::SimpleMath::Quaternion& GetBeforeRotation() const;
};