/**
 *
 * @file SceneUI.cpp
 *
 * @brief �V�[���ɔz�u����UI���܂Ƃ߂�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "SceneUI.h"

#include "Game/UI/OperatableUI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
 */
SceneUI::SceneUI()
	: m_newList()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
SceneUI::~SceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneUI::Update()
{
	// �p����ŏ���������΋L�q����
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[�֓o�^
 *
 * @param tag�F�o�^����UI�̃L�[
 * @return �Ȃ�
 */
void SceneUI::AddUIManager(const std::string& tag)
{
	// UI�}�l�[�W���[�󂯎��
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();

	for (auto& ui : m_newList)
	{
		// UI�}�l�[�W���[�֓o�^
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			if (tag != t) continue;

			uiManager->AddUI(ui.second.get());
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[�փ��X�g���S�Ă�UI��o�^
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneUI::AddUIManagerAll()
{
	for (auto& ui : m_newList)
	{
		// UI�}�l�[�W���[�֓o�^
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			AddUIManager(t);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[����폜
 *
 * @param tag�F
 * @return �Ȃ�
 */
void SceneUI::DeleteUIManager(const std::string& tag)
{
	// UI�}�l�[�W���[�󂯎��
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	for (auto& ui : m_newList)
	{
		// UI�}�l�[�W���[�֓o�^
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			if (tag != t) continue;

			uiManager->Delete(ui.second.get());
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[�փ��X�g���S�Ă�UI���폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneUI::DeleteUIManagerAll()
{
	for (auto& ui : m_newList)
	{
		// UI�}�l�[�W���[�֓o�^
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			DeleteUIManager(t);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief �V�[��UI���}�l�[�W���[�ɐݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneUI::SetUIManagerSceneUI()
{
	// UI�}�l�[�W���[�󂯎��
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	// �V�[��UI���}�l�[�W���[�֓o�^
	uiManager->SetSceneUI(this);
}

//------------------------------------------------------------------
/**
 * @brief �V�[��UI���}�l�[�W���[����폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneUI::DeleteUIManagerSceneUI()
{
	// UI�}�l�[�W���[�󂯎��
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	// �V�[��UI���}�l�[�W���[����폜
	uiManager->DeleteSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief UI�쐬�i�Ăяo���p�j
 *
 * @param  sceneName�F�쐬����V�[���̖��O
 * @return �Ȃ�
 */
void SceneUI::CreateUI(const std::string& sceneName)
{
	using namespace KT::UI;

	// UI�f�[�^�擾
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json uiData = FileManager::LoadJSON(filePathList->GetPath(KT::File::UI));
	nlohmann::json sceneUIData = uiData[sceneName];

	for (const nlohmann::json& data : sceneUIData)
	{
		// UI�̖��O
		std::string name = data[PROPERTIE_NAME];
		// ���삷�邩
		bool isOperate = data[PROPERTIE_IS_OPERATE];
		// �g�p����摜�̖��O
		std::string texName = data[PROPERTIE_TEXTURE];
		// �`��ʒu
		SimpleMath::Vector2 position = SimpleMath::Vector2(data[PROPERTIE_POSITION][0], data[PROPERTIE_POSITION][1]);
		// �A���J�[�|�C���g
		Texture::AnchorPoint anchorPoint = static_cast<Texture::AnchorPoint>(data[PROPERTIE_ANCHOR_POINT]);
		// �g�嗦
		SimpleMath::Vector2 scale = SimpleMath::Vector2(data[PROPERTIE_SCALE][0], data[PROPERTIE_SCALE][1]);
		// UI�̐F����
		SimpleMath::Color color = SimpleMath::Color(data[PROPERTIE_COLOR][0], data[PROPERTIE_COLOR][1], data[PROPERTIE_COLOR][2], data[PROPERTIE_COLOR][3]);
		// �c�A���𔽓]�����邩
		bool reverseX = data[PROPERTIE_REVERSE_X];
		bool reverseY = data[PROPERTIE_REVERSE_Y];
		// �Ή�������L�[
		std::string keyStr = data[PROPERTIE_INPUT_KEY];
		Keyboard::Keys key = static_cast<Keyboard::Keys>(KT::MyUtility::ConvertToHexadecimal(keyStr));
		// �^�O
		std::vector<std::string> tagList;
		for (const nlohmann::json& tag : data[PROPERTIE_TAG])
		{
			tagList.push_back(tag);
		}

		// UI�쐬
		if (isOperate) m_newList[name] = std::move(CreateOperatableUI(tagList, texName, anchorPoint, position, scale, color, key, reverseX, reverseY));
		else           m_newList[name] = std::move(CreateUI(tagList, texName, anchorPoint, position, scale, color, reverseX, reverseY));
	}
}

//------------------------------------------------------------------
/**
 * @brief ����UI�̎擾
 *
 * @param name�F�擾������UI�̖��O
 * @return OperatableUI*�F����UI�̃|�C���^
 */
OperatableUI* SceneUI::GetUI(const std::string& name)
{
	for (auto& ui : m_newList)
	{
		// �擾���������O�łȂ��Ȃ��΂�
		if (ui.first != name) continue;

		// UI�𑀍�UI�փL���X�g
		OperatableUI* opUI = dynamic_cast<OperatableUI*>(ui.second.get());

		assert(opUI && "�擾������UI������UI�ł͂���܂���");

		return opUI;
	}
	// ���݂��Ȃ��Ȃ狭���I��
	assert(false && "�擾������UI�����݂��܂���");
	return nullptr;
}

//------------------------------------------------------------------
/**
 * @brief �ʏ�UI�쐬
 *
 * @param tagList        �F���ʗp�^�O���X�g
 * @param texName        �FUI�Ɏg�p����e�N�X�`���̖��O
 * @param anchor         �F�A���J�[�|�C���g
 * @param position       �F�`��ʒu
 * @param scale          �F�X�P�[��
 * @param color          �F�e�N�X�`���̐F����
 * @param reverseX       �F���𔽓]�\�������邩
 * @param reverseY       �F�c�𔽓]�\�������邩
 * @return unique_ptr<UI>�F�쐬����UI
 */
std::unique_ptr<UI> SceneUI::CreateUI(
	const std::vector<std::string>& tagList,
	const std::string& texName,
	const Texture::AnchorPoint& anchor,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const DirectX::SimpleMath::Color& color,
	const bool& reverseX,
	const bool& reverseY)
{
	// ���\�[�X�}�l�[�W���[�󂯎��
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	// �e�N�X�`���󂯎��
	KT::Texture::TextureData data = resourceManager->GetTexture(texName);
	// �e�N�X�`���쐬
	std::unique_ptr<Texture> texture = std::make_unique<Texture>(data, anchor, scale, color);
	// UI�쐬
	std::unique_ptr<UI> ui = std::make_unique<UI>(tagList, std::move(texture), position, reverseX, reverseY);

	return std::move(ui);
}

//------------------------------------------------------------------
/**
 * @brief ����UI�쐬
 *
 * @param tagList        �F���ʗp�^�O���X�g
 * @param texName        �FUI�Ɏg�p����e�N�X�`���̖��O
 * @param anchor         �F�A���J�[�|�C���g
 * @param position       �F�`��ʒu
 * @param scale          �F�X�P�[��
 * @param color          �F�e�N�X�`���̐F����
 * @param key            �F�Ή�������L�[
 * @param reverseX       �F���𔽓]�\�������邩
 * @param reverseY       �F�c�𔽓]�\�������邩
 * @return unique_ptr<UI>�F�쐬����UI
 */
std::unique_ptr<OperatableUI> SceneUI::CreateOperatableUI(
	const std::vector<std::string>& tagList,
	const std::string& texName,
	const Texture::AnchorPoint& anchor,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const DirectX::SimpleMath::Color& color,
	const DirectX::Keyboard::Keys& key,
	const bool& reverseX,
	const bool& reverseY)
{
	// ���\�[�X�}�l�[�W���[�󂯎��
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	// �e�N�X�`���󂯎��
	KT::Texture::TextureData data = resourceManager->GetTexture(texName);
	// �e�N�X�`���쐬
	std::unique_ptr<Texture> texture = std::make_unique<Texture>(data, anchor, scale, color);
	// ����UI�쐬
	std::unique_ptr<OperatableUI> operatableUI = std::make_unique<OperatableUI>(tagList, std::move(texture), position, key, reverseX, reverseY);

	return operatableUI;
}