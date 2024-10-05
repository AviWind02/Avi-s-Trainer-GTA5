#include "pch.h"
#include "localfeatures.hpp"

namespace app {
    namespace feature::local {

        using namespace g_feature;
 
    

        PlayerMovement::PlayerMovement()
            : tickNoclip(false), noClipSpeed(0.f), entityAlpha(150),
            tickFastRun(false), tickFastSwim(false), tickFastRunReset(false),
            tickFastSwimReset(false), tickMaxStamina(false), tickSuperJump(false),
            runningIndex(1.f), swimmingIndex(1.f) {}

        void PlayerMovement::SetNoclipState(bool enabled) {
            tickNoclip = enabled;
        }

        void PlayerMovement::UpdateNoclipSpeed(float speed) {
            noClipSpeed = speed;
        }

        void PlayerMovement::ResetNoclip() {
            ENTITY::RESET_ENTITY_ALPHA(g_player::GetPlayerPed());
            ENTITY::SET_ENTITY_COLLISION(g_player::GetPlayerPed(), true, true);
            noClipSpeed = 0;
        }

        void PlayerMovement::SetRunSpeed(float speed) {
            runningIndex = speed;
        }

        void PlayerMovement::SetSwimSpeed(float speed) {
            swimmingIndex = speed;
        }

        void PlayerMovement::EnableSuperJump(bool enabled) {
            tickSuperJump = enabled;
        }

        void PlayerMovement::ResetStamina() {
            PLAYER::RESET_PLAYER_STAMINA(g_player::GetPlayerID());
        }

        void PlayerMovement::Tick() {
            static bool resetNoclip = false;
            if (tickNoclip) {
                Vector3 playerCoords = g_player::GetPlayerCoords();
                Vector3 gamePlayCam = g_player::GetGamePlayCamRotation();
                noClipSpeed = std::distance(&gamePlayCam, &playerCoords);

                if (GUI::controls::IsMovingForward()) {
                    noClipSpeed += GUI::controls::IsLeftShiftPressed() ? 2.5f : 1.5f;
                }
                else if (GUI::controls::IsMovingBackward()) {
                    noClipSpeed -= GUI::controls::IsLeftShiftPressed() ? 2.5f : 1.5f;
                }
                else if (GUI::controls::IsLeftCtrlPressed()) {
                    noClipSpeed = 0;
                }
                else {
                    ResetNoclip();
                    return;
                }

                Vector3 dirSpeed = app::math::Multiply(app::math::RotationToDirection(&gamePlayCam), noClipSpeed);
                Vector3 coords = app::math::Add(playerCoords, dirSpeed);
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_player::GetPlayerPed(), coords.x, coords.y, coords.z, false, false, false);
                ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), entityAlpha, false);
                ENTITY::SET_ENTITY_COLLISION(g_player::GetPlayerPed(), false, false);
                resetNoclip = true;

            }
            else if (resetNoclip) {
                ResetNoclip();
                resetNoclip = false;
            }

            if (tickSuperJump) {
                MISC::SET_SUPER_JUMP_THIS_FRAME(g_player::GetPlayerID());
            }

            if (swimmingIndex > 1.f) {
                PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), swimmingIndex);
                tickFastSwimReset = true;
            }
            else if (tickFastSwimReset) {
                PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), 1.f);
                tickFastSwimReset = false;
            }

            if (runningIndex > 1.f) {
                PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), runningIndex);
                tickFastRunReset = true;
            }
            else if (tickFastRunReset) {
                PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player::GetPlayerID(), 1.f);
                tickFastRunReset = false;
            }

            if (tickMaxStamina) {
                ResetStamina();
            }
        }



    }
}