#include "pch.h"
#include "app/feature/weapons/weaponclub/weaponclub.h"

using namespace GUI;

/*
	extern std::vector<weaponSpawnList> g_weaponList;
	extern std::vector<weaponSpawnList_comp> g_weaponListComp;
	inline const std::string WeaponGroups[10]

	WeaponClubGroups_page,
	WeaponClubGun_page,
	WeaponClub_Picked_Gun_page,

*/
namespace view {
	namespace weaponclub {
		
		static std::string selectedWeaponhash;
		static int selectedWeaponClass;
		static std::string selectedWeaponName;

		void WeaponClubListClassView()
		{
			GUI::menu::SetSubTitle("Weapon Groups");
			feature::weapon::weaponclub::weaponsdataonoption::showDisplay = false;
			if (buttons::Sub("All-Weapons", pages::WeaponClub_Picked_Group_page))
				selectedWeaponClass = 22;
			for (int i = 0; i < feature::weapon::weaponclub::WeaponGroups[i].size(); i++)
				if (buttons::Sub(feature::weapon::weaponclub::WeaponGroups[i].c_str(), pages::WeaponClub_Picked_Group_page))
					selectedWeaponClass = i;
		}
		
		void WeaponClubListWeaponView()
		{
			GUI::menu::SetSubTitle(feature::weapon::weaponclub::WeaponGroups[selectedWeaponClass].c_str());
			feature::weapon::weaponclub::weaponsdataonoption::showDisplay = true;


			for (auto weapon : feature::weapon::weaponclub::g_weaponList)
			{

				 
				if (weapon.classIndex == selectedWeaponClass)
				{
					if (buttons::Sub((weapon.displayName == "NULL" ? weapon.hashstring : weapon.displayName).c_str(), pages::WeaponClub_Picked_Gun_page))
					{
						selectedWeaponhash = weapon.hashstring;
						selectedWeaponName = "Editing " + weapon.displayName;
					}
				}
				else if (selectedWeaponClass == 22)
				{
					if (buttons::Sub((weapon.displayName == "NULL" ? weapon.hashstring : weapon.displayName).c_str(), pages::WeaponClub_Picked_Gun_page))
					{
						selectedWeaponhash = weapon.hashstring;
						selectedWeaponName = "Editing " + weapon.displayName;
					}
				}

				if (GUI::controls::currentOption == GUI::controls::optionCount)
				{
					feature::weapon::weaponclub::weaponsdataonoption::hashstring = weapon.hashstring;
					feature::weapon::weaponclub::weaponsdataonoption::displayName = weapon.displayName;
				}
			}
		}

		void WeaponClubListWeaponItemView()
		{
			GUI::menu::SetSubTitle(selectedWeaponName.c_str());

			for (auto weapon : feature::weapon::weaponclub::g_weaponList)
			{
				if (weapon.hashstring == selectedWeaponhash)
				{
					//Setting this values for the Display use
					//Need to re do these this is shit code - works for now tho
					feature::weapon::weaponclub::weaponsdataonoption::hashstring = weapon.hashstring;
					feature::weapon::weaponclub::weaponsdataonoption::displayName = weapon.displayName;


					if (buttons::Option(("Equip/Unequip " + weapon.displayName).c_str()))
						feature::g_weapon::ToggleWeapon(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str());
					if (WEAPON::HAS_PED_GOT_WEAPON(feature::g_player::GetPlayerPed(), rage::joaat(weapon.hashstring), NULL))
						menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");

					if (buttons::Option(("Add Ammo for " + weapon.displayName + " (x1000)").c_str()))
						feature::g_weapon::AddAmmoForWeapon(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str(), 1000);
					if (feature::g_weapon::HasMaxAmmo(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str()))
						menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
				

					buttons::Break(NULL, "Components");
					for (auto complist : feature::weapon::weaponclub::g_weaponListComp)
					{
						for (int i = 0; i < weapon.components.size(); i++)
						{
							if (weapon.components[i] == complist.name)
							{
								if (buttons::Option(complist.displayName.c_str()))
									feature::g_weapon::ToggleComponent(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str(), complist.hashstring.c_str());
								if (feature::g_weapon::IsComponentAttached(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str(), complist.hashstring.c_str()))
									menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
							}
						}
					}

					buttons::Break(NULL, "Tints");
					//void ToggleWeaponTint(Ped ped, const char* weaponHashName, int tintIndex);
					//int GetCurrentWeaponTint(Ped ped, const char* weaponHashName);

					for (int i = 0; i < feature::weapon::weaponclub::WeaponTintNames->size(); i++)
					{
						if (buttons::Option(feature::weapon::weaponclub::WeaponTintNames[i].c_str()))
							feature::g_weapon::ToggleWeaponTint(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str(), i);
						if (feature::g_weapon::GetCurrentWeaponTint(feature::g_player::GetPlayerPed(), weapon.hashstring.c_str()) == i)
							menu::SetSpriteOnOption("commonmenu", "shop_gunclub_icon_a");
					}



				}
		
			}
		}

	}
}