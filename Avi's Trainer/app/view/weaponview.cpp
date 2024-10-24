#include "pch.h"
#include "app/feature/weapons/weaponfeat/weaponfeatures.h"
using namespace GUI;

namespace view {
    namespace weapon {
        using namespace app::feature::weapon;
      
        void View()
        {
            GUI::menu::SetSubTitle("Weapon Stuff");

            {//Grav Guns
                GUI::buttons::Toggle("Oscillating Gravity Gun", &gravityGun::tickGravityGun_Oscillate, []() { gravityGun::tickGravityGun_Static = false; gravityGun::tickGravityGun_Force = false; });
                GUI::buttons::Toggle("Static Gravity Gun", &gravityGun::tickGravityGun_Static, []() { gravityGun::tickGravityGun_Oscillate = false; gravityGun::tickGravityGun_Force = false; });
                GUI::buttons::Toggle("Force Gun", &gravityGun::tickGravityGun_Force, []() { gravityGun::tickGravityGun_Oscillate = false;  gravityGun::tickGravityGun_Static = false; });
                GUI::buttons::Toggle("Disable Gravity Gun", &gravityGun::tickGravityGun_DisableGrav, []() { gravityGun::tickGravityGun_Oscillate = false;  gravityGun::tickGravityGun_Static = false; });


                

            }
            
        }

    }
}