#include "pch.h"
#include "app/feature/local/localfeatures.h"

namespace app {
    namespace feature {
        namespace local {
            using namespace  app::feature::local;
            void LocalThread() {
                srand(GetTickCount64());
                while (true)
                {
                    playerhealth::Tick();
                    playermovement::Tick();
                    wantedlevel::Tick();
                    playermisc::Tick();
                    WAIT(0);
                }
            }
        }
    }
}