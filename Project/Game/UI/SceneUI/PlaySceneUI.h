/**
 *
 * @file PlaySceneUI.h
 *
 * @brief �v���C�V�[���Ŏg�p����UI�A�摜�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class PlayScene;
class Player;
class GameCamera;
class OperatableUI;

class PlaySceneUI : public SceneUI
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �v���C��Ԃŏ�ɕ`�悷��UI�̃^�O
	const std::string TAG_PLAY_ALWAYS           = "Always";
	// �J�n�A�j���[�V����UI�̃^�O
	const std::string TAG_START_ANIMATION       = "StartAnimation";
	// �v���C���UI�̃^�O
	const std::string TAG_PLAY_STATE            = "PlayState";
	// 2D���n�����UI�^�O
	const std::string TAG_OVER_LOOKING_STATE_2D = "OverLooking2D";
	// 3D���n�����UI�̃^�O
	const std::string TAG_OVER_LOOKING_STATE_3D = "OverLooking3D";

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C�V�[��
	PlayScene* m_playScene;
	// �v���C���[
	Player* m_player;
	// �J����
	GameCamera* m_camera;

	// �ړ��{�^��
	OperatableUI* m_moveButtonUp;
	OperatableUI* m_moveButtonDown;
	OperatableUI* m_moveButtonRight;
	OperatableUI* m_moveButtonLeft;
	// �W�����v�{�^��
	OperatableUI* m_jumpButton;
	// �J�����̉�]�{�^��
	OperatableUI* m_camRotButtonW;
	OperatableUI* m_camRotButtonS;
	OperatableUI* m_camRotButtonA;
	OperatableUI* m_camRotButtonD;
	// �����؂�ւ��{�^��
	OperatableUI* m_dimensionButton;
	// ���n���{�^��
	OperatableUI* m_overLookingButton;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	PlaySceneUI(PlayScene* playScene, Player* player, GameCamera* camera);
	// �f�X�g���N�^
	~PlaySceneUI();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;

	// �v���C���X�V
	void PlayUpdate();
	// ���n�����X�V
	void OverLookingUpdate();

	// �J�n���A�j���[�V�����X�L�b�vUI�\��
	void ShowSkipUI();
	// �J�n���A�j���[�V��������v���C��Ԃ�
	void ChangeStateAnimationToPlay();
	// ���j���[����v���C��Ԃ֐ؑ�
	void ChangeStateMenuToPlay();
	// ���j���[���猩�n����Ԃ֐ؑ�
	void ChangeStateMenuToOverLooking();
	// �v���C���猩�n����Ԃ֐ؑ�
	void ChangeStatePlayToOverLooking();
	// ���n������v���C��Ԃ֐ؑ�
	void ChangeStateOverLookingToPlay();

	// ���n����Ԃ̃L�[���擾����
	std::string GetOverLookingKey(bool is2D);
};