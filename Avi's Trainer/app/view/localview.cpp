#include "pch.h"
#include "app/feature/local/localfeatures.h"
using namespace GUI;

namespace view {
	namespace local {
        using namespace app::feature::local;

        
		void View()
        {
            GUI::menu::SetSubTitle("Local Menu");

            {//Health Options

                buttons::Toggle("Invincible", &playerhealth::tickInvincibility);
                buttons::Toggle("Fast Health Regen", &playerhealth::tickHealthRechargeRate, "Health Regen is 2.5x faster");
                buttons::Toggle("Keep player clean", &playerhealth::tickCleanPlayer, "Player clean is looped");
                buttons::Option("Clean player", []() { playerhealth::ClearPlayerDamage(); });
                buttons::Option("Refil health", []() { playerhealth::RefillHealth(); });
                buttons::Toggle("Loop Max Health", &playerhealth::tickrefillhealth);
                buttons::Option("Refill Armour", []() { playerhealth::RefillArmor(); });
                buttons::Toggle("Loop Max Armour", &playerhealth::tickrefillarmor);

            }

            {
                buttons::Option("Clear Wanted Level", []() { wantedlevel::ClearWantedLevel(); });
                buttons::Toggle("Hold Level", &wantedlevel::holdWantedLevel);
                buttons::Toggle("Never Wanted", &wantedlevel::neverWantedLevel);
                buttons::Toggle("Always Wanted", &wantedlevel::alwaysWantedLevel);
                buttons::Int("Wanted Level", &wantedlevel::wantedLevelIndex, 0, 5, 1, []() { wantedlevel::SetWantedLevel(wantedlevel::wantedLevelIndex); });
            }      

            {//Player Movement options

                buttons::Toggle("No Clip", &playermovement::tickNoclip, "Navigate through the environment with collisions disabled. Controls(W: forward, S backwards, Mouse : camera, Left shfit boost, CTRL to pause at current coords)");
                buttons::Option("Max Stamina", []() { playermovement::ResetStamina(); });
                buttons::Float("Fast Run", &playermovement::runningIndex, 0.f, 1.5f, 0.1f);
                buttons::Float("Fast Swim", &playermovement::swimmingIndex, 0.f, 1.5f, 0.1f);
                buttons::Toggle("Loop Max Stamina", &playermovement::tickMaxStamina, "Enable Max Player Stamina(Loop)");
                buttons::Toggle("Super Jump", &playermovement::tickSuperJump, "Allows you to jump super high");

            }

            {//Player physics
                buttons::Toggle("Seatbelt", &playermisc::tickSeatbelt, "Fun to use on bikes | Works in SP in all vehicle");
                buttons::Toggle("No Ragdoll", &playermisc::tickNoRagdoll, "Most collision rules dont work on player");
                buttons::Toggle("Invisible", &playermisc::tickInvisible);
                buttons::Toggle("Invisible Network", &playermisc::tickInvisibleNetwork);
                buttons::Int("Alpha Value", &playermisc::alphaValue, 1, 255, 25);
            }

            {//Health Options #2 plus Igonre Player
                buttons::Toggle("Igonre Player", &playermisc::tickIgnorePlayer, "Most Peds will Igonre you, try going into the army base.");
                buttons::Option("Kill Yourself", []() { playerhealth::SetPlayerHealth(0); });
                buttons::Toggle("Keep Killing Yourself", &playerhealth::tickKillPlayer, "Why Not?");
            }
		}

	} 
}