/**
 *
 * @file IEffect.h
 *
 * @brief �G�t�F�N�g�̃C���^�[�t�F�[�X�N���X
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once
namespace KT
{
	class IEffect
	{
	public:

		// �f�X�g���N�^
		virtual ~IEffect() = default;
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Render(
			DirectX::SimpleMath::Matrix view,
			DirectX::SimpleMath::Matrix projection,
			DirectX::SimpleMath::Vector3 eye,
			DirectX::SimpleMath::Vector3 target,
			DirectX::SimpleMath::Vector3 up
		) = 0;

	};
}
