#include "pch.h"
#include "localfeatures.h"

namespace app {
    namespace feature::local::wantedlevel {

        using namespace g_feature;

        int wantedLevelIndex;
        bool holdWantedLevel;
        bool neverWantedLevel;
        bool alwaysWantedLevel;

        void SetWantedLevel(int level) {
            wantedLevelIndex = level;
            PLAYER::SET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID(), wantedLevelIndex, false);
            PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(g_player::GetPlayerID(), false);
        }

        void ClearWantedLevel() {
            SetWantedLevel(0);
        }

        void HoldCurrentLevel() {
            holdWantedLevel = true;
        }

        void EnableNeverWanted() {
            neverWantedLevel = true;
            alwaysWantedLevel = false;
            ClearWantedLevel(); 
        }

        void EnableAlwaysWanted() {
            alwaysWantedLevel = true;
            neverWantedLevel = false;
            SetWantedLevel(5);
        }

        void Tick() {
            if (alwaysWantedLevel) {
                SetWantedLevel(5);
            }

            if (neverWantedLevel && PLAYER::GET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID()) > 0) {
                ClearWantedLevel(); 
            }

            if (holdWantedLevel) {
                int currentLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID());
                SetWantedLevel(currentLevel); 
            }
        }

    }
} 
