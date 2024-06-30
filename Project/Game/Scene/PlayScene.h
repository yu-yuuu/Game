/**
 *
 * @file PlayScene.h
 *
 * @brief �v���C�V�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include "Model.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"

#include "Game/Scene/IScene.h"

class SceneManager;
class PlayStage;
class GameCamera;
class Player;
class PlaySceneUI;
class SkyDome;
template<typename Vertex>
class Shader;

class PlayScene : public IScene
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �Q�[���̏��
	enum class GameState
	{
		START,     // �Q�[���J�n��
		PLAY,      // �v���C��
		OVER_LOOK, // �X�e�[�W���n��
		GOAL,      // �S�[��
		MENU,      // ���j���[
	};

//----------------------------------------------
// �萔
//----------------------------------------------
public:

	// �A�j���[�V�����X�L�b�v���o����l�ɂȂ鎞��
	const float ANIMETION_SKIP_TIME = 1.0f;

	// �Q�[���J�n�}�X�N�`��p�|���S��
	const DirectX::VertexPositionTexture VERTICES[4] =
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)), // ����
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)), // �E��
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)), // �E��
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f))  // ����
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;
	
	// �X�e�[�W
	std::unique_ptr<PlayStage> m_stage;
	// �J����
	std::unique_ptr<GameCamera> m_camera;
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// �v���C�V�[����UI�A�摜
	std::unique_ptr<PlaySceneUI> m_ui;
	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> m_skyDome;

	// �Q�[���̏��
	GameState m_gameState;
	// ���j���[�\�����ɊJ������ԕۑ��p
	GameState m_beforeMenuState;

	// �X�e�[�W�Ɏg�p����[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_dssStage;
	// �v���C���[�̃V���G�b�g�Ɏg�p����[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_dssPlayerSilhouette;
	// �v���C���[�V���G�b�g�p�V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPosition>> m_playerSilhouetteShader;
	// �Q�[���J�n����ʃ}�X�N�p�V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_gameStartShader;

	// �A�j���[�V�����X�L�b�v�p�^�C�}�[
	float m_animationSkipTimer;
	// �A�j���[�V�����X�L�b�v��UI��\��������
	bool m_isDispSkipUI;
	// �����؂�ւ����s�t���O
	bool m_isSwitchFail;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	PlayScene(SceneManager* sceneManager);
	// �f�X�g���N�^
	~PlayScene();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Render() override;
	// �㏈��
	void Finalize() override;

	// �V�[���̐؂�ւ�
	void ChangeScene() override;

	// �Q�[���J�n���̍X�V����
	void GameStartUpdate();
	// �Q�[���v���C���̍X�V����
	void GamePlayUpdate();
	// �X�e�[�W���n�����̍X�V����
	void GameOverLookingUpdate();
	// ���j���[���̍X�V����
	void GameMenuUpdate();

	// �����蔻��
	void CollisionDetection();

	// ��ʃ}�X�N�`��
	void RenderMask();

	// �����؂�ւ�
	void ChangeDimension(bool isOwnOperation = true);
	// �S�[���ɓ���
	void ArrivalGoal();
	// �[�x�X�e���V���̍쐬
	void CreateDepthStancil();

	// ���j���[�̕\���E��\��
	void OpenCloseMenu();

	// 2D���ǂ���
	bool Is2D();
	// 3D���ǂ���
	bool Is3D();
	// �����؂�ւ����������邩�m�F
	bool CheckChangeTo2DSuccessful(const DirectX::SimpleMath::Vector3& camDir);
	bool CheckChangeTo3DSuccessful();
	// �����낵���_��
	bool IsTopDown() const;
	// �J�������쒆��
	bool IsOperationCamera() const;
	// �J�������슮��������
	bool IsOperationCompeteCamera() const;
	// �v���C���[���n�ʂɂ��邩
	bool OnGroundPlayer();
	// �Q�[���̏�Ԏ擾
	GameState GetGameState() const;
};