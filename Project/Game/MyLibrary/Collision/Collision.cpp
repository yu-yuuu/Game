/**
 *
 * @file Collision.cpp
 *
 * @brief 当たり判定処理を行うクラスのソースファイル
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
 * @brief AABB判定
 *
 * @param 　is2D           ：2Dかどうか
 * @param 　cameraDirection：カメラの向き
 * @param 　box1           ：判定に使用する箱１
 * @param 　box2           ：判定に使用する箱２
 * @return  true           ：当たっている
 * @return  false          ：当たっていない
 */
bool Collision::AABBCheck(
    bool is2D, 
    const DirectX::SimpleMath::Vector3& cameraDirection, 
    const BoxCollider& box1,
    const BoxCollider& box2)
{
    // 位置、長さ取得
    SimpleMath::Vector3 pos1 = box1.GetPosition();
    SimpleMath::Vector3 pos2 = box2.GetPosition();
    SimpleMath::Vector3 ext1 = box1.GetExtents();
    SimpleMath::Vector3 ext2 = box2.GetExtents();

    // 2Dか
    if (is2D)
    {
        // 判定に使う方向を計算する
        SimpleMath::Vector3 dir = 
            SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
        // 判定に使う方向をのみ残す
        pos1 *= dir;
        pos2 *= dir;
    }

    // 当たり判定
    bool hitX = std::fabsf(pos1.x - pos2.x) < (ext1.x + ext2.x);
    bool hitY = std::fabsf(pos1.y - pos2.y) < (ext1.y + ext2.y);
    bool hitZ = std::fabsf(pos1.z - pos2.z) < (ext1.z + ext2.z);

    return hitX && hitY && hitZ;
}

//------------------------------------------------------------------
/**
 * @brief AABBの当たった方向を求める
 *
 * @param 　is2D           ：2Dかどうか
 * @param 　cameraDirection：カメラの向き
 * @param 　box1           ：判定に使用する箱１
 * @param 　box2           ：判定に使用する箱２
 * @return  HitDirection   ：box1から見たbox2の方向
 */
Collision::HitDirection Collision::GetHitDirection(
    bool is2D, 
    const DirectX::SimpleMath::Vector3& cameraDirection,
    BoxCollider box1,
    BoxCollider box2)
{
    // 判定に使用する頂点
    SimpleMath::Vector3 min1, min2, max1, max2;
    // 頂点取得
    box1.GetCorners(min1, max1);
    box2.GetCorners(min2, max2);
    // 当たった方向取得用
    int checkDir = Collision::HitDirection::None;
    // めり込み具合確認用変数
    DirectX::SimpleMath::Vector3 checkRatio;
    // 当たった相手の大きさを計算
    DirectX::SimpleMath::Vector3 boxSize = box2.GetExtents() * 2.0f;

    // 各方向のめり込み具合
    float rightRaito = (max1.x - min2.x) / boxSize.x;
    float leftRaito  = (max2.x - min1.x) / boxSize.x;
    float upRaito    = (max1.y - min2.y) / boxSize.y;
    float downRaito  = (max2.y - min1.y) / boxSize.y;
    float backRaito  = (max1.z - min2.z) / boxSize.z;
    float frontRaito = (max2.z - min1.z) / boxSize.z;

    // 左右の比率から小さいほうを記憶する
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
    // 上下の比率から小さいほうを記憶する
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

    // 手前と奥の比率から小さいほうを記憶する
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

    // 比率が小さい方を残す
    int ret = Collision::HitDirection::None;

    // 2D
    if (is2D)
    {
        // 判定に使う方向を計算する
        SimpleMath::Vector3 dir =
            SimpleMath::Vector3::One -
            KT::MyUtility::AbsVector(cameraDirection);

        // 視点方向によって判定を切り替える

        // X軸方向
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
       // Y軸方向
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
       // Z軸方向
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
        // X軸方向
        if ((checkRatio.x < checkRatio.y) && (checkRatio.x < checkRatio.z))
        {
            ret = checkDir & (Collision::HitDirection::Left | Collision::HitDirection::Right);
        }
        // Y軸方向
        else if ((checkRatio.y < checkRatio.x) && (checkRatio.y < checkRatio.z))
        {
            ret = checkDir & (Collision::HitDirection::Top | Collision::HitDirection::Bottom);
        }
        // Z軸方向
        else if ((checkRatio.z < checkRatio.x) && (checkRatio.z < checkRatio.y))
        {
            ret = checkDir & (Collision::HitDirection::Front | Collision::HitDirection::Back);
        }
    }

    return static_cast<Collision::HitDirection>(ret);
}