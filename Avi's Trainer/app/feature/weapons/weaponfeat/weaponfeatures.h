#pragma once
namespace app {
    namespace feature::weapon {

        namespace gravityGun {
            extern bool tickGravityGun;
            extern bool tickGravityGun_Static;
            extern bool tickGravityGun_Oscillate;
            extern bool tickGravityGun_Force;
            extern bool tickGravityGun_DisableGrav;
            void Tick();
        }
        void WeaponThread();

    }
}