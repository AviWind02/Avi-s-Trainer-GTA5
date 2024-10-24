#include "pch.h"
#include "weaponfeatures.h"

namespace app {
    namespace feature::weapon {

        using namespace g_feature;
        namespace gravityGun {
            bool tickGravityGun; // If I make a sub menu I can add that later
            bool tickGravityGun_Static;
            bool tickGravityGun_Oscillate;
            bool tickGravityGun_Force;
            bool tickGravityGun_DisableGrav;


            Entity objectToHold = NULL;
            bool isObjectToHoldValid = false;
            bool isHoldingObject = false;
            void Tick()
            {
                if (tickGravityGun_Static || tickGravityGun_Oscillate || tickGravityGun_Force || tickGravityGun_DisableGrav)
                {
                    if (g_weapon::IsPlayerAiming())
                    {
                        Vector3 gameCamCoords = g_entity::GetGameplayCamCoords();
                        Vector3 gameCamRot = g_entity::GetGameplayCamRot();
                        Vector3 playerCoords = g_player::GetPlayerCoords();
                        float distance = math::CalculateDistance(&gameCamCoords, &playerCoords) + 10.f;
                        Vector3 posOfEntityInFrontOfGun = math::Add(gameCamCoords, math::Multiply(math::RotationToDirection(&gameCamRot), distance));

                        if (!isHoldingObject)
                            g_entity::GetObjectPlayerLookingAt(&objectToHold, &isObjectToHoldValid);

                        if (isObjectToHoldValid)
                        {
                            isHoldingObject = true;

                            if (ENTITY::IS_ENTITY_A_PED(objectToHold) &&
                                PED::IS_PED_IN_ANY_VEHICLE(objectToHold, 1))
                            {
                                objectToHold = PED::GET_VEHICLE_PED_IS_IN(objectToHold, 0);
                            }

                            if (!tickGravityGun_Force && !tickGravityGun_DisableGrav)
                            {
                                if (tickGravityGun_Static)
                                    g_entity::SetCoords(objectToHold, posOfEntityInFrontOfGun);

                                if (tickGravityGun_Oscillate)
                                    g_entity::Oscillate(objectToHold, posOfEntityInFrontOfGun, 0.5f, 0.3f);
                            }
                            if (g_weapon::IsPlayerShooting())
                            {
                                if (tickGravityGun_DisableGrav)
                                {
                                    g_entity::ApplyForce(objectToHold, { 0, 0, 1.5f }, 1);
                                    g_entity::SetGravity(objectToHold, 0.f);
                                }
                                else
                                    g_entity::ApplyForceForwardCam(objectToHold, 1000.f);

                                isObjectToHoldValid = false;
                                objectToHold = NULL;
                            }
                        }
                    }
                    else
                    {
                        isHoldingObject = false;
                    }
                }
            }
        }


 
    }
}
