/**
 *
 * @file InputManager.h
 *
 * @brief キー入力を管理するマネージャークラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/21
 *
 */
#pragma once
#include <unordered_map>
#include <initializer_list>

class InputManager
{
//----------------------------------------------
// 構造体
//----------------------------------------------
public:
	
	// キーの押し下げ状態
	struct PushState
	{
		bool down;    // 長押し
		bool press;   // 押した瞬間
		bool release; // 離している
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker* m_keyTracker;
	// キーリスト
	std::unordered_map<DirectX::Keyboard::Keys, PushState> m_keyList;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	InputManager(DirectX::Keyboard::KeyboardStateTracker* keyTracker);
	// デストラクタ
	~InputManager();
	// 更新
	void Update();
	// キーの追加 ( 一つ )
	void AddKey(const DirectX::Keyboard::Keys& keys);
	// キーの追加 ( 複数 )
	void AddKey(const std::initializer_list<DirectX::Keyboard::Keys>& list);
	// キーの削除 ( 一つ )
	void DeleteKey(const DirectX::Keyboard::Keys& keys);
	// キーの削除 ( 複数 )
	void DeleteKey(const std::initializer_list<DirectX::Keyboard::Keys>& list);

	// キーの押し込み状態の取得
	PushState GetKey(const DirectX::Keyboard::Keys& keys);
	// キーの全削除
	void Clear();
	// キーの入力状態初期化
	void Reset();

private:

	// キーボードに入力がされたか確認
	bool IsPushKey(DirectX::Keyboard::State keyState);
	// キーリストのキーが押されているか確認
	void CheckKey(const DirectX::Keyboard::State& keyState);
};

