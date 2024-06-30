//--------------------------------------------------------------------------------------
// File: DisplayCollision.h
//
// �R���W�����\���N���X�i�f�o�b�O�p�j
//
// Usage: AddBoundingSphere��AddBoundingBox�œo�^���Ă��������B
//        DrawCollision�֐��ŕ\�����܂��B�o�^���ꂽ���͕`���N���A����܂��B
//        ���f�����̏Փ˔���p�̃R���W�������̕\���ȂǂɎg�p���Ă��������B
//        �{�b�N�X�͉�]�ɂ͑Ή����Ă��܂���B�iAABB�̏Փ˔���p�j
//        ���R���W�����̌ʂ̐F�w��́A�`��̍������̂��߃��C���̂ݑΉ����Ă��܂��B
//
// Date: 2023.3.8
// Author: Hideyasu Imase
//
//--------------------------------------------------------------------------------------
#pragma once

#include <vector>
#include "SimpleMath.h"
#include "CommonStates.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "DirectXHelpers.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"

// ���C���̕\�����������ꍇ�͒�`���Ă��������B
// DebugDraw.cpp��DebugDraw.h���K�v�ɂȂ�܂��B
// https://github.com/microsoft/DirectXTK/wiki/Utilities
#define _COLLISION_LINE_ON 

namespace Imase
{

	class DisplayCollision
	{
	private:

		// �\���\�ȃR���W�����̍ő吔�i�f�B�t�H���g�j
		static const uint32_t DISPLAY_COLLISION_MAX = 1000;

		// �\���\�ȃR���W�����̍ő吔
		uint32_t m_collisionMax;

		// ���f���̕\��
		bool m_modelActive;

		// ���C���̕\��
		bool m_lineActive;

		// ���̏��
		struct Sphere
		{
			DirectX::SimpleMath::Vector3 center;	// ���S
			float radius;							// ���a
			DirectX::SimpleMath::Color lineColor;	// �F�i���C���p�j

			constexpr Sphere(
				const DirectX::SimpleMath::Vector3& center,
				float radius,
				DirectX::SimpleMath::Color lineColor) noexcept
				: center(center), radius(radius), lineColor(lineColor) {}
		};

		// �{�b�N�X�̏��
		struct Box
		{
			DirectX::SimpleMath::Vector3 center;	// ���S
			DirectX::SimpleMath::Vector3 extents;	// �e�ʂ̒��S����̋���.
			DirectX::SimpleMath::Color lineColor;	// �F�i���C���p�j

			constexpr Box(
				const DirectX::SimpleMath::Vector3& center,
				const DirectX::SimpleMath::Vector3& extents,
				DirectX::SimpleMath::Color lineColor) noexcept
				: center(center), extents(extents), lineColor(lineColor) {}
		};

		// ���̃R���W�������
		std::vector<Sphere> m_spheres;

		// �{�b�N�X�̃R���W�������
		std::vector<Box> m_boxes;

		// ���̃��f��
		std::unique_ptr<DirectX::GeometricPrimitive> m_modelSphere;

		// �{�b�N�X�̃��f��
		std::unique_ptr<DirectX::GeometricPrimitive> m_modelBox;

		// �G�t�F�N�g�i���f���p�j
		std::unique_ptr<DirectX::NormalMapEffect> m_modelEffect;

		// ���̓��C�A�E�g�i���f���p�j
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_modelInputLayout;

		// �C���X�^���X�p���_�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_instancedVB;

		// �v���~�e�B�u�o�b�`�i���C���p�j
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

		// �G�t�F�N�g�i���C���p�j
		std::unique_ptr<DirectX::BasicEffect> m_lineEffect;

		// ���̓��C�A�E�g�i���C���p�j
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_lineInputLayout;

	private:

		// �R���W�������f���̕`��֐�
		void DrawCollisionModel(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj,
			DirectX::FXMVECTOR color
		);

		// �R���W�������C���̕`��֐�
		void DrawCollisionLine(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj,
			DirectX::FXMVECTOR color
		);

	public:

		// �R���X�g���N�^
		DisplayCollision(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			bool modelActive = true,
			bool lineActive = true,
			uint32_t collisionMax = DISPLAY_COLLISION_MAX
		);

		// �o�^���ꂽ�R���W�����̕`��֐�
		void DrawCollision(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj,
			DirectX::FXMVECTOR baseColor = DirectX::Colors::White,
			DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f },
			float alpha = 0.5f
		);
		
		// ���̃R���W������o�^����֐�
		void AddBoundingSphere(
			DirectX::BoundingSphere shpere,
			DirectX::SimpleMath::Vector3 pos,
			DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
		{
			DirectX::XMFLOAT3 center = shpere.Center + pos;
			m_spheres.push_back(Sphere(center, shpere.Radius, lineColor));
		}

		// �{�b�N�X�̃R���W������o�^����֐�
		void AddBoundingBox(
			DirectX::BoundingBox box,
			DirectX::SimpleMath::Vector3 pos,
			DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f })
		{
			DirectX::XMFLOAT3 center = box.Center + pos;
			m_boxes.push_back(Box(center, box.Extents, lineColor));
		}

		// �R���W�������f���̕\���iON/OFF�j
		void SetModelActive(bool active) { m_modelActive = active; }

		// �R���W�������C���̕\���iON/OFF�j
		void SetLineActive(bool active) { m_lineActive = active; }

	};

}


