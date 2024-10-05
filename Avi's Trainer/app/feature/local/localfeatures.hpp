#pragma once
namespace app {
    namespace feature::local {

        class PlayerHealth {
        public:
            float healthRechargeRateSpeed;
            bool tickHealthRechargeRate;
            bool tickCleanPlayer;
            bool tickInvincibility;
            bool wasInvincible;
            bool tickKillPlayer;
            bool tickrefillhealth;
            bool tickrefillarmor;

            PlayerHealth();

            void SetPlayerHealth(int health);
            void SetPlayerArmor(int armor);
            void SetHealthRechargeRate(float rate);
            void SetInvincibility(bool enabled);
            void ClearPlayerDamage();

            void Tick();

            void RefillHealth();
            void RefillArmor();
        };


        class WantedLevel {
        private:

        public:
            int wantedLevelIndex;
            bool holdWantedLevel;
            bool neverWantedLevel;
            bool alwaysWantedLevel;

            WantedLevel();

            void SetWantedLevel(int level);
            void ClearWantedLevel();

            void EnableAlwaysWanted();
            void EnableNeverWanted();
            void HoldCurrentLevel();

            void Tick();
        };

        class PlayerMovement {
        public:
            bool tickNoclip;
            float noClipSpeed;
            int entityAlpha;

            bool tickFastRun;
            bool tickFastSwim;
            bool tickFastRunReset;
            bool tickFastSwimReset;
            bool tickMaxStamina;
            bool tickSuperJump;
            float runningIndex;
            float swimmingIndex;

            PlayerMovement();

            void SetNoclipState(bool enabled);
            void UpdateNoclipSpeed(float speed);
            void ResetNoclip();

            void SetRunSpeed(float speed);
            void SetSwimSpeed(float speed);
            void EnableSuperJump(bool enabled);
            void ResetStamina();

            void Tick();
        };

        class PlayerMisc {
        public:
            bool tickIgnorePlayer;
            bool resetIgnorePlayer;

            bool tickNoRagdoll;

            bool tickSeatbelt;

            int alphaValue;
            bool tickInvisible;
            bool tickInvisibleIndex;
            bool tickInvisibleNetwork;
            bool tickInvisibleReset;
            bool tickInvisibleNetworkReset;

            PlayerMisc();

            void ToggleIgnorePlayer(bool enabled);

            void ToggleRagdoll(bool enabled);
            void ToggleSeatbelt(bool enabled);
            void SetInvisibility(bool enabled, int alpha = 255, bool networkInvisible = false);

            void Tick();
        };

        void LocalThread();
    }
}