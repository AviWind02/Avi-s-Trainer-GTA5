#include "pch.h"
#include "weaponfeatures.h"

namespace app {
    namespace feature {
        namespace weapon {
            using namespace  app::feature::weapon;       

            void WeaponThread() {
                srand(GetTickCount64());
                while (true)
                {
                    gravityGun::Tick();

                    WAIT(0);
                }
            }
        }
    }
}