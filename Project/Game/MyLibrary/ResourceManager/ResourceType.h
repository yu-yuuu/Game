#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Model.h"
#include "Audio.h"
#include "Game/Sound/SE.h"
#include "Game/Sound/BGM.h"

//----------------------------------------------
// 自作の共通定義を扱う名前空間
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	// 汎用定義
	//----------------------------------------------
	namespace Utility
	{
		// キー等の名前に使用する
		using NAME = const std::string;
	}

	//----------------------------------------------
	// ファイル関係を扱う名前空間
	//----------------------------------------------
	namespace File
	{
		using namespace Utility;

		// CSVデータ
		using CSVData = std::vector<std::stringstream>;

		// キー名
		static NAME STAGE      = "Stage";     // ステージデータ
		static NAME MODEL      = "Model";     // モデルデータ
		static NAME TEXTURE    = "Texture";   // 画像データ
		static NAME SOUND      = "Sound";     // 音データ
		static NAME OPTION     = "Option";    // 設定データ
		static NAME DEBUG_FONT = "DebugFont"; // デバッグ文字
		static NAME UI         = "UI";        // UIデータ
		static NAME SHADER     = "Shader";    // シェーダーデータ


		// ファイル内で使用する名前
		static NAME STAGE_DATA_TOP  = "Stage"; // ステージデータの先頭検出用
				
	}
	
	//----------------------------------------------
	// テクスチャ関係を扱う名前空間
	//----------------------------------------------
	namespace Texture
	{
		using namespace Utility;
	
		// テクスチャのデータ構造体
		struct TextureData
		{
			// シェーダーリソースビュー
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
			// サイズ
			DirectX::SimpleMath::Vector2 size;
		};

		// テクスチャデータリスト
		using TextureList = std::unordered_map<std::string, TextureData>;
	
		// キー名
		static NAME UI_KEY_S                = "S";              // Sキー
		static NAME UI_KEY_SPACE            = "Space";          // Spaceキー
		static NAME UI_KEY_UP               = "Up";             // Upキー
		static NAME UI_KEY_V                = "V";              // Vキー
		static NAME UI_KEY_W                = "W";              // Wキー
		static NAME UI_KEY_A                = "A";              // Aキー
		static NAME UI_KEY_C                = "C";              // Cキー
		static NAME UI_KEY_D                = "D";              // Dキー
		static NAME UI_KEY_E                = "E";              // Eキー
		static NAME UI_KEY_F                = "F";              // Fキー
		static NAME UI_KEY_DOWN             = "Down";           // Downキー
		static NAME UI_KEY_ENTER            = "Enter";          // Enterキー
		static NAME UI_KEY_ESCAPE           = "Escape";         // Escapeキー
		static NAME UI_KEY_LEFT             = "Left";           // Leftキー
		static NAME UI_KEY_RIGHT            = "Right";          // Rightキー

		static NAME UI_TEXT_CAMERA_ROTATION = "CameraRotation"; // カメラ回転
		static NAME UI_TEXT_CLOSE           = "Close";          // 閉じる
		static NAME UI_TEXT_DECISION        = "Decision";       // 決定
		static NAME UI_TEXT_DIMENSION       = "Dimension";      // 2D3D切替
		static NAME UI_TEXT_JUMP            = "Jump";           // ジャンプ
		static NAME UI_TEXT_MENU            = "Menu";           // メニュー
		static NAME UI_TEXT_OPTION          = "Option";         // ゲーム設定
		static NAME UI_TEXT_OVERLOOKING     = "OverLooking";    // 見渡す
		static NAME UI_TEXT_RETURN          = "Return";         // 戻る(黒枠)
		static NAME UI_TEXT_RETURN_2        = "Return_2";       // 戻る(白枠)
		static NAME UI_TEXT_RETURN_TO_GAME  = "ReturnToGame";   // ゲームへ戻る
		static NAME UI_TEXT_SCALING         = "Scaling";        // 拡縮
		static NAME UI_TEXT_SE              = "SE";             // SE
		static NAME UI_TEXT_SELECT          = "Select";         // 選択
		static NAME UI_TEXT_STAGE_CLEAR     = "StageClear";     // ステージクリア
		static NAME UI_TEXT_STAGE_SELECT    = "StageSelect";    // ステージセレクト
		static NAME UI_TEXT_TITLE_LOGO      = "TitleLogo";      // タイトルロゴ
		static NAME UI_TEXT_TO_STAGE_SELECT = "ToStageSelect";  // ステージセレクトへ
		static NAME UI_TEXT_TO_TITLE        = "ToTitle";        // タイトルへ
		static NAME UI_TEXT_BGM             = "BGM";            // BGM
		static NAME UI_TEXT_CAMERA_MOVE     = "CameraMove";     // カメラ移動
		static NAME UI_TEXT_MOVE            = "Move";           // 移動
		static NAME UI_TEXT_NEXT_SCENE      = "NextScene";      // 次のシーンへ
		static NAME UI_TEXT_PUSH_ENTER      = "PushEnter";      // エンターを押してください
		static NAME UI_TEXT_SKIP            = "Skip";           // スキップ

		static NAME UI_ADJUST_KNOB          = "AdjustKnob";     // 音量調整のつまみ
		static NAME UI_ADJUST_BAR           = "AdjustBar";      // 音量調整のバー

		static NAME UI_SELECT_ARROW         = "SelectArrow"; // 選択表示用の三角形

		static NAME PARTICLE_DUST           = "dust";           // パーティクルの粒
		static NAME WINDOW_FRAME            = "WindowFrame";    // ウィンドウの枠
		static NAME SHADOW                  = "Shadow";         // 影
	}

	//----------------------------------------------
	// モデル関係を扱う名前空間
	//----------------------------------------------
	namespace Model
	{
		using namespace Utility;
		
		// モデルデータ
		using ModelData = std::unique_ptr<DirectX::Model>;
		// モデルデータリスト
		using ModelList = std::unordered_map<std::string, ModelData>;

		// キー名
		static NAME TEXTURE_DIRECTORY = "TextureDirectory"; // モデルテクスチャのディレクトリ
		static NAME PLAYER            = "Player";           // プレイヤー
		static NAME PLAYER_H          = "Player_H";         // プレイヤー
		static NAME GRASS_BLOCK       = "GrassBlock";       // 草ブロック
		static NAME TEST_HOME         = "TestHome";         // テスト用家モデル
		static NAME TEST_FLOOR        = "TestFloor";        // テスト用床モデル
		static NAME GHOST_BLOCK       = "GhostBlock";       // ゴーストブロック
		static NAME GHOST_FLOOR_BLOCK = "GhostFloorBlock";  // ゴースト床ブロック
		static NAME BRICK_BLOCK       = "BrickBlock";       // レンガブロック
		static NAME GOAL_BLOCK        = "GoalBlock";        // ゴールブロック
		static NAME GAME_START_BLOCK  = "GameStartBlock";   // はじめるボタン
		static NAME GAME_END_BLOCK    = "GameEndBlock";     // おわるボタン
		static NAME SKY_DOME          = "SkyDome";          // スカイドーム
		static NAME PLAYER_SILHOUETTE = "PlayerSilhouette"; // プレイヤーシルエット

		static NAME PLAYER_BODY       = "PlayerBody";	    // プレイヤーの体
		static NAME PLAYER_HEAD       = "PlayerHead";	    // プレイヤーの頭
		static NAME PLAYER_ARM_L      = "Player_Arm_L";	    // プレイヤーの左腕
		static NAME PLAYER_ARM_R      = "Player_Arm_R";	    // プレイヤーの右腕
		static NAME PLAYER_LEG_L      = "PlayerLeg_L";	    // プレイヤーの左足
		static NAME PLAYER_LEG_R      = "PlayerLeg_R";	    // プレイヤーの右足

		static NAME PLAYER_TEST       = "PlayerTest";	    // テスト
	}

	//----------------------------------------------
	// 音関係を扱う名前空間
	//----------------------------------------------
	namespace Sound
	{
		using namespace Utility;
		
		// サウンドデータ構造体
		struct SoundData
		{
			// ウェーブバンク
			std::unique_ptr<DirectX::WaveBank> wb;
			// サウンドインスタンス
			std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> sound;
		};

		// サウンドデータリスト
		using SoundList = std::unordered_map<std::string, SoundData>;

		// BGMの音番号
		using BGMNumber = XACT_WAVEBANK_BGM;
		// SEの音番号
		using SENumber = XACT_WAVEBANK_SE;

		// キー名
		static NAME BGM = "BGM"; // BGM
		static NAME SE  = "SE";  // SE
		
		// 設定のプロパティ名（音量）
		static NAME PROPERTIE_SOUND = "Sound";
	}

	//----------------------------------------------
	// UI関係を扱う名前空間
	//----------------------------------------------
	namespace UI
	{
		using namespace Utility;

		// UIのプロパティ名
		static NAME PROPERTIE_TITLE        = "TitleScene";       // UIの使用場所のプロパティ名（タイトルシーン）
		static NAME PROPERTIE_STAGESELECT  = "StageSelectScene"; // UIの使用場所のプロパティ名（ステージセレクトシーン）
		static NAME PROPERTIE_PLAY         = "PlayScene";        // UIの使用場所のプロパティ名（プレイシーン）
		static NAME PROPERTIE_RESULT       = "ResultScene";      // UIの使用場所のプロパティ名（リザルトシーン）
		static NAME PROPERTIE_MEMU         = "MenuWindow";       // UIの使用場所のプロパティ名（メニュー）	

		static NAME PROPERTIE_NAME         = "Name";             // 名前
		static NAME PROPERTIE_IS_OPERATE   = "isOperate";        // 操作するか
		static NAME PROPERTIE_TAG          = "Tag";              // 識別用タグ
		static NAME PROPERTIE_TEXTURE      = "Texture";          // 画像名
		static NAME PROPERTIE_POSITION     = "Position";         // 描画位置
		static NAME PROPERTIE_ANCHOR_POINT = "AnchorPoint";      // アンカーポイント
		static NAME PROPERTIE_SCALE        = "Scale";            // 拡大率
		static NAME PROPERTIE_COLOR        = "Color";            // 色合い
		static NAME PROPERTIE_REVERSE_X    = "ReverseX";         // 横反転させるか
		static NAME PROPERTIE_REVERSE_Y    = "ReverseY";         // 縦反転させるか
		static NAME PROPERTIE_INPUT_KEY    = "InputKey";         // 入力応答させるキー

		// 操作するUIの名前
		static NAME TITLE_PUSH_ENTER_TEXT      = "PushEnterText";          // エンターを押してくださいテキスト
		
		static NAME STAGE_SELECT_ARROW_UP      = "SelectArrowUp";          // ステージ選択用矢印（上向き）
		static NAME STAGE_SELECT_ARROW_DOWN    = "SelectArrowDown";        // ステージ選択用矢印（下向き）
		
		static NAME PLAY_MOVE_BUTTON_UP        = "MoveButtonUp";           // 移動ボタン↑
		static NAME PLAY_MOVE_BUTTON_DOWN      = "MoveButtonDown";         // 移動ボタン↓
		static NAME PLAY_MOVE_BUTTON_RIGHT     = "MoveButtonRight";        // 移動ボタン→
		static NAME PLAY_MOVE_BUTTON_LEFT      = "MoveButtonLeft";         // 移動ボタン左
		static NAME PLAY_JUMP_BUTTON           = "JumpButton";             // ジャンプボタン
		static NAME PLAY_CAMROT_BUTTON_W       = "CameraRotationButtonW";  // カメラ回転ボタンW
		static NAME PLAY_CAMROT_BUTTON_S       = "CameraRotationButtonS";  // カメラ回転ボタンS
		static NAME PLAY_CAMROT_BUTTON_A       = "CameraRotationButtonA";  // カメラ回転ボタンA
		static NAME PLAY_CAMROT_BUTTON_D       = "CameraRotationButtonD";  // カメラ回転ボタンD
		static NAME PLAY_DIMESION_BUTTON       = "DimensionButton";        // 次元切替ボタン
		static NAME PLAY_OVERLOOKING_BUTTON    = "OverLookingButton";      // 見渡しボタン

		static NAME RESULT_NEXT_SCENE_TEXT     = "NextSceneText";          // 次のシーンへテキスト
		static NAME RESULT_TOSELECT_SCENE_TEXT = "ToStageSelectSceneText"; // セレクトシーンへテキスト
		
		static NAME MENU_OPTION_MENU_TEXT      = "OptionMenuText";         // 設定テキスト
		static NAME MENU_TO_TITLE_SCENE_TEXT   = "ToTitleSceneText";       // タイトルへ戻るテキスト
		static NAME MENU_TO_SELECT_SCENE_TEXT  = "ToStageSelectSceneText"; // ステージセレクトへ戻るテキスト
		static NAME MENU_BGM_KNOB              = "BGMKnob";                // BGM調整つまみ
		static NAME MENU_SE_KNOB               = "SEKnob";                 // SE調整つまみ
		static NAME MENU_TO_HOME_MENU          = "ToHomeMenu";             // メニューのホーム画面に戻るテキスト
	}

	//----------------------------------------------
	// シェーダー関係を扱う名前空間
	//----------------------------------------------
	namespace Shader
	{
		using namespace Utility;

		// シェーダーのプロパティ名
		static NAME PROPERTIE_VS = "VS"; // 頂点シェーダー
		static NAME PROPERTIE_GS = "GS"; // ジオメトリシェーダー
		static NAME PROPERTIE_PS = "PS"; // ピクセルシェーダー
	
		// シェーダーの名前
		static NAME FADE              = "Fade";             // フェード
		static NAME EFFECT            = "Effect";           // エフェクト
		static NAME PLAYER_SILHOUETTE = "PlayerSilhouette"; // プレイヤーシルエット
		static NAME GAME_START_MASK   = "GameStartMask";    // ゲーム開始時画面マスク
		static NAME UI                = "UI";               // UI
		static NAME WINDOW            = "Window";           // ウィンドウ
		static NAME MENU_BACKGROUND   = "MenuBackGround";   // メニューウィンドウ背景
	}
}