#include "pch.h"

namespace feature {
    namespace g_player {


        Player GetPlayerID() {
            return PLAYER::PLAYER_ID();
        }

        Ped GetPlayerPed() {
            return PLAYER::PLAYER_PED_ID();
        }

        Player GetPlayerPed(int player) {
            return PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
        }

        Player GetPlayerScriptIndex() {
            return PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
        }

        Vehicle GetPlayerVehicle() {
            return PED::GET_VEHICLE_PED_IS_IN(GetPlayerPed(), false);
        }

        Vehicle GetPlayerVehicle(int player) {
            return PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
        }

        Vector3 GetPlayerCoords() {
            return ENTITY::GET_ENTITY_COORDS(GetPlayerPed(), true);
        }
        Vector3 GetGamePlayCamRotation() {
            return CAM::GET_GAMEPLAY_CAM_ROT(0);
        }

        float GetPlayerHealth() {
            return ENTITY::GET_ENTITY_HEALTH(GetPlayerPed());
        }

        float GetPlayerMaxHealth() {
            return ENTITY::GET_ENTITY_MAX_HEALTH(GetPlayerPed());
        }

        float GetPlayerArmour() {
            return PED::GET_PED_ARMOUR(GetPlayerPed());
        }

        bool IsPlayerInVehicle() {
            return PED::IS_PED_IN_ANY_VEHICLE(GetPlayerPed(), false);
        }

        bool IsPlayerOnFoot() {
            return PED::IS_PED_ON_FOOT(GetPlayerPed());
        }

        bool IsPlayerInCombat() {
            return PED::IS_PED_IN_COMBAT(GetPlayerPed(), 0);
        }

        bool IsPedInjured(Ped ped) {
            return PED::IS_PED_INJURED(ped);
        }

        bool IsPedHurt(Ped ped) {
            return PED::IS_PED_HURT(ped);
        }

        bool IsPedFatallyInjured(Ped ped) {
            return PED::IS_PED_FATALLY_INJURED(ped);
        }

        bool IsPedDeadOrDying(Ped ped) {
            return PED::IS_PED_DEAD_OR_DYING(ped, NULL);
        }

        bool IsPedAimingFromCover(Ped ped) {
            return PED::IS_PED_AIMING_FROM_COVER(ped);
        }

        bool IsPedReloading(Ped ped) {
            return PED::IS_PED_RELOADING(ped);
        }

        bool IsPedAPlayer(Ped ped) {
            return PED::IS_PED_A_PLAYER(ped);
        }
        float GetPlayerDir()
        {
            return ENTITY::GET_ENTITY_HEADING(GetPlayerPed());
        }

        Vector3 GetCoordsInFrontOfPlayer(Ped playerPed, float distance)
        {
            Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
            float xOffset = distance * sin(app::math::DegreeToRadian(GetPlayerDir())) * -1.f;
            float yOffset = distance * cos(app::math::DegreeToRadian(GetPlayerDir()));
            return { (playerCoords.x + xOffset), (playerCoords.y + yOffset), playerCoords.z };
        }

        void SeatPlayerInVehicle(Ped playerPed, Vehicle vehicle)
        {
            if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
                return;

            int maxSeats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle);
            for (int seatIndex = -1; seatIndex <= maxSeats; ++seatIndex)
            {
                if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, seatIndex, false))
                {
                    PED::SET_PED_INTO_VEHICLE(playerPed, vehicle, seatIndex);
                    return;
                }
            }

        }

    }
}