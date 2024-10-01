#pragma once
namespace feature {
    namespace g_player {

        Player GetPlayerID();
        Ped GetPlayerPed();

        Player GetPlayerPed(int player);
        Player GetPlayerScriptIndex();

        Vehicle GetPlayerVehicle();
        Vehicle GetPlayerVehicle(int player);

        Vector3 GetPlayerCoords();
        Vector3 GetGamePlayCamRotation();
        float GetPlayerHealth();
        float GetPlayerMaxHealth();
        float GetPlayerArmour();

        bool IsPlayerInVehicle();
        bool IsPlayerOnFoot();
        bool IsPlayerInCombat();
        bool IsPedInjured(Ped ped);
        bool IsPedHurt(Ped ped);
        bool IsPedFatallyInjured(Ped ped);
        bool IsPedDeadOrDying(Ped ped);
        bool IsPedAimingFromCover(Ped ped);
        bool IsPedReloading(Ped ped);
        bool IsPedAPlayer(Ped ped);

    }
}

