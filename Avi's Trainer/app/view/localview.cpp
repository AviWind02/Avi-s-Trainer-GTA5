#include "pch.h"
#include "app/feature/local/localfeatures.hpp"
using namespace GUI;

namespace view {
	namespace local {
        using namespace app::feature::local;

        PlayerHealth playerHealth;
        WantedLevel wantedLevel;
        PlayerMovement playerMovement;
        PlayerMisc playermisc;
        
		void View()
        {
            GUI::menu::SetSubTitle("Local Menu");

            {//Health Options

                buttons::Toggle("Invincible", &playerHealth.tickInvincibility);
                buttons::Toggle("Fast Health Regen", &playerHealth.tickHealthRechargeRate, "Health Regen is 2.5x faster");
                buttons::Toggle("Keep player clean", &playerHealth.tickCleanPlayer, "Player clean is looped");
                buttons::Option("Clean player", []() { playerHealth.ClearPlayerDamage(); });
                buttons::Option("Refil health", []() { playerHealth.RefillHealth(); });
                buttons::Toggle("Loop Max Health", &playerHealth.tickrefillhealth);
                buttons::Option("Refill Armour", []() { playerHealth.RefillArmor(); });
                buttons::Toggle("Loop Max Armour", &playerHealth.tickrefillarmor);

            }

            {
                buttons::Option("Clear Wanted Level", []() { wantedLevel.ClearWantedLevel(); });
                buttons::Toggle("Hold Level", &wantedLevel.holdWantedLevel);
                buttons::Toggle("Never Wanted", &wantedLevel.neverWantedLevel);
                buttons::Toggle("Always Wanted", &wantedLevel.alwaysWantedLevel);
                buttons::Int("Wanted Level", &wantedLevel.wantedLevelIndex, 0, 5, 1, []() { wantedLevel.SetWantedLevel(wantedLevel.wantedLevelIndex); });
            }      

            {//Player Movement options

                buttons::Toggle("No Clip", &playerMovement.tickNoclip, "Navigate through the environment with collisions disabled. Controls(W: forward, S backwards, Mouse : camera, Left shfit boost, CTRL to pause at current coords)");
                buttons::Option("Max Stamina", []() { playerMovement.ResetStamina(); });
                buttons::Float("Fast Run", &playerMovement.runningIndex, 0.f, 1.5f, 0.1f);
                buttons::Float("Fast Swim", &playerMovement.swimmingIndex, 0.f, 1.5f, 0.1f);
                buttons::Toggle("Loop Max Stamina", &playerMovement.tickMaxStamina, "Enable Max Player Stamina(Loop)");
                buttons::Toggle("Super Jump", &playerMovement.tickSuperJump, "Allows you to jump super high");

            }

            {//Player physics
                buttons::Toggle("Seatbelt", &playermisc.tickSeatbelt, "Fun to use on bikes | Works in SP in all vehicle");
                buttons::Toggle("No Ragdoll", &playermisc.tickNoRagdoll, "Most collision rules dont work on player");
                buttons::Toggle("Invisible", &playermisc.tickInvisible);
                buttons::Toggle("Invisible Network", &playermisc.tickInvisibleNetwork);
                buttons::Int("Alpha Value", &playermisc.alphaValue, 1, 255, 25);
            }

            {//Health Options #2 plus Igonre Player
                buttons::Toggle("Igonre Player", &playermisc.tickIgnorePlayer, "Most Peds will Igonre you, try going into the army base.");
                buttons::Option("Kill Yourself", []() { playerHealth.SetPlayerHealth(0); });
                buttons::Toggle("Keep Killing Yourself", &playerHealth.tickKillPlayer, "Why Not?");
            }
		}

	} 
}