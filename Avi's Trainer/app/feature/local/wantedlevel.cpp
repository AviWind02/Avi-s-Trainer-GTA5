#include "pch.h"
#include "localfeatures.hpp"

namespace app {
    namespace feature::local {

        using namespace g_feature;

        WantedLevel::WantedLevel()
            : wantedLevelIndex(0), holdWantedLevel(false), neverWantedLevel(false), alwaysWantedLevel(false) {}

        void WantedLevel::SetWantedLevel(int level) {
            wantedLevelIndex = level;
            PLAYER::SET_PLAYER_WANTED_LEVEL(g_player::GetPlayerID(), wantedLevelIndex, false);
            PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(g_player::GetPlayerID(), false);
        }

        void WantedLevel::ClearWantedLevel() {
            SetWantedLevel(0);
        }

        void WantedLevel::HoldCurrentLevel() {
            holdWantedLevel = true;
        }

        void WantedLevel::EnableNeverWanted() {
            neverWantedLevel = true;
            alwaysWantedLevel = false;
            ClearWantedLevel(); 
        }

        void WantedLevel::EnableAlwaysWanted() {
            alwaysWantedLevel = true;
            neverWantedLevel = false;
            SetWantedLevel(5);
        }

        void WantedLevel::Tick() {
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
