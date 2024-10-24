#include "pch.h"

#include "weaponclub.h"

#include <vendor/rapidjson/document.h>
#include <vendor/rapidjson/filereadstream.h>


namespace feature {
    namespace weapon::weaponclub {



        std::vector<weaponSpawnList> g_weaponList;
        std::vector<weaponSpawnList_comp> g_weaponListComp;
        
        bool loadWeaponWithInfo = true;
        
        void LoadWeaponWithInfo()// so far ok we peformace 
        {
            LOG << "Loading Weapons Info";
            if (loadWeaponWithInfo)
            {
                FILE* fp = fopen("Avi\\Data\\weapons.json", "r");
                char readBuffer[65536];
                rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

                rapidjson::Document doc;
                doc.ParseStream(is);
                fclose(fp);

                if (!doc.HasMember("weapons_cache")) {
                    LOG_TAG("WARN") << "JSON does not have weapons_cache!";
                    return;
                }

                const auto& weaponsCache = doc["weapons_cache"];

                if (weaponsCache.HasMember("weapon_map")) {
                    const auto& weaponMap = weaponsCache["weapon_map"];
                    for (auto it = weaponMap.MemberBegin(); it != weaponMap.MemberEnd(); ++it) {
                        const auto& weapon = it->value;
                        std::string weaponName = it->name.GetString();
                        std::string displayName = weapon["m_display_name"].GetString();

                        weaponSpawnList weaponData;
                        WeaponHudStatsData data;

                        weaponData.hashstring = weaponName;
                        weaponData.displayName = HUD::_GET_LABEL_TEXT(displayName.c_str());
                        if (WEAPON::GET_WEAPON_HUD_STATS(rage::joaat(weaponName), (Any*)&data))
                        {
                            weaponData.damage = data.hudDamage;
                            weaponData.speed = data.hudSpeed;
                            weaponData.capacity = data.hudCapacity;
                            weaponData.accuracy = data.hudAccuracy;
                            weaponData.hudrange = data.hudRange;
                        }
                        
                        weaponData.classIndex = 9;// Other

                        Hash Group = WEAPON::GET_WEAPONTYPE_GROUP(rage::joaat(weaponName));
                        for (int i = 0; i < 9; i++)
                        {
                            if (rage::joaat(WeaponGroupsHash[i]) == Group)
                            {
                                weaponData.classIndex = i;
                            }
                        }

                        //LOG << "Loaded weapon: " << weaponData.hashstring << " | (" << weaponData.displayName << ")" << " | Group " << weaponData.classIndex;

                        if (weapon.HasMember("m_attachments")) {
                            const auto& attachments = weapon["m_attachments"];
                            if (attachments.Size() > 0) {
                                //LOG << "Weapon " << weaponName << " has the following components:";
                            }
                            for (rapidjson::SizeType i = 0; i < attachments.Size(); ++i) {
                                std::string componentName = attachments[i].GetString();
                                weaponData.components.push_back(componentName);

                                // Log each component assigned to this weapon
                                //LOG << " - Component: " << componentName;
                            }
                        }

                        g_weaponList.push_back(weaponData);
                    }
                }

                if (weaponsCache.HasMember("weapon_components")) {
                    const auto& components = weaponsCache["weapon_components"];
                    for (auto it = components.MemberBegin(); it != components.MemberEnd(); ++it) {
                        const auto& component = it->value;
                        std::string componentName = it->name.GetString();
                        std::string displayDesc = component["m_display_desc"].GetString();
                        std::string displayName = component["m_display_name"].GetString();
                        std::string name = component["m_name"].GetString();

                        weaponSpawnList_comp componentData;
                        componentData.hashstring = componentName;
                        componentData.displayDesc = HUD::_GET_LABEL_TEXT(displayDesc.c_str());
                        componentData.displayName = HUD::_GET_LABEL_TEXT(displayName.c_str());
                        componentData.name = name;

                        g_weaponListComp.push_back(componentData);

   /*                     LOG << "Loaded component: " << componentName
                            << " | Display Desc: " << componentData.displayDesc
                            << " | Display Name: " << componentData.displayName
                            << " | Name: " << name;*/
                    }
                }
                LOG << "Weapon and component information loaded successfully.";
                loadWeaponWithInfo = false;
            }
        }


    }
}





