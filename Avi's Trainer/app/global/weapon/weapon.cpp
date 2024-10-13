#include "pch.h"
#include "app/feature/weapons/weaponclub/weaponclub.h"

namespace g_feature {
    namespace g_weapon {

        using namespace app;

        bool IsWeaponInGroup(int group, const char* weaponName) {
            Hash weaponGroup = WEAPON::GET_WEAPONTYPE_GROUP(rage::joaat(weaponName));
            return weaponGroup == rage::joaat(feature::weapon::weaponclub::WeaponGroupsHash[group]);
        }

        bool IsComponentForWeapon(const std::string& componentName, const std::string& weaponName) {
            return WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(rage::joaat(weaponName), rage::joaat(componentName));
        }

        bool IsPlayerShooting(Ped ped) {
            Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, true);
            return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
        }

        void ShootBullet(const std::string& hashBullet, int speed, int damage, bool audible, bool showBullet) {
            Entity weaponInHand = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
            Vector3 camCoord = CAM::GET_GAMEPLAY_CAM_COORD();
            Vector3 weaponCoord = ENTITY::GET_ENTITY_COORDS(weaponInHand, true);
            Vector3 playerCoord = g_player::GetPlayerCoords();

            float startDistance = math::CalculateDistance(&camCoord, &weaponCoord) + 0.25f;
            float endDistance = math::CalculateDistance(&camCoord, &playerCoord) + 1000.0f;

            if (PED::IS_PED_ON_FOOT(g_player::GetPlayerPed()) && IsPlayerShooting(g_player::GetPlayerPed())) {
                Hash weaponAsset = rage::joaat(hashBullet);

                do {
                    WEAPON::REQUEST_WEAPON_ASSET(weaponAsset, 31, false);
                    WAIT(0);
                } while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAsset));

                Vector3 camRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
                Vector3 direction = math::RotationToDirection(&camRot);

