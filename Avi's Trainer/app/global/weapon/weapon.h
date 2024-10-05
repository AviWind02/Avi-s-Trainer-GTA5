#pragma once
namespace g_feature {
	namespace g_weapon {

        bool IsPlayerAiming(Ped ped);
        void SetInfiniteAmmo(Ped ped, bool enable);
        int GetAmmoCountInHand(Ped ped);
        Hash GetCurrentWeaponInHand(Ped ped);
        Vector3 GetWeaponCoordsInHand();
        bool ToggleWeapon(Ped ped, const char* weaponHashName);
        void TakeWeapon(Ped ped, const char* weaponHashName);
        void GiveWeapon(Ped ped, const char* weaponHashName, bool inHand);
        void ShootBullet(const std::string& hashBullet, int speed, int damage, bool audible, bool showBullet);
        bool IsPlayerShooting(Ped ped);
        bool IsComponentForWeapon(const std::string& componentName, const std::string& weaponName);
        bool IsWeaponInGroup(int group, const char* weaponName);
        void AddAmmoForWeapon(Ped ped, const char* weaponHashName, int ammoAmount);
        bool HasMaxAmmo(Ped ped, const char* weaponHashName);
        void EquipWeapon(Ped ped, const char* weaponHashName);
        bool IsComponentAttached(Ped ped, const char* weaponHashName, const char* componentHashName);
        void AttachComponent(Ped ped, const char* weaponHashName, const char* componentHashName);
        void RemoveComponent(Ped ped, const char* weaponHashName, const char* componentHashName);
        bool ToggleComponent(Ped ped, const char* weaponHashName, const char* componentHashName);
        void ToggleWeaponTint(Ped ped, const char* weaponHashName, int tintIndex);
        void RemoveTintFromWeapon(Ped ped, const char* weaponHashName);
        int GetCurrentWeaponTint(Ped ped, const char* weaponHashName);
        void ApplyTintToWeapon(Ped ped, const char* weaponHashName, int tintIndex);
    }
}