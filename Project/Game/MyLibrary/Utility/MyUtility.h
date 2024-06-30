/**
 *
 * @file MyUtility.h
 *
 * @brief ����̔ėp�֐����W�߂��N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/12
 *
 */
#pragma once
#include <string>
#include "Game/MyLibrary/CommonResource/GameResource.h"

namespace KT
{
	class MyUtility
	{
	//----------------------------------------------
	// �֐�
	//----------------------------------------------
	public:

		// �x�N�g���̐�Βl�����߂�
		static DirectX::SimpleMath::Vector3 AbsVector(const DirectX::SimpleMath::Vector3& vec);

		// �x�N�g���̐������̂݋��߂�
		static DirectX::SimpleMath::Vector3 ModVector(const DirectX::SimpleMath::Vector3& vec);
		// �x�N�g���t���O�𔽓]
		static DirectX::SimpleMath::Vector3 InverseFlag(const DirectX::SimpleMath::Vector3& vec);
		// �x�N�g���̃N�����v����
		static DirectX::SimpleMath::Vector3 Clamp(
			const DirectX::SimpleMath::Vector3& value,
			const DirectX::SimpleMath::Vector3& min,
			const DirectX::SimpleMath::Vector3& max
		);
		// 6�����x�N�g���̌덷���Ȃ���
		// ( �㉺ ���E ����O��0��1�݂̂̃x�N�g�� )
		static DirectX::SimpleMath::Vector3 EliminateDirectionError(const DirectX::SimpleMath::Vector3& vec);
		// 2��float�^�ϐ����قړ������m�F����
		static bool FloatPresqueEqual(const float& f1, const float& f2);

		// ���j���[�I��
		template<typename ENUM>
		static void MenuSelect(bool countUpKey, bool countDownKey, ENUM& enumMenu, bool playSE = true);
		// string ���� wstring �֕ϊ�
		static std::wstring  StringToWide(const std::string& str);
		// string ���� 16�i���̐��l�֕ϊ�
		static int ConvertToHexadecimal(const std::string& str);
	};

	//----------------------------------------------
	// �e���v���[�g�֐���`
	//----------------------------------------------

   //------------------------------------------------------------------
   /**
	* @brief ���j���[�I��
	* @brief �����@ENUM�ɂ͐���\��COUNT��ǉ����Ă�������
	*
	* @tparam ENUM        �F���j���[�Ɏg�p���Ă���񋓑�
	* @param  countUpKey  �F���j���[�ԍ����J�E���g�A�b�v������L�[�̓��͏�
	* @param  countDownKey�F���j���[�ԍ����J�E���g�_�E��������L�[�̓��͏�
	* @param  enumMenu    �F���ݑI�����Ă��郁�j���[
	* @param  playSE      �FSE���Đ����邩
	* @return �Ȃ�
	*/
	template<typename ENUM>
	inline void MyUtility::MenuSelect(bool countUpKey, bool countDownKey, ENUM& enumMenu, bool playSE)
	{
		// ���j���[�̍ő吔���擾
		int max = static_cast<int>(ENUM::COUNT);

		// ���ݑI�����Ă��郁�j���[���擾
		int current = static_cast<int>(enumMenu);

		// �J�E���g�A�b�v
		if (countUpKey)
		{
			current--;

			// �}�C�i�X�Ȃ�
			if (current < 0)
			{
				// �����̃��j���[��ݒ�
				current = max - 1;
			}
		}
		// �J�E���g�_�E��
		else if (countDownKey)
		{
			current++;

			// ���j���[�̐��Ɠ����Ȃ�
			if (current == max)
			{
				// �擪�̃��j���[��ݒ�
				current = 0;
			}
		}

		// ���l��񋓑̂ɒ���
		enumMenu = static_cast<ENUM>(current);

		// �I����SE�𗬂�
		if ((countUpKey || countDownKey) && playSE)
		{
			GameResource::GetInstance()->GetResourceManager()->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_MOVECURSOL);
		}
	}
}