#include "pch.h"
#include "localfeatures.h"

namespace app {
    namespace feature::local::playermisc {

        using namespace g_feature;
        
        bool tickIgnorePlayer;
        bool resetIgnorePlayer;

        bool tickNoRagdoll;

        bool tickSeatbelt;

        int alphaValue = 255;
        bool tickInvisible;
        bool tickInvisibleIndex;
        bool tickInvisibleNetwork;
        bool tickInvisibleReset;
        bool tickInvisibleNetworkReset;

        void ToggleIgnorePlayer(bool enabled) {
            tickIgnorePlayer = enabled;
            if (enabled) {
                Ped ped = NULL;  // Placeholder for handling ped
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
            else if (resetIgnorePlayer) {
                PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(g_player::GetPlayerPed(), 1);
                PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(g_player::GetPlayerPed(), 0);
                PLAYER::SET_EVERYONE_IGNORE_PLAYER(g_player::GetPlayerPed(), false);
                PLAYER::SET_POLICE_IGNORE_PLAYER(g_player::GetPlayerPed(), false);
                resetIgnorePlayer = false;
            }
        }

        void ToggleRagdoll(bool enabled) {
            tickNoRagdoll = enabled;
            if (enabled) {
                PED::SET_PED_CAN_RAGDOLL(g_player::GetPlayerPed(), false);
                PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_player::GetPlayerPed(), false);
            }
            else {
                PED::SET_PED_CAN_RAGDOLL(g_player::GetPlayerPed(), true);
                PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_player::GetPlayerPed(), true);
            }
        }

        void ToggleSeatbelt(bool enabled) {
            tickSeatbelt = enabled;
            if (enabled) {
                PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(g_player::GetPlayerPed(), 1);
                PED::SET_PED_CONFIG_FLAG(g_player::GetPlayerPed(), 32, false);
            }
        }

        void SetInvisibility(bool enabled, int alpha, bool networkInvisible) {
            alphaValue = alpha;
            tickInvisible = enabled;
            tickInvisibleNetwork = networkInvisible;

            if (tickInvisibleNetwork) {
                ENTITY::SET_ENTITY_VISIBLE(g_player::GetPlayerPed(), false, 0);
                NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(g_player::GetPlayerPed(), false);
                tickInvisibleNetworkReset = true;
            }
            else if (tickInvisibleNetworkReset) {
                ENTITY::SET_ENTITY_VISIBLE(g_player::GetPlayerPed(), true, 0);
                NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(g_player::GetPlayerPed(), true);
                tickInvisibleNetworkReset = false;
            }

            if (alphaValue != 255) {
                ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), alphaValue, false);
                tickInvisibleReset = true;
            }
            else if (tickInvisible) {
                ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), 0, false);
                tickInvisibleReset = true;
            }
            else if (tickInvisibleReset) {
                ENTITY::SET_ENTITY_ALPHA(g_player::GetPlayerPed(), 255, false);
                tickInvisibleReset = false;
            }
        }

        void Tick() {
            if (tickIgnorePlayer) {
                ToggleIgnorePlayer(true);
            }

            if (tickNoRagdoll) {
                ToggleRagdoll(true);
            }

            if (tickSeatbelt) {
                ToggleSeatbelt(true);
            }

            if (tickInvisible || tickInvisibleNetwork || alphaValue != 255) {
                SetInvisibility(tickInvisible, alphaValue, tickInvisibleNetwork);
            }
        }
    }
}