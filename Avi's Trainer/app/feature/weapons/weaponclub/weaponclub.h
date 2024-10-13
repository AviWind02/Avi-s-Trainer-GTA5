#pragma once
namespace feature {
    namespace weapon::weaponclub {


        namespace weaponsdataonoption {
            inline bool showDisplay = false;
            inline std::string displayName = "NULL";
            inline std::string hashstring = "NULL";
        }

        struct weaponSpawnList {
            std::string hashstring; 
            std::string displayName;
            std::vector<std::string> components;
            float damage;
            float speed;
            float capacity;
            float accuracy;
            float hudrange;
            std::string className;
            int classIndex;
            int arrayIndex;
        };

        struct weaponSpawnList_comp {
            std::string hashstring; 
            std::string displayDesc;
            std::string displayName;
            std::string name;
        };

        struct WeaponHudStatsData
        {
            alignas(8) uint8_t hudDamage;
            alignas(8) uint8_t hudSpeed;
            alignas(8) uint8_t hudCapacity;
            alignas(8) uint8_t hudAccuracy;
            alignas(8) uint8_t hudRange;
        };

        extern std::vector<weaponSpawnList> g_weaponList;
        extern std::vector<weaponSpawnList_comp> g_weaponListComp;

  

        inline const std::string WeaponGroupsHash[9] =
        {
            "GROUP_MELEE",
            "GROUP_PISTOL",
            "GROUP_RIFLE",
            "GROUP_MG",
            "GROUP_SHOTGUN",
            "GROUP_SNIPER",
            "GROUP_HEAVY",
            "GROUP_THROWN",
            "GROUP_SMG"
        };

 

        inline const std::string WeaponTintNames[8] =
        {
            "Normal",
            "Green",
            "Gold",
            "Pink",
            "Army",
            "LSPD",
            "Orange",
            "Platinum"
        };


        void LoadWeaponWithInfo();
    }
}