#include "pch.h"


namespace feature {
	namespace local {
		
        namespace CleanPlayer {

            float healthRechargeRateSpeed = 2.5f;
            bool tickHealthRechargeRate, tickCleanPlayer, tickCleanPlayerLooped;

            void Tick() {
                if (tickHealthRechargeRate) {
                    PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(g_player::GetPlayerPed(), healthRechargeRateSpeed);
                }
                if (tickCleanPlayer || tickCleanPlayerLooped) {
                    PED::CLEAR_PED_WETNESS(g_player::GetPlayerPed());
                    PED::CLEAR_PED_BLOOD_DAMAGE(g_player::GetPlayerPed());
                    PED::RESET_PED_VISIBLE_DAMAGE(g_player::GetPlayerPed());
                    tickCleanPlayer = false;
                }
            }
        }

        namespace Health {

            bool tickInvincibility, wasInvincible, tickkillPlayer, tickkillPlayerLooped;

            void Tick() {
                if (tickInvincibility) {
                    if (!wasInvincible) {
                        ENTITY::SET_ENTITY_INVINCIBLE(g_player::GetPlayerPed(), true);
                        wasInvincible = true;
                    }
                }
                else {
                    if (wasInvincible) {
                        ENTITY::SET_ENTITY_INVINCIBLE(g_player::GetPlayerPed(), false);
                        wasInvincible = false;
                    }
                }
                if (tickkillPlayer || tickkillPlayerLooped) {
                    ENTITY::SET_ENTITY_HEALTH(g_player::GetPlayerPed(), 0, NULL);
                    tickkillPlayer = false;
                }
            }
        }

        namespace Refill {

            bool tickRefillHealthBar, tickRefillArmourBar, tickRefillHealthBarLooped, tickRefillArmourBarLooped;

            void Tick() {
                if (tickRefillHealthBar || tickRefillHealthBarLooped) {
                    ENTITY::SET_ENTITY_HEALTH(g_player::GetPlayerPed(), 200, NULL);
                    tickRefillHealthBar = false;
                }
                if (tickRefillArmourBar || tickRefillArmourBarLooped) {
                    ENTITY::SET_ENTITY_HEALTH(g_player::GetPlayerPed(), 200, NULL);
                    PED::SET_PED_ARMOUR(g_player::GetPlayerPed(), 500);
                    tickRefillArmourBar = false;
                }
            }
        }

        namespace Ragdoll {

            bool tickNoRagdoll;

