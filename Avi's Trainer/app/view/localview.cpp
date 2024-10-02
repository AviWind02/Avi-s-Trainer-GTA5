#include "pch.h"
#include "app/feature/local/localfeatures.h"

using namespace GUI;

namespace view {
	namespace local {

		void View()
		{
            GUI::menu::SetSubTitle("Local Menu");

            {//Health Options
                buttons::Toggle("Invincible", &feature::local::Health::tickInvincibility);
                buttons::Toggle("Fast Health Regen", &feature::local::CleanPlayer::tickHealthRechargeRate, "Health Regen is 2.5x faster");
                buttons::Toggle("Keep player clean", &feature::local::CleanPlayer::tickCleanPlayerLooped, "Player clean is looped");
                buttons::Option("Clean player", &feature::local::CleanPlayer::tickCleanPlayer, "Cleans player. Removes dust, dirt, and blood");
                buttons::Option("Refil health", &feature::local::Refill::tickRefillHealthBar);
                buttons::Toggle("Loop Max Health", &feature::local::Refill::tickRefillHealthBarLooped);
                buttons::Option("Refill Armour", &feature::local::Refill::tickRefillArmourBar);
                buttons::Toggle("Loop Max Armour", &feature::local::Refill::tickRefillArmourBarLooped);
            }

            {//Wanted Level Stuff
                buttons::Option("Clear Wanted Level", &feature::local::WantedLevel::clearWantedLevel);
                buttons::Toggle("Hold Level", &feature::local::WantedLevel::holdWantedLevel, "Holds current wanted level and disable wanted level slider");
                buttons::Toggle("Never Wanted", &feature::local::WantedLevel::neverWantedLevel);
                buttons::Toggle("Always Wanted", &feature::local::WantedLevel::alwaysWantedLevel, "Sets wanted level to 5 and loops");
                if (buttons::Int("Wanted Level", &feature::local::WantedLevel::wantedLevelIndex, 0, 5, 1))
                    feature::local::WantedLevel::editWantedLevel = true;
            }

            {//Player Movement options

                buttons::Toggle("No Clip", &feature::local::Noclip::tickNoclip, "Navigate through the environment with collisions disabled. Controls(W: forward, S backwards, Mouse : camera, Left shfit boost, CTRL to pause at current coords)");
                buttons::Option("Max Stamina", &feature::local::Movement::tickSetMaxStamina, "Enable Max Player Stamina(Loop)");
                //buttons::Float("Fast Run", &feature::local::Movement::runningIndex, 1, 10, 0.5f);
                //buttons::Float("Fast Swim", &feature::local::Movement::swimmingIndex, 1, 10, 0.5f);
                buttons::Toggle("Loop Max Stamina", &feature::local::Movement::tickMaxStamina, "Enable Max Player Stamina(Loop)");
                buttons::Toggle("Super Jump", &feature::local::Movement::tickSuperJump, "Allows you to jump super high");

            }

            {//Player physics
                buttons::Toggle("Seatbelt", &feature::local::Seatbelt::tickSeatbelt, "Fun to use on bikes | Works in SP in all vehicle");
                buttons::Toggle("No Ragdoll", &feature::local::Ragdoll::tickNoRagdoll, "Most collision rules dont work on player");
                buttons::Toggle("Invisible", &feature::local::Invisible::tickInvisible);
                buttons::Toggle("Invisible Network", &feature::local::Invisible::tickInvisibleNetwork);
                buttons::Int("Alpha Value", &feature::local::Invisible::alphaValue, 1, 255, 25);

            }

            {//Misc
                buttons::Toggle("Igonre Player", &feature::local::IgnorePlayer::tickIgnorePlayer, "Most Peds will Igonre you, try going into the army base.");
                buttons::Option("Kill Yourself", &feature::local::Health::tickkillPlayer, "The gods have offered you a choice: rise above or fall below, but know that every action has a consequence.");
                buttons::Toggle("Keep Killing Yourself", &feature::local::Health::tickkillPlayerLooped, "Why Not?");
            }
		}

	} 
}