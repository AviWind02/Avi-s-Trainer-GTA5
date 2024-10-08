#include "pch.h"

#include "controls.h"
#include "GUI/menu/menu.h"

#include <vendor/imgui/imgui.h>

// This is the control(key) file. 
// Not sure what to add
// it handles the menu controls, and has some options to check if something is being pressed
// oh and sub menu too

namespace GUI {
    namespace controls {

        bool isMenuOpen = true;

        bool cursorVisible = true;
        bool usingInMenuKeyboard = false;

        bool leftPressed = false;
        bool rightPressed = false;
        bool selectPressed = false;
        bool selectPressedCursor = false;

        int optionCount;
        int currentOption;

        int keyPressDelay = 150;
        uint64_t keyPressDelayTickCount = GetTickCount64();


        bool IsKeyPressed(int virtualKey)
        {
            return GetAsyncKeyState(virtualKey) & 0x8000;
        }

        bool IsOpenMenuPressed() { return IsKeyPressed(VK_F4); }
        bool IsMouseButtonPressed() { return IsKeyPressed('X'); }
        bool IsFavoriteKeyPressed() { return IsKeyPressed('B'); }
        bool IsScrollTopMenuPressed() { return IsKeyPressed(VK_TAB); }

        bool IsMovingForward() { return IsKeyPressed('W'); }
        bool IsMovingBackward() { return IsKeyPressed('S'); }
        bool IsMovingRight() { return IsKeyPressed('D'); }
        bool IsMovingLeft() { return IsKeyPressed('A'); }

        bool IsLeftShiftPressed() { return IsKeyPressed(VK_LSHIFT); }
        bool IsLeftCtrlPressed() { return IsKeyPressed(VK_CONTROL); }