            void Tick() {
                static bool resetTickNoRagdoll = false;
                if (tickNoRagdoll) {
                    PED::SET_PED_CAN_RAGDOLL(g_player::GetPlayerPed(), false);
                    PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_player::GetPlayerPed(), false);
                    resetTickNoRagdoll = true;
                }
                else {
                    if (resetTickNoRagdoll) {
                        PED::SET_PED_CAN_RAGDOLL(g_player::GetPlayerPed(), true);
                        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_player::GetPlayerPed(), true);
                        resetTickNoRagdoll = false;
                    }
                }
            }
        }

        namespace Seatbelt {

            bool tickSeatbelt;

            void Tick() {
                if (tickSeatbelt) {
                    PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(g_player::GetPlayerPed(), 1);
                    PED::SET_PED_CONFIG_FLAG(g_player::GetPlayerPed(), 32, false);
                }
            }
        }

        namespace WantedLevel {

            bool neverWantedLevel, alwaysWantedLevel, editWantedLevel, clearWantedLevel, holdWantedLevel;
            int wantedLevelIndex;

            void AdjustLevel(int wantedLevel) {
                PLAYER::SET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID(), wantedLevel, false);
                PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(g_player::GetPlayerID(), NULL);
            }

            void Tick() {
                if (clearWantedLevel) {
                    holdWantedLevel = false;
                    if (PLAYER::IS_PLAYER_WANTED_LEVEL_GREATER(g_player::GetPlayerID(), 0)) {
                        AdjustLevel(0);
                        wantedLevelIndex = 0;
                    }
                    clearWantedLevel = false;
                }

                if (editWantedLevel && !alwaysWantedLevel) {
                    neverWantedLevel = false;
                    AdjustLevel(wantedLevelIndex);
                    editWantedLevel = false;
                }
                else
                    wantedLevelIndex = PLAYER::GET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID());


                if (alwaysWantedLevel) {
                    holdWantedLevel = false;
                    AdjustLevel(5);
                }

                if (neverWantedLevel) {
                    holdWantedLevel = false;
                    alwaysWantedLevel = false;
                    if (PLAYER::IS_PLAYER_WANTED_LEVEL_GREATER(g_player::GetPlayerID(), 0)) {
                        AdjustLevel(0);
                    }
                }

                if (holdWantedLevel) {
                    if (PLAYER::IS_PLAYER_WANTED_LEVEL_GREATER(g_player::GetPlayerID(), 0)) {
                        AdjustLevel(PLAYER::GET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID()));
                        editWantedLevel = false;
                    }
                }
            }
        }

        namespace Noclip {

            bool tickNoclip;
            float noClipSpeed;
            int entityAlpha = 150;

            void Tick() {
                static bool resetNoclip = false;
                if (tickNoclip) {

                    Vector3 playerCoords = g_player::GetPlayerCoords();
                    Vector3 gamePlayCam = g_player::GetGamePlayCamRotation();
                    noClipSpeed = std::distance(&gamePlayCam, &playerCoords);

                    if (GUI::controls::IsMovingForward())
                        GUI::controls::IsLeftShiftPressed() ? noClipSpeed += 2.5f : noClipSpeed += 1.5f;
                    else if (GUI::controls::IsMovingBackward())
                        GUI::controls::IsLeftShiftPressed() ? noClipSpeed -= 2.5f : noClipSpeed -= 1.5f;
                    else if (GUI::controls::IsLeftCtrlPressed())
                        noClipSpeed = NULL;
                    else {//If you not moving set the player back to normal
                        noClipSpeed = NULL;
                        ENTITY::RESET_ENTITY_ALPHA(g_player::GetPlayerPed());
                        ENTITY::SET_ENTITY_COLLISION(g_player::GetPlayerPed(), true, true);
                        return;
                    }



                    Vector3 dirSpeed = app::math::Multiply(app::math::RotationToDirection(&gamePlayCam), noClipSpeed);
                    Vector3 coords = app::math::Add(playerCoords, dirSpeed);
                    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_player::GetPlayerPed(), coords.x, coords.y, coords.z, false, false, false);
                    ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), entityAlpha, false);
                    ENTITY::SET_ENTITY_COLLISION(g_player::GetPlayerPed(), false, false);
                    resetNoclip = true;

                }
                else {
                    if (resetNoclip) {
                        ENTITY::RESET_ENTITY_ALPHA(g_player::GetPlayerPed());
                        ENTITY::SET_ENTITY_COLLISION(g_player::GetPlayerPed(), true, true);
                        resetNoclip = false;
                    }
                }
            }
        }

        namespace Movement {

            bool tickFastRun, tickFastSwim, tickFastRunReset, tickFastSwimReset, tickMaxStamina, tickSuperJump, tickSetMaxStamina;
            float runningIndex = 1.f, swimmingIndex = 1.f;

            void Tick() {
                if (tickSuperJump) {
                    MISC::SET_SUPER_JUMP_THIS_FRAME(g_player::GetPlayerID());
                }

                if (swimmingIndex > 1.f) {
                    PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), swimmingIndex);//Max is 1.5f Need to get ptr
                    tickFastSwimReset = true;
                }
                else {
                    if (tickFastSwimReset) {
                        PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), 1.f);
                        tickFastSwimReset = false;
                    }
                }

                if (runningIndex > 1.f) {
                    PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), runningIndex);
                    tickFastRunReset = true;
                }
                else {
                    if (tickFastRunReset) {
                        PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), 1.f);
                        tickFastRunReset = false;
                    }
                }

                if (tickMaxStamina || tickSetMaxStamina) {
                    PLAYER::RESET_PLAYER_STAMINA(g_player::GetPlayerID());
                    tickSetMaxStamina = false;
                }
            }
        }

        namespace Invisible {

            int alphaValue = 255;
            bool tickInvisible, tickInvisibleIndex, tickInvisibleNetwork, tickInvisibleReset, tickInvisibleNetworkReset;

            void Tick() {
                if (tickInvisibleNetwork) {
                    ENTITY::SET_ENTITY_VISIBLE(g_player::GetPlayerPed(), false, 0);
                    NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(g_player::GetPlayerPed(), false);
                    tickInvisibleNetworkReset = true;
                }
                else {
                    if (tickInvisibleNetworkReset) {
                        ENTITY::SET_ENTITY_VISIBLE(g_player::GetPlayerPed(), true, 0);
                        NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(g_player::GetPlayerPed(), true);
                        tickInvisibleNetworkReset = false;
                    }
                }

                if (alphaValue != 255) {
                    ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), alphaValue, false);
                    tickInvisibleReset = true;
                }
                else if (tickInvisible) {
                    ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), 0, false);
                    tickInvisibleReset = true;
                }
                else {
                    if (tickInvisibleReset) {
                        ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), 255, false);
                        tickInvisibleReset = false;
                    }
                }
            }
        }

        namespace IgnorePlayer {

            bool tickIgnorePlayer, resetIgnorePlayer;

            void Tick() {
                if (tickIgnorePlayer) {
                    Ped ped = NULL; /*gobal::getpeds->nearby()*/
                    PLAYER::SET_POLICE_IGNORE_PLAYER(g_player::GetPlayerPed(), 1);
                    PLAYER::SET_EVERYONE_IGNORE_PLAYER(g_player::GetPlayerPed(), 1);
                    PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(g_player::GetPlayerPed(), 0);
                    PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(g_player::GetPlayerPed(), 1);
                    NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
                    PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
                    PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, 0);
                    PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, 1);
                    resetIgnorePlayer = true;
                }
                else {
                    if (resetIgnorePlayer) {
                        PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(g_player::GetPlayerPed(), 1);
                        PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(g_player::GetPlayerPed(), 0);
                        PLAYER::SET_EVERYONE_IGNORE_PLAYER(g_player::GetPlayerPed(), false);
                        PLAYER::SET_POLICE_IGNORE_PLAYER(g_player::GetPlayerPed(), false);
                        resetIgnorePlayer = false;
                    }
                }
            }
        }

        void LocalThread() {
            srand(GetTickCount64());
            while (true)
            {
                Health::Tick();
                Invisible::Tick();
                WantedLevel::Tick();
                CleanPlayer::Tick();
                Movement::Tick();
                Refill::Tick();
                Ragdoll::Tick();
                Seatbelt::Tick();
                Noclip::Tick();
                IgnorePlayer::Tick();
                WAIT(0);
            }
        }
        
	}//Local
}//Feat