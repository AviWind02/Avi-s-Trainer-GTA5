#pragma once

namespace app {
    namespace feature {
        namespace local {
            namespace playerhealth {
                extern float healthRechargeRateSpeed;
                extern bool tickHealthRechargeRate;
                extern bool tickCleanPlayer;
                extern bool tickInvincibility;
                extern bool wasInvincible;
                extern bool tickKillPlayer;
                extern bool tickrefillhealth;
                extern bool tickrefillarmor;

                void SetPlayerHealth(int health);
                void SetPlayerArmor(int armor);
                void SetHealthRechargeRate(float rate);
                void SetInvincibility(bool enabled);
                void ClearPlayerDamage();

                void Tick();

                void RefillHealth();
                void RefillArmor();
            }

            namespace wantedlevel {
                extern int wantedLevelIndex;
                extern bool holdWantedLevel;
                extern bool neverWantedLevel;
                extern bool alwaysWantedLevel;

                void SetWantedLevel(int level);
                void ClearWantedLevel();

                void EnableAlwaysWanted();
                void EnableNeverWanted();
                void HoldCurrentLevel();

                void Tick();
            }

            namespace playermovement {
                extern bool tickNoclip;
                extern float noClipSpeed;
                extern int entityAlpha;

                extern bool tickFastRun;
                extern bool tickFastSwim;
                extern bool tickFastRunReset;
                extern bool tickFastSwimReset;
                extern bool tickMaxStamina;
                extern bool tickSuperJump;
                extern float runningIndex;
                extern float swimmingIndex;

                void SetNoclipState(bool enabled);
                void UpdateNoclipSpeed(float speed);
                void ResetNoclip();

                void SetRunSpeed(float speed);
                void SetSwimSpeed(float speed);
                void EnableSuperJump(bool enabled);
                void ResetStamina();

                void Tick();
            }

            namespace playermisc {
                extern bool tickIgnorePlayer;
                extern bool resetIgnorePlayer;

                extern bool tickNoRagdoll;

                extern bool tickSeatbelt;

                extern int alphaValue;
                extern bool tickInvisible;
                extern bool tickInvisibleIndex;
                extern bool tickInvisibleNetwork;
                extern bool tickInvisibleReset;
                extern bool tickInvisibleNetworkReset;

                void ToggleIgnorePlayer(bool enabled);

                void ToggleRagdoll(bool enabled);
                void ToggleSeatbelt(bool enabled);
                void SetInvisibility(bool enabled, int alpha = 255, bool networkInvisible = false);

                void Tick();
            }

            void LocalThread();
        }
    }
}
