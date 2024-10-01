#pragma once
namespace feature {
    namespace local {

        void LocalThread();


        namespace CleanPlayer {

            extern float healthRechargeRateSpeed;
            extern bool tickHealthRechargeRate, tickCleanPlayer, tickCleanPlayerLooped;

            void Tick();
        }

        namespace Health {

            extern bool tickInvincibility, tickkillPlayer, tickkillPlayerLooped;

            void Tick();
        }

        namespace Refill {

            extern bool tickRefillHealthBar, tickRefillArmourBar, tickRefillHealthBarLooped, tickRefillArmourBarLooped;

            void Tick();
        }

        namespace Ragdoll {

            extern bool tickNoRagdoll;

            void Tick();
        }

        namespace Seatbelt {

            extern bool tickSeatbelt;

            void Tick();
        }

        namespace WantedLevel {

            extern bool neverWantedLevel, alwaysWantedLevel, editWantedLevel, clearWantedLevel, holdWantedLevel;
            extern int wantedLevelIndex;

            void AdjustLevel(int wantedLevel);
            void Tick();
        }

        namespace Noclip {

            extern bool tickNoclip;
            extern float noClipSpeed;
            extern int entityAlpha;

            void Tick();
        }

        namespace Movement {

            extern bool tickFastRun, tickFastSwim, tickFastRunReset, tickFastSwimReset, tickMaxStamina, tickSuperJump, tickSetMaxStamina;
            extern float runningIndex, swimmingIndex;

            void Tick();
        }

        namespace Invisible {

            extern int alphaValue;
            extern bool tickInvisible, tickInvisibleIndex, tickInvisibleNetwork;

            void Tick();
        }

        namespace IgnorePlayer {

            extern bool tickIgnorePlayer;

            void Tick();
        }
    }
}