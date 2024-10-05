#include "pch.h"
#include "localfeatures.hpp"

namespace app {
    namespace feature::local {

        using namespace g_feature;

        PlayerHealth::PlayerHealth()
            : healthRechargeRateSpeed(2.5f),
            tickHealthRechargeRate(false),
            tickCleanPlayer(false),
            tickInvincibility(false),
            wasInvincible(false),
            tickKillPlayer(false),
            tickrefillhealth(false),
            tickrefillarmor(false) {}

        void PlayerHealth::SetPlayerHealth(int health) {
            ENTITY::SET_ENTITY_HEALTH(g_player::GetPlayerPed(), health, NULL);
        }

        void PlayerHealth::SetPlayerArmor(int armor) {
            PED::SET_PED_ARMOUR(g_player::GetPlayerPed(), armor);
        }

        void PlayerHealth::SetHealthRechargeRate(float rate) {
            PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(g_player::GetPlayerPed(), rate);
        }

        void PlayerHealth::SetInvincibility(bool enabled) {
            ENTITY::SET_ENTITY_INVINCIBLE(g_player::GetPlayerPed(), enabled);
        }

        void PlayerHealth::ClearPlayerDamage() {
            PED::CLEAR_PED_WETNESS(g_player::GetPlayerPed());
            PED::CLEAR_PED_BLOOD_DAMAGE(g_player::GetPlayerPed());
            PED::RESET_PED_VISIBLE_DAMAGE(g_player::GetPlayerPed());
        }


        void PlayerHealth::RefillHealth() {
            SetPlayerHealth(200);
        }

        void PlayerHealth::RefillArmor() {
            SetPlayerArmor(500);
        }

        void PlayerHealth::Tick() {
            if (tickrefillhealth){
                RefillHealth();
            }

            if (tickrefillarmor){
                RefillArmor();
            }

            if (tickHealthRechargeRate) {
                SetHealthRechargeRate(healthRechargeRateSpeed);
            }

            if (tickCleanPlayer) {
                ClearPlayerDamage();
            }

            if (tickInvincibility) {
                if (!wasInvincible) {
                    SetInvincibility(true);
                    wasInvincible = true;
                }
            }
            else {
                if (wasInvincible) {
                    SetInvincibility(false);
                    wasInvincible = false;
                }
            }

            if (tickKillPlayer) {
                SetPlayerHealth(0);
            }
        }


    }
}