        bool IsMouseWheelScrolledUp() { return PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_SCROLL_UP); }
        bool IsMouseWheelScrolledDown() { return PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN); }
        bool IsUpArrowPressed() { return IsKeyPressed(VK_UP) || IsKeyPressed(VK_NUMPAD8) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_UP); }

        bool IsDownArrowPressed() { return IsKeyPressed(VK_DOWN) || IsKeyPressed(VK_NUMPAD2) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_DOWN); }
        bool IsRightArrowPressed() { return IsKeyPressed(VK_RIGHT) || IsKeyPressed(VK_NUMPAD6) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_RIGHT); }
        bool IsLeftArrowPressed() { return IsKeyPressed(VK_LEFT) || IsKeyPressed(VK_NUMPAD4) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_LEFT); }
        bool IsSelectKeyPressed() { return IsKeyPressed(VK_RETURN) || IsKeyPressed(VK_NUMPAD5) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_ACCEPT); }
        bool IsBackKeyPressed() { return IsKeyPressed(VK_BACK) || IsKeyPressed(VK_NUMPAD0) || PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_CANCEL); }


        static constexpr int maxSubMenuLevels = 250;
        pages::SubMenu subMenuArray[maxSubMenuLevels];
        int subMenuLevel;
        pages::SubMenu currentSubMenu = pages::mainmenu_page;
        int originalOption[maxSubMenuLevels];
        void NextSubmenu(pages::SubMenu menu) {
            if (subMenuLevel < maxSubMenuLevels) {
                subMenuArray[subMenuLevel] = currentSubMenu;
                subMenuLevel++;
                originalOption[currentSubMenu] = currentOption;// Save the OG option - Dont need to re scroll and shit
                currentSubMenu = menu;
                currentOption = 1;
            }
        }
        void BackSubmenu() {
            if (subMenuLevel > 0) {
                subMenuLevel--;
                currentSubMenu = subMenuArray[subMenuLevel];
                currentOption = originalOption[subMenuLevel];
            }
        }


        char GetCharFromVK(int vk) {

            BYTE keyboardState[256];
            if (GetKeyboardState(keyboardState))
            {

                // Translate the virtual key to a scan code
                UINT scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);

                // Get the character from the virtual key
                char buffer[2];
                if (ToAscii(vk, scanCode, keyboardState, (LPWORD)buffer, 0) == 1) {
                    return buffer[0];
                }
            }
            return '\0';
        }

        char GetPressedKeyChar() {
            for (int key = 8; key <= 190; ++key) {
                if (GetAsyncKeyState(key) & 0x8000) {
                    return GetCharFromVK(key);
                }
            }
            return '\0'; //Return null character if no key is pressed
        }


        void GetUserInput(const char* option, char* userInput, int maxLength, bool* enterpressed) {
            int currentCharIndex = strlen(userInput);

            menu::SetOption(option, NULL, userInput);
            if (currentOption == optionCount)
            {
                usingInMenuKeyboard = true;
                uint64_t currentTick = GetTickCount64();
                if (currentTick - keyPressDelayTickCount > 150) {
                    //Check for input
                    if (IsKeyPressed(VK_ACCEPT)) { //Enter key
                        *enterpressed = true;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsKeyPressed(VK_BACK)) { //Backspace key
                        if (currentCharIndex > 0) {
                            userInput[--currentCharIndex] = '\0';
                            keyPressDelayTickCount = currentTick;
                        }
                    }
                    else {
                        char key = GetPressedKeyChar();
                        if (key != '\0' && currentCharIndex < maxLength - 1) {
                            *enterpressed = false;
                            userInput[currentCharIndex++] = key;
                            userInput[currentCharIndex] = '\0';
                            keyPressDelayTickCount = currentTick;
                        }
                    }
                }
            }
            else
                usingInMenuKeyboard = false;
        }


        void ControlTick()
        {
            uint64_t currentTick = GetTickCount64();


            leftPressed = false;
            rightPressed = false;
            selectPressed = false;
            selectPressedCursor = false;

        /*    if (cursorVisible) {
                ImGui::GetIO().MouseDown[0] = PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_ACCEPT);
                ImGui::GetIO().MouseDown[1] = PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_CANCEL);
            }*/

            if (currentTick - keyPressDelayTickCount > keyPressDelay)
            {
                if (IsOpenMenuPressed())
                {
                    isMenuOpen = !isMenuOpen;
                    keyPressDelayTickCount = currentTick;
                }
                if (isMenuOpen)
                {
                    if (IsUpArrowPressed() || IsMouseWheelScrolledUp())
                    {
                        currentOption > 1 ? currentOption-- : currentOption = optionCount;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsDownArrowPressed() || IsMouseWheelScrolledDown())
                    {
                        currentOption < optionCount ? currentOption++ : currentOption = 1;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsSelectKeyPressed())
                    {
                        selectPressed = true;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsBackKeyPressed() && !usingInMenuKeyboard)
                    {
                        BackSubmenu();
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsRightArrowPressed())
                    {
                        rightPressed = true;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsLeftArrowPressed())
                    {
                        leftPressed = true;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_ACCEPT))
                    {
                        //selectPressedCursor = true;
                        keyPressDelayTickCount = currentTick;
                    }
                    else if (IsMouseButtonPressed())
                    {
                        cursorVisible = !cursorVisible;
                        keyPressDelayTickCount = currentTick;
                    }
                }
            }
            optionCount = 0;
        }



        void DisableControls()
        {
            if (isMenuOpen)
            {
                if (usingInMenuKeyboard)
                {
                    PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
                }

                if (cursorVisible) {
                    //HUD::HUD_FORCE_WEAPON_WHEEL(false);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_LR, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_UD, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_UP_ONLY, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_DOWN_ONLY, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_LEFT_ONLY, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_RIGHT_ONLY, true);

                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK1, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK2, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_BLOCK, true);
                    PAD::DISABLE_CONTROL_ACTION(2, INPUT_LOOK_RIGHT_ONLY, true);

                }

                HUD::HIDE_HELP_TEXT_THIS_FRAME();
                CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(5);//MP_MESSAGE
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);//HELP_TEXT
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(11);//FLOATING_HELP_TEXT_1
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(12);//FLOATING_HELP_TEXT_2
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(16);//RADIO_STATIONS
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(18);//GAME_STREAM
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(19);//WEAPON_WHEEL
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(20);//WEAPON_WHEEL_STATS
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(21);//HUD_COMPONENTS
                HUD::HIDE_HUD_COMPONENT_THIS_FRAME(22);//HUD_WEAPONS



                //Phone
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_UP, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_DOWN, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_LEFT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_RIGHT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_SELECT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_CANCEL, true);


                //Hud
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);

                //Vehicle
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_NEXT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_PREV, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_NEXT_WEAPON, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_PREV_WEAPON, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);

                //Weapons/Attack
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_UNARMED, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_MELEE, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_HANDGUN, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_SHOTGUN, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_SMG, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_AUTO_RIFLE, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_SNIPER, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_HEAVY, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON_SPECIAL, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_WEAPON, true);
                PAD::DISABLE_CONTROL_ACTION(2, INPUT_PREV_WEAPON, true);
            }
        }

    }
}