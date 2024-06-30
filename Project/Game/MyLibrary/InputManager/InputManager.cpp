/**
 *
 * @file InputManager.cpp
 *
 * @brief キー入力を管理するマネージャークラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/21
 *
 */
#include "pch.h"
#include "InputManager.h"
#include <algorithm>

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param keyTracker：キーボードステートトラッカー
 */
InputManager::InputManager(DirectX::Keyboard::KeyboardStateTracker* keyTracker)
	: m_keyTracker(keyTracker)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
InputManager::~InputManager()
{
	Clear();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void InputManager::Update()
{
	// キーボード取得
	Keyboard::State keyState = Keyboard::Get().GetState();

	// キーボードが押されたか確認
	if (IsPushKey(keyState))
	{
		// 登録されたキーが入力されているか確認
		CheckKey(keyState);
	}
}

//------------------------------------------------------------------
/**
 * @brief キーの追加 ( 一つ )
 *
 * @param  keys：追加するキー
 * @return なし
 */
void InputManager::AddKey(const DirectX::Keyboard::Keys& keys)
{
	// すでに追加してあるか確認
	if (m_keyList.count(keys) != 0) return;

	// キーを追加
	m_keyList[keys] = PushState{};
}

//------------------------------------------------------------------
/**
 * @brief キーの追加 ( 複数 )
 *
 * @param  list：追加するキーリスト
 * @return なし
 */
void InputManager::AddKey(const std::initializer_list<DirectX::Keyboard::Keys>& list)
{
	for (DirectX::Keyboard::Keys keys : list)
	{
		AddKey(keys);
	}
}

//------------------------------------------------------------------
/**
 * @brief キーの削除 ( 一つ )
 *
 * @param  keys：削除するキー
 * @return なし
 */
void InputManager::DeleteKey(const DirectX::Keyboard::Keys& keys)
{
	// エイリアス宣言
	using List = std::unordered_map<DirectX::Keyboard::Keys, PushState>;

	// 削除対象のキーを探す
	List::iterator findKey = std::find_if(m_keyList.begin(), m_keyList.end(), 
		[&](const std::pair<DirectX::Keyboard::Keys, PushState>& pair)
		{
			return pair.first == keys;
		}
	);

	// 見つからないなら終了
	assert(findKey != m_keyList.end() && "削除対象のキーが登録されていません");
	// キー削除
	m_keyList.erase(findKey);
}

//------------------------------------------------------------------
/**
 * @brief キーの削除 ( 複数 )
 *
 * @param  list：削除するキーリスト
 * @return なし
 */
void InputManager::DeleteKey(const std::initializer_list<DirectX::Keyboard::Keys>& list)
{
	for (const DirectX::Keyboard::Keys& keys : list)
	{
		DeleteKey(keys);
	}
}

//------------------------------------------------------------------
/**
 * @brief キーの押し込み状態の取得
 *
 * @param  keys     ：押し込み状態を確信したいキー
 * @return PushState：キーの押し込み状態
 */
InputManager::PushState InputManager::GetKey(const DirectX::Keyboard::Keys& keys)
{
	// キーが登録されていなければ押されていない状態を返す
	if (m_keyList.count(keys) == 0) return PushState{ false, false, false };

	// キーの押し込み状態を返す
	return m_keyList[keys];
}

//------------------------------------------------------------------
/**
 * @brief キーの全削除
 *
 * @param なし
 * @return なし
 */
void InputManager::Clear()
{
	m_keyList.clear();
}

//------------------------------------------------------------------
/**
 * @brief キーの入力状態初期化
 *
 * @param  なし
 * @return なし
 */
void InputManager::Reset()
{
	std::for_each(m_keyList.begin(), m_keyList.end(),
		[&](std::pair<const DirectX::Keyboard::Keys, PushState>& data)
		{
			// 入力状態取得
			PushState& state = data.second;
			// 入力状態をリセット
			state.down = state.press = state.release = false;
		}
	);
}

//------------------------------------------------------------------
/**
 * @brief キーボードに入力がされたか確認
 *
 * @param  keyState：キーボードステート
 * @return なし
 */
bool InputManager::IsPushKey(DirectX::Keyboard::State keyState)
{
	auto ptr = reinterpret_cast<uint32_t*>(&keyState);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int bf = 1u << (key & 0x1f);
		if (ptr[(key >> 5)] && bf)
			// キーが押下げられた
			return true;
	}

	// キーが押し下げられていない
	return false;
}

//------------------------------------------------------------------
/**
 * @brief キーリストのキーが押されているか確認
 *
 * @param  keyState：キーの状態
 * @return なし
 */
void InputManager::CheckKey(const DirectX::Keyboard::State& keyState)
{
	std::for_each(m_keyList.begin(), m_keyList.end(),
		[&](std::pair<const DirectX::Keyboard::Keys, PushState>& data)
		{
			// キー取得
			DirectX::Keyboard::Keys keys = data.first;
			// 入力状態取得
			PushState& state = data.second;
			// キーが入力されているか判定
			state.down    = keyState.IsKeyDown(keys);
			state.press   = m_keyTracker->IsKeyPressed(keys);
			state.release = m_keyTracker->IsKeyReleased(keys);
		}
	);
}