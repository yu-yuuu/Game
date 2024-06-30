#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Model.h"
#include "Audio.h"
#include "Game/Sound/SE.h"
#include "Game/Sound/BGM.h"

//----------------------------------------------
// ����̋��ʒ�`���������O���
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	// �ėp��`
	//----------------------------------------------
	namespace Utility
	{
		// �L�[���̖��O�Ɏg�p����
		using NAME = const std::string;
	}

	//----------------------------------------------
	// �t�@�C���֌W���������O���
	//----------------------------------------------
	namespace File
	{
		using namespace Utility;

		// CSV�f�[�^
		using CSVData = std::vector<std::stringstream>;

		// �L�[��
		static NAME STAGE      = "Stage";     // �X�e�[�W�f�[�^
		static NAME MODEL      = "Model";     // ���f���f�[�^
		static NAME TEXTURE    = "Texture";   // �摜�f�[�^
		static NAME SOUND      = "Sound";     // ���f�[�^
		static NAME OPTION     = "Option";    // �ݒ�f�[�^
		static NAME DEBUG_FONT = "DebugFont"; // �f�o�b�O����
		static NAME UI         = "UI";        // UI�f�[�^
		static NAME SHADER     = "Shader";    // �V�F�[�_�[�f�[�^


		// �t�@�C�����Ŏg�p���閼�O
		static NAME STAGE_DATA_TOP  = "Stage"; // �X�e�[�W�f�[�^�̐擪���o�p
				
	}
	
	//----------------------------------------------
	// �e�N�X�`���֌W���������O���
	//----------------------------------------------
	namespace Texture
	{
		using namespace Utility;
	
		// �e�N�X�`���̃f�[�^�\����
		struct TextureData
		{
			// �V�F�[�_�[���\�[�X�r���[
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
			// �T�C�Y
			DirectX::SimpleMath::Vector2 size;
		};

		// �e�N�X�`���f�[�^���X�g
		using TextureList = std::unordered_map<std::string, TextureData>;
	
		// �L�[��
		static NAME UI_KEY_S                = "S";              // S�L�[
		static NAME UI_KEY_SPACE            = "Space";          // Space�L�[
		static NAME UI_KEY_UP               = "Up";             // Up�L�[
		static NAME UI_KEY_V                = "V";              // V�L�[
		static NAME UI_KEY_W                = "W";              // W�L�[
		static NAME UI_KEY_A                = "A";              // A�L�[
		static NAME UI_KEY_C                = "C";              // C�L�[
		static NAME UI_KEY_D                = "D";              // D�L�[
		static NAME UI_KEY_E                = "E";              // E�L�[
		static NAME UI_KEY_F                = "F";              // F�L�[
		static NAME UI_KEY_DOWN             = "Down";           // Down�L�[
		static NAME UI_KEY_ENTER            = "Enter";          // Enter�L�[
		static NAME UI_KEY_ESCAPE           = "Escape";         // Escape�L�[
		static NAME UI_KEY_LEFT             = "Left";           // Left�L�[
		static NAME UI_KEY_RIGHT            = "Right";          // Right�L�[

		static NAME UI_TEXT_CAMERA_ROTATION = "CameraRotation"; // �J������]
		static NAME UI_TEXT_CLOSE           = "Close";          // ����
		static NAME UI_TEXT_DECISION        = "Decision";       // ����
		static NAME UI_TEXT_DIMENSION       = "Dimension";      // 2D3D�ؑ�
		static NAME UI_TEXT_JUMP            = "Jump";           // �W�����v
		static NAME UI_TEXT_MENU            = "Menu";           // ���j���[
		static NAME UI_TEXT_OPTION          = "Option";         // �Q�[���ݒ�
		static NAME UI_TEXT_OVERLOOKING     = "OverLooking";    // ���n��
		static NAME UI_TEXT_RETURN          = "Return";         // �߂�(���g)
		static NAME UI_TEXT_RETURN_2        = "Return_2";       // �߂�(���g)
		static NAME UI_TEXT_RETURN_TO_GAME  = "ReturnToGame";   // �Q�[���֖߂�
		static NAME UI_TEXT_SCALING         = "Scaling";        // �g�k
		static NAME UI_TEXT_SE              = "SE";             // SE
		static NAME UI_TEXT_SELECT          = "Select";         // �I��
		static NAME UI_TEXT_STAGE_CLEAR     = "StageClear";     // �X�e�[�W�N���A
		static NAME UI_TEXT_STAGE_SELECT    = "StageSelect";    // �X�e�[�W�Z���N�g
		static NAME UI_TEXT_TITLE_LOGO      = "TitleLogo";      // �^�C�g�����S
		static NAME UI_TEXT_TO_STAGE_SELECT = "ToStageSelect";  // �X�e�[�W�Z���N�g��
		static NAME UI_TEXT_TO_TITLE        = "ToTitle";        // �^�C�g����
		static NAME UI_TEXT_BGM             = "BGM";            // BGM
		static NAME UI_TEXT_CAMERA_MOVE     = "CameraMove";     // �J�����ړ�
		static NAME UI_TEXT_MOVE            = "Move";           // �ړ�
		static NAME UI_TEXT_NEXT_SCENE      = "NextScene";      // ���̃V�[����
		static NAME UI_TEXT_PUSH_ENTER      = "PushEnter";      // �G���^�[�������Ă�������
		static NAME UI_TEXT_SKIP            = "Skip";           // �X�L�b�v

		static NAME UI_ADJUST_KNOB          = "AdjustKnob";     // ���ʒ����̂܂�
		static NAME UI_ADJUST_BAR           = "AdjustBar";      // ���ʒ����̃o�[

		static NAME UI_SELECT_ARROW         = "SelectArrow"; // �I��\���p�̎O�p�`

		static NAME PARTICLE_DUST           = "dust";           // �p�[�e�B�N���̗�
		static NAME WINDOW_FRAME            = "WindowFrame";    // �E�B���h�E�̘g
		static NAME SHADOW                  = "Shadow";         // �e
	}

	//----------------------------------------------
	// ���f���֌W���������O���
	//----------------------------------------------
	namespace Model
	{
		using namespace Utility;
		
		// ���f���f�[�^
		using ModelData = std::unique_ptr<DirectX::Model>;
		// ���f���f�[�^���X�g
		using ModelList = std::unordered_map<std::string, ModelData>;

		// �L�[��
		static NAME TEXTURE_DIRECTORY = "TextureDirectory"; // ���f���e�N�X�`���̃f�B���N�g��
		static NAME PLAYER            = "Player";           // �v���C���[
		static NAME PLAYER_H          = "Player_H";         // �v���C���[
		static NAME GRASS_BLOCK       = "GrassBlock";       // ���u���b�N
		static NAME TEST_HOME         = "TestHome";         // �e�X�g�p�ƃ��f��
		static NAME TEST_FLOOR        = "TestFloor";        // �e�X�g�p�����f��
		static NAME GHOST_BLOCK       = "GhostBlock";       // �S�[�X�g�u���b�N
		static NAME GHOST_FLOOR_BLOCK = "GhostFloorBlock";  // �S�[�X�g���u���b�N
		static NAME BRICK_BLOCK       = "BrickBlock";       // �����K�u���b�N
		static NAME GOAL_BLOCK        = "GoalBlock";        // �S�[���u���b�N
		static NAME GAME_START_BLOCK  = "GameStartBlock";   // �͂��߂�{�^��
		static NAME GAME_END_BLOCK    = "GameEndBlock";     // �����{�^��
		static NAME SKY_DOME          = "SkyDome";          // �X�J�C�h�[��
		static NAME PLAYER_SILHOUETTE = "PlayerSilhouette"; // �v���C���[�V���G�b�g

		static NAME PLAYER_BODY       = "PlayerBody";	    // �v���C���[�̑�
		static NAME PLAYER_HEAD       = "PlayerHead";	    // �v���C���[�̓�
		static NAME PLAYER_ARM_L      = "Player_Arm_L";	    // �v���C���[�̍��r
		static NAME PLAYER_ARM_R      = "Player_Arm_R";	    // �v���C���[�̉E�r
		static NAME PLAYER_LEG_L      = "PlayerLeg_L";	    // �v���C���[�̍���
		static NAME PLAYER_LEG_R      = "PlayerLeg_R";	    // �v���C���[�̉E��

		static NAME PLAYER_TEST       = "PlayerTest";	    // �e�X�g
	}

	//----------------------------------------------
	// ���֌W���������O���
	//----------------------------------------------
	namespace Sound
	{
		using namespace Utility;
		
		// �T�E���h�f�[�^�\����
		struct SoundData
		{
			// �E�F�[�u�o���N
			std::unique_ptr<DirectX::WaveBank> wb;
			// �T�E���h�C���X�^���X
			std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> sound;
		};

		// �T�E���h�f�[�^���X�g
		using SoundList = std::unordered_map<std::string, SoundData>;

		// BGM�̉��ԍ�
		using BGMNumber = XACT_WAVEBANK_BGM;
		// SE�̉��ԍ�
		using SENumber = XACT_WAVEBANK_SE;

		// �L�[��
		static NAME BGM = "BGM"; // BGM
		static NAME SE  = "SE";  // SE
		
		// �ݒ�̃v���p�e�B���i���ʁj
		static NAME PROPERTIE_SOUND = "Sound";
	}

	//----------------------------------------------
	// UI�֌W���������O���
	//----------------------------------------------
	namespace UI
	{
		using namespace Utility;

		// UI�̃v���p�e�B��
		static NAME PROPERTIE_TITLE        = "TitleScene";       // UI�̎g�p�ꏊ�̃v���p�e�B���i�^�C�g���V�[���j
		static NAME PROPERTIE_STAGESELECT  = "StageSelectScene"; // UI�̎g�p�ꏊ�̃v���p�e�B���i�X�e�[�W�Z���N�g�V�[���j
		static NAME PROPERTIE_PLAY         = "PlayScene";        // UI�̎g�p�ꏊ�̃v���p�e�B���i�v���C�V�[���j
		static NAME PROPERTIE_RESULT       = "ResultScene";      // UI�̎g�p�ꏊ�̃v���p�e�B���i���U���g�V�[���j
		static NAME PROPERTIE_MEMU         = "MenuWindow";       // UI�̎g�p�ꏊ�̃v���p�e�B���i���j���[�j	

		static NAME PROPERTIE_NAME         = "Name";             // ���O
		static NAME PROPERTIE_IS_OPERATE   = "isOperate";        // ���삷�邩
		static NAME PROPERTIE_TAG          = "Tag";              // ���ʗp�^�O
		static NAME PROPERTIE_TEXTURE      = "Texture";          // �摜��
		static NAME PROPERTIE_POSITION     = "Position";         // �`��ʒu
		static NAME PROPERTIE_ANCHOR_POINT = "AnchorPoint";      // �A���J�[�|�C���g
		static NAME PROPERTIE_SCALE        = "Scale";            // �g�嗦
		static NAME PROPERTIE_COLOR        = "Color";            // �F����
		static NAME PROPERTIE_REVERSE_X    = "ReverseX";         // �����]�����邩
		static NAME PROPERTIE_REVERSE_Y    = "ReverseY";         // �c���]�����邩
		static NAME PROPERTIE_INPUT_KEY    = "InputKey";         // ���͉���������L�[

		// ���삷��UI�̖��O
		static NAME TITLE_PUSH_ENTER_TEXT      = "PushEnterText";          // �G���^�[�������Ă��������e�L�X�g
		
		static NAME STAGE_SELECT_ARROW_UP      = "SelectArrowUp";          // �X�e�[�W�I��p���i������j
		static NAME STAGE_SELECT_ARROW_DOWN    = "SelectArrowDown";        // �X�e�[�W�I��p���i�������j
		
		static NAME PLAY_MOVE_BUTTON_UP        = "MoveButtonUp";           // �ړ��{�^����
		static NAME PLAY_MOVE_BUTTON_DOWN      = "MoveButtonDown";         // �ړ��{�^����
		static NAME PLAY_MOVE_BUTTON_RIGHT     = "MoveButtonRight";        // �ړ��{�^����
		static NAME PLAY_MOVE_BUTTON_LEFT      = "MoveButtonLeft";         // �ړ��{�^����
		static NAME PLAY_JUMP_BUTTON           = "JumpButton";             // �W�����v�{�^��
		static NAME PLAY_CAMROT_BUTTON_W       = "CameraRotationButtonW";  // �J������]�{�^��W
		static NAME PLAY_CAMROT_BUTTON_S       = "CameraRotationButtonS";  // �J������]�{�^��S
		static NAME PLAY_CAMROT_BUTTON_A       = "CameraRotationButtonA";  // �J������]�{�^��A
		static NAME PLAY_CAMROT_BUTTON_D       = "CameraRotationButtonD";  // �J������]�{�^��D
		static NAME PLAY_DIMESION_BUTTON       = "DimensionButton";        // �����ؑփ{�^��
		static NAME PLAY_OVERLOOKING_BUTTON    = "OverLookingButton";      // ���n���{�^��

		static NAME RESULT_NEXT_SCENE_TEXT     = "NextSceneText";          // ���̃V�[���փe�L�X�g
		static NAME RESULT_TOSELECT_SCENE_TEXT = "ToStageSelectSceneText"; // �Z���N�g�V�[���փe�L�X�g
		
		static NAME MENU_OPTION_MENU_TEXT      = "OptionMenuText";         // �ݒ�e�L�X�g
		static NAME MENU_TO_TITLE_SCENE_TEXT   = "ToTitleSceneText";       // �^�C�g���֖߂�e�L�X�g
		static NAME MENU_TO_SELECT_SCENE_TEXT  = "ToStageSelectSceneText"; // �X�e�[�W�Z���N�g�֖߂�e�L�X�g
		static NAME MENU_BGM_KNOB              = "BGMKnob";                // BGM�����܂�
		static NAME MENU_SE_KNOB               = "SEKnob";                 // SE�����܂�
		static NAME MENU_TO_HOME_MENU          = "ToHomeMenu";             // ���j���[�̃z�[����ʂɖ߂�e�L�X�g
	}

	//----------------------------------------------
	// �V�F�[�_�[�֌W���������O���
	//----------------------------------------------
	namespace Shader
	{
		using namespace Utility;

		// �V�F�[�_�[�̃v���p�e�B��
		static NAME PROPERTIE_VS = "VS"; // ���_�V�F�[�_�[
		static NAME PROPERTIE_GS = "GS"; // �W�I���g���V�F�[�_�[
		static NAME PROPERTIE_PS = "PS"; // �s�N�Z���V�F�[�_�[
	
		// �V�F�[�_�[�̖��O
		static NAME FADE              = "Fade";             // �t�F�[�h
		static NAME EFFECT            = "Effect";           // �G�t�F�N�g
		static NAME PLAYER_SILHOUETTE = "PlayerSilhouette"; // �v���C���[�V���G�b�g
		static NAME GAME_START_MASK   = "GameStartMask";    // �Q�[���J�n����ʃ}�X�N
		static NAME UI                = "UI";               // UI
		static NAME WINDOW            = "Window";           // �E�B���h�E
		static NAME MENU_BACKGROUND   = "MenuBackGround";   // ���j���[�E�B���h�E�w�i
	}
}