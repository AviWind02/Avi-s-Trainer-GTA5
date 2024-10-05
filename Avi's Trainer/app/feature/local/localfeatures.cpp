#include "pch.h"
#include "app/feature/local/localfeatures.hpp"

namespace app {
    namespace feature {
        namespace local {
            using namespace  app::feature::local;

            PlayerHealth playerHealth;
            WantedLevel wantedLevel;
            PlayerMovement playerMovement;
            PlayerMisc playermisc;

            void LocalThread() {
                srand(GetTickCount64());
                while (true)
                {
                    playerHealth.Tick();
                    playerMovement.Tick();
                    wantedLevel.Tick();
                    playermisc.Tick();
                    WAIT(0);
                }
            }
        }
    }
}