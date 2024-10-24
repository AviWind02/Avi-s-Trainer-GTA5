#include "pch.h"
#include "localfeatures.h"

namespace app {
    namespace feature::local::playerhealth {

        using namespace g_feature;

        float healthRechargeRateSpeed;
        bool tickHealthRechargeRate;
        
        bool tickCleanPlayer;
        
        bool tickInvincibility;
        bool wasInvincible;
        
        bool tickKillPlayer;
        
        bool tickrefillhealth;
        bool tickrefillarmor;

        void SetPlayerHealth(int health) {
            ENTITY::SET_ENTITY_HEALTH(g_player::GetPlayerPed(), health, NULL);
        }

        void SetPlayerArmor(int armor) {
            PED::SET_PED_ARMOUR(g_player::GetPlayerPed(), armor);
        }

        void SetHealthRechargeRate(float rate) {
            PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(g_player::GetPlayerPed(), rate);
        }

        void SetInvincibility(bool enabled) {
            ENTITY::SET_ENTITY_INVINCIBLE(g_player::GetPlayerPed(), enabled);
        }

        void ClearPlayerDamage() {
            PED::CLEAR_PED_WETNESS(g_player::GetPlayerPed());
            PED::CLEAR_PED_BLOOD_DAMAGE(g_player::GetPlayerPed());
            PED::RESET_PED_VISIBLE_DAMAGE(g_player::GetPlayerPed());
        }


        void RefillHealth() {
            SetPlayerHealth(200);
        }

        void RefillArmor() {
            SetPlayerArmor(500);
        }

        void Tick() {
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
