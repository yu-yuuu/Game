/**
 *
 * @file CameraStateTracking2D.h
 *
 * @brief 2D�ǐՃJ�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateTracking2D : public ICameraState
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �Q�[���J����
	GameCamera* m_gameCamera;
	// �I�t�Z�b�g�ʒu
	DirectX::SimpleMath::Vector3 m_offsetPosition;
	// �����낵�֑ؑO�̒����_
	DirectX::SimpleMath::Vector3 m_beforeTarget;


//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateTracking2D(GameCamera* gameCamera);
	// �f�X�g���N�^
	~CameraStateTracking2D();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �ؑ֒��t���O
	bool IsOperation() override;

	// �����؂�ւ��ݒ�
	void ChangeDimensionSetting();
	// ���n���J�����֐؂�ւ��ėǂ����m�F
	bool CheckChangeOverLooking();
	// ���n���J�����ؑ֐ݒ�
	void ChangeOverLookingSetting();

	// �I�t�Z�b�g�ʒu�擾
	const DirectX::SimpleMath::Vector3& GetEyePosition() const;
	// �I�t�Z�b�g�ʒu�ݒ�
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eyeOffsetPosition);
	// �����낵�֑ؑO�̒����_�擾
	const DirectX::SimpleMath::Vector3& GetBeforeTarget() const;
	// �����ݒ�
	void InitSetting(const DirectX::SimpleMath::Vector3& eyePosition);
};