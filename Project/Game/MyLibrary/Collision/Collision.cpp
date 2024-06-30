/**
 *
 * @file Collision.cpp
 *
 * @brief �����蔻�菈�����s���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/3
 *
 */
#include "pch.h"
#include "Collision.h"

#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;


//------------------------------------------------------------------
/**
 * @brief AABB����
 *
 * @param �@is2D           �F2D���ǂ���
 * @param �@cameraDirection�F�J�����̌���
 * @param �@box1           �F����Ɏg�p���锠�P
 * @param �@box2           �F����Ɏg�p���锠�Q
 * @return  true           �F�������Ă���
 * @return  false          �F�������Ă��Ȃ�
 */
bool Collision::AABBCheck(
    bool is2D, 
    const DirectX::SimpleMath::Vector3& cameraDirection, 
    const BoxCollider& box1,
    const BoxCollider& box2)
{
    // �ʒu�A�����擾
    SimpleMath::Vector3 pos1 = box1.GetPosition();
    SimpleMath::Vector3 pos2 = box2.GetPosition();
    SimpleMath::Vector3 ext1 = box1.GetExtents();
    SimpleMath::Vector3 ext2 = box2.GetExtents();

    // 2D��
    if (is2D)
    {
        // ����Ɏg���������v�Z����
        SimpleMath::Vector3 dir = 
            SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
        // ����Ɏg���������̂ݎc��
        pos1 *= dir;
        pos2 *= dir;
    }

    // �����蔻��
    bool hitX = std::fabsf(pos1.x - pos2.x) < (ext1.x + ext2.x);
    bool hitY = std::fabsf(pos1.y - pos2.y) < (ext1.y + ext2.y);
    bool hitZ = std::fabsf(pos1.z - pos2.z) < (ext1.z + ext2.z);

    return hitX && hitY && hitZ;
}

//------------------------------------------------------------------
/**
 * @brief AABB�̓����������������߂�
 *
 * @param �@is2D           �F2D���ǂ���
 * @param �@cameraDirection�F�J�����̌���
 * @param �@box1           �F����Ɏg�p���锠�P
 * @param �@box2           �F����Ɏg�p���锠�Q
 * @return  HitDirection   �Fbox1���猩��box2�̕���
 */
Collision::HitDirection Collision::GetHitDirection(
    bool is2D, 
    const DirectX::SimpleMath::Vector3& cameraDirection,
    BoxCollider box1,
    BoxCollider box2)
{
    // ����Ɏg�p���钸�_
    SimpleMath::Vector3 min1, min2, max1, max2;
    // ���_�擾
    box1.GetCorners(min1, max1);
    box2.GetCorners(min2, max2);
    // �������������擾�p
    int checkDir = Collision::HitDirection::None;
    // �߂荞�݋�m�F�p�ϐ�
    DirectX::SimpleMath::Vector3 checkRatio;
    // ������������̑傫�����v�Z
    DirectX::SimpleMath::Vector3 boxSize = box2.GetExtents() * 2.0f;

    // �e�����̂߂荞�݋
    float rightRaito = (max1.x - min2.x) / boxSize.x;
    float leftRaito  = (max2.x - min1.x) / boxSize.x;
    float upRaito    = (max1.y - min2.y) / boxSize.y;
    float downRaito  = (max2.y - min1.y) / boxSize.y;
    float backRaito  = (max1.z - min2.z) / boxSize.z;
    float frontRaito = (max2.z - min1.z) / boxSize.z;

    // ���E�̔䗦���珬�����ق����L������
    if (leftRaito < rightRaito)
    {
        checkDir |= Collision::HitDirection::Left;
        checkRatio.x = leftRaito;
    }
    else
    {
        checkDir |= Collision::HitDirection::Right;
        checkRatio.x = rightRaito;
    }
    // �㉺�̔䗦���珬�����ق����L������
    if (upRaito < downRaito)
    {
        checkDir |= Collision::HitDirection::Top;
        checkRatio.y = upRaito;
    }
    else
    {
        checkDir |= Collision::HitDirection::Bottom;
        checkRatio.y = downRaito;
    }

    // ��O�Ɖ��̔䗦���珬�����ق����L������
    if (frontRaito < backRaito)
    {
        checkDir |= Collision::HitDirection::Front;
        checkRatio.z = frontRaito;
    }
    else
    {
        checkDir |= Collision::HitDirection::Back;
        checkRatio.z = backRaito;
    }

    // �䗦�������������c��
    int ret = Collision::HitDirection::None;

    // 2D
    if (is2D)
    {
        // ����Ɏg���������v�Z����
        SimpleMath::Vector3 dir =
            SimpleMath::Vector3::One -
            KT::MyUtility::AbsVector(cameraDirection);

        // ���_�����ɂ���Ĕ����؂�ւ���

        // X������
       if(dir.x < std::numeric_limits<float>::epsilon()) 
       {
           if (checkRatio.y < checkRatio.z)
           {
               ret = checkDir & (Collision::HitDirection::Top | Collision::HitDirection::Bottom);
           }
           else if (checkRatio.y > checkRatio.z)
           {
               ret = checkDir & (Collision::HitDirection::Front | Collision::HitDirection::Back);
           }
       }
       // Y������
       else if (dir.y < std::numeric_limits<float>::epsilon())
       {
           if (checkRatio.x < checkRatio.z)
           {
               ret = checkDir & (Collision::HitDirection::Left | Collision::HitDirection::Right);
           }
           else if (checkRatio.x > checkRatio.z)
           {
               ret = checkDir & (Collision::HitDirection::Front | Collision::HitDirection::Back);
           }
       }
       // Z������
       else if (dir.z < std::numeric_limits<float>::epsilon())
       {
           if (checkRatio.y < checkRatio.x)
           {
               ret = checkDir & (Collision::HitDirection::Top | Collision::HitDirection::Bottom);
           }
           else if (checkRatio.y > checkRatio.x)
           {
               ret = checkDir & (Collision::HitDirection::Left | Collision::HitDirection::Right);
           }
       }
    }
    // 3D
    else
    {
        // X������
        if ((checkRatio.x < checkRatio.y) && (checkRatio.x < checkRatio.z))
        {
            ret = checkDir & (Collision::HitDirection::Left | Collision::HitDirection::Right);
        }
        // Y������
        else if ((checkRatio.y < checkRatio.x) && (checkRatio.y < checkRatio.z))
        {
            ret = checkDir & (Collision::HitDirection::Top | Collision::HitDirection::Bottom);
        }
        // Z������
        else if ((checkRatio.z < checkRatio.x) && (checkRatio.z < checkRatio.y))
        {
            ret = checkDir & (Collision::HitDirection::Front | Collision::HitDirection::Back);
        }
    }

    return static_cast<Collision::HitDirection>(ret);
}