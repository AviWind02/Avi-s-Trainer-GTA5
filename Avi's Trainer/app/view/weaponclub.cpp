#include "pch.h"
#include "app/feature/weapons/weaponclub/weaponclub.h"

using namespace GUI;
using namespace g_feature;

namespace view {
    namespace weaponclub {

        static std::string selectedWeaponhash;
        static int selectedWeaponClass;
        static std::string selectedWeaponName;

        void SelectWeapon(const feature::weapon::weaponclub::weaponSpawnList& weapon) {
            selectedWeaponhash = weapon.hashstring;
            selectedWeaponName = "Editing " + weapon.displayName;
        }

        void DisplayWeaponDetails(const feature::weapon::weaponclub::weaponSpawnList& weapon) {
            feature::weapon::weaponclub::weaponsdataonoption::hashstring = weapon.hashstring;
            feature::weapon::weaponclub::weaponsdataonoption::displayName = weapon.displayName;
            feature::weapon::weaponclub::weaponsdataonoption::showDisplay = true;
        }

        void WeaponClubListClassView() {
            GUI::menu::SetSubTitle("Weapon Groups");
            feature::weapon::weaponclub::weaponsdataonoption::showDisplay = false;

            if (buttons::Sub("All-Weapons", pages::WeaponClub_Picked_Group_page)) {
                selectedWeaponClass = 22;
            }

            for (size_t i = 0; i < feature::weapon::weaponclub::WeaponGroups->size(); ++i) {
                if (buttons::Sub(feature::weapon::weaponclub::WeaponGroups[i].c_str(), pages::WeaponClub_Picked_Group_page, [i]() {selectedWeaponClass = i; }));
            }
        }

        void WeaponClubListWeaponView() {
            GUI::menu::SetSubTitle(feature::weapon::weaponclub::WeaponGroups[selectedWeaponClass].c_str());

            for (const auto& weapon : feature::weapon::weaponclub::g_weaponList) {
                if (weapon.classIndex == selectedWeaponClass || selectedWeaponClass == 22) {
                    if (buttons::Sub((weapon.displayName == "NULL" ? weapon.hashstring : weapon.displayName).c_str(), pages::WeaponClub_Picked_Gun_page, [weapon]() {SelectWeapon(weapon); }));

                    if (GUI::controls::currentOption == GUI::controls::optionCount) {
                        DisplayWeaponDetails(weapon);
                    }
                }
            }
        }

        // View to manage selected weapon and its components
        void WeaponClubListWeaponItemView() {
            GUI::menu::SetSubTitle(selectedWeaponName.c_str());

            for (const auto& weapon : feature::weapon::weaponclub::g_weaponList) {
                if (weapon.hashstring == selectedWeaponhash) {
                    DisplayWeaponDetails(weapon);  // Set weapon details for display

                    buttons::Option(("Equip/Unequip " + weapon.displayName).c_str(), [&]() {
                        g_weapon::ToggleWeapon(g_player::GetPlayerPed(), weapon.hashstring.c_str());
                    });

                    if (WEAPON::HAS_PED_GOT_WEAPON(g_player::GetPlayerPed(), rage::joaat(weapon.hashstring), NULL)) {
                        menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
                    }

                    buttons::Option(("Add Ammo for " + weapon.displayName + " (x1000)").c_str(), [&]() {
                        g_weapon::AddAmmoForWeapon(g_player::GetPlayerPed(), weapon.hashstring.c_str(), 1000);
                    });

                    if (g_weapon::HasMaxAmmo(g_player::GetPlayerPed(), weapon.hashstring.c_str())) {
                        menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
                    }

                    buttons::Break(NULL, "Components");

                    for (const auto& complist : feature::weapon::weaponclub::g_weaponListComp) {
                        for (const auto& component : weapon.components) {
                            if (component == complist.name) {
                                buttons::Option(complist.displayName.c_str(), [&]() { 
                                    g_weapon::ToggleComponent(g_player::GetPlayerPed(), weapon.hashstring.c_str(), complist.hashstring.c_str());
                                });

                                if (g_weapon::IsComponentAttached(g_player::GetPlayerPed(), weapon.hashstring.c_str(), complist.hashstring.c_str())) {
                                    menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
                                }
                            }
                        }
                    }

                    buttons::Break(NULL, "Tints");

                    for (size_t i = 0; i < feature::weapon::weaponclub::WeaponTintNames->size(); ++i) {
                        buttons::Option(feature::weapon::weaponclub::WeaponTintNames[i].c_str(), [&]() {
                            g_weapon::ToggleWeaponTint(g_player::GetPlayerPed(), weapon.hashstring.c_str(), i);
                        });
        
                        if (g_weapon::GetCurrentWeaponTint(g_player::GetPlayerPed(), weapon.hashstring.c_str()) == i) {
                            menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
                        }
                    }
                }
            }
        }

    }  // namespace weaponclub
}  // namespace view