                Vector3 startCoords = math::Add(camCoord, math::Multiply(direction, startDistance));
                Vector3 endCoords = math::Add(camCoord, math::Multiply(direction, endDistance));

                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
                    startCoords.x, startCoords.y, startCoords.z,
                    endCoords.x, endCoords.y, endCoords.z,
                    damage, true, weaponAsset, PLAYER::PLAYER_PED_ID(), audible, !showBullet, speed
                );

                WEAPON::REMOVE_WEAPON_ASSET(weaponAsset);
            }
        }

        void GiveWeapon(Ped ped, const char* weaponHashName, bool inHand) {
            if (!WEAPON::HAS_PED_GOT_WEAPON(ped, rage::joaat(weaponHashName), false)) {
                WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat(weaponHashName), 25, false, inHand);
            }
        }

        void TakeWeapon(Ped ped, const char* weaponHashName) {
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, rage::joaat(weaponHashName), false)) {
                WEAPON::REMOVE_WEAPON_FROM_PED(ped, rage::joaat(weaponHashName));
            }
        }

        bool ToggleWeapon(Ped ped, const char* weaponHashName) {
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, rage::joaat(weaponHashName), false)) {
                TakeWeapon(ped, weaponHashName);
                return false;
            }
            else {
                GiveWeapon(ped, weaponHashName, true);
                return true;
            }
        }

        Vector3 GetWeaponCoordsInHand() {
            Entity weaponInHand = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
            return ENTITY::GET_ENTITY_COORDS(weaponInHand, true);
        }

        Hash GetCurrentWeaponInHand(Ped ped) {
            Hash currentWeapon;
            WEAPON::GET_CURRENT_PED_WEAPON(ped, &currentWeapon, true);
            return currentWeapon;
        }

        int GetAmmoCountInHand(Ped ped) {
            Hash currentWeapon = GetCurrentWeaponInHand(ped);
            return WEAPON::GET_AMMO_IN_PED_WEAPON(ped, currentWeapon);
        }

        void SetInfiniteAmmo(Ped ped, bool enable) {
            Hash currentWeapon = GetCurrentWeaponInHand(ped);
            WEAPON::SET_PED_INFINITE_AMMO(ped, enable, currentWeapon);
        }

        bool IsPlayerAiming(Ped ped) {
            return PLAYER::IS_PLAYER_FREE_AIMING(g_player::GetPlayerPed());
        }

        void AddAmmoForWeapon(Ped ped, const char* weaponHashName, int ammoAmount) {
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, rage::joaat(weaponHashName), false)) {
                WEAPON::ADD_AMMO_TO_PED(ped, rage::joaat(weaponHashName), ammoAmount);
            }
        }

        bool HasMaxAmmo(Ped ped, const char* weaponHashName) {
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, rage::joaat(weaponHashName), false)) {
                int currentAmmo = WEAPON::GET_AMMO_IN_PED_WEAPON(ped, rage::joaat(weaponHashName));
                int maxAmmo;

                if (WEAPON::GET_MAX_AMMO(ped, rage::joaat(weaponHashName), &maxAmmo)) {
                    return currentAmmo >= maxAmmo;
                }
            }
            return false;
        }

        void EquipWeapon(Ped ped, const char* weaponHashName) {
            Hash weaponHash = rage::joaat(weaponHashName);
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                WEAPON::SET_CURRENT_PED_WEAPON(ped, weaponHash, true);
            }
        }

        bool IsComponentAttached(Ped ped, const char* weaponHashName, const char* componentHashName) {
            Hash weaponHash = rage::joaat(weaponHashName);
            Hash componentHash = rage::joaat(componentHashName);

            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                return WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(ped, weaponHash, componentHash);
            }
            return false;
        }

        void AttachComponent(Ped ped, const char* weaponHashName, const char* componentHashName) {
            Hash weaponHash = rage::joaat(weaponHashName);
            Hash componentHash = rage::joaat(componentHashName);

            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                if (!IsComponentAttached(ped, weaponHashName, componentHashName)) {
                    WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, componentHash);
                }
            }
        }

        void RemoveComponent(Ped ped, const char* weaponHashName, const char* componentHashName) {
            Hash weaponHash = rage::joaat(weaponHashName);
            Hash componentHash = rage::joaat(componentHashName);

            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                if (IsComponentAttached(ped, weaponHashName, componentHashName)) {
                    WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weaponHash, componentHash);
                }
            }
        }

        bool ToggleComponent(Ped ped, const char* weaponHashName, const char* componentHashName) {
            if (IsComponentAttached(ped, weaponHashName, componentHashName)) {
                RemoveComponent(ped, weaponHashName, componentHashName);
                return false;
            }
            else {
                AttachComponent(ped, weaponHashName, componentHashName);
                return true;
            }
        }


        void ApplyTintToWeapon(Ped ped, const char* weaponHashName, int tintIndex) {
            Hash weaponHash = rage::joaat(weaponHashName);
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, weaponHash, tintIndex);
            }
        }

        int GetCurrentWeaponTint(Ped ped, const char* weaponHashName) {
            Hash weaponHash = rage::joaat(weaponHashName);
            if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, false)) {
                return WEAPON::GET_PED_WEAPON_TINT_INDEX(ped, weaponHash);
            }
            return -1;
        }

        void RemoveTintFromWeapon(Ped ped, const char* weaponHashName) {
            ApplyTintToWeapon(ped, weaponHashName, 0);
        }

        void ToggleWeaponTint(Ped ped, const char* weaponHashName, int tintIndex) {
            int currentTint = GetCurrentWeaponTint(ped, weaponHashName);
            if (currentTint != tintIndex) {
                ApplyTintToWeapon(ped, weaponHashName, tintIndex);
            }
            else {
                RemoveTintFromWeapon(ped, weaponHashName);
            }
        }


    }
}
