#pragma once
namespace pages
{
    enum SubMenu {
        base_sub,

        VehicleView_VehicleCategories,
        VehicleView_VehicleCategories_Picked,
    };
}

namespace GUI {
    namespace controls {
        extern bool cursorVisible;
        extern bool leftPressed;
        extern bool rightPressed;
        extern bool selectPressed;
        extern bool selectPressedCursor;
        extern bool usingInMenuKeyboard;
        extern bool isMenuOpen;

        extern int optionCount;
        extern int currentOption;
        extern int keyPressDelay;

        extern uint64_t keyPressDelayTickCount;

        bool IsOpenMenuPressed();
        bool IsMouseButtonPressed();
        bool IsFavoriteKeyPressed();
        bool IsScrollTopMenuPressed();
        bool IsMovingForward();
        bool IsMovingBackward();
        bool IsMovingRight();
        bool IsMovingLeft();
        bool IsLeftShiftPressed();
        bool IsLeftCtrlPressed();
        bool IsMouseWheelScrolledUp();
        bool IsMouseWheelScrolledDown();
        bool IsUpArrowPressed();
        bool IsDownArrowPressed();
        bool IsRightArrowPressed();
        bool IsLeftArrowPressed();
        bool IsSelectKeyPressed();
        bool IsBackKeyPressed();

        void NextSubmenu(pages::SubMenu menu);
        void BackSubmenu();
        char GetCharFromVK(int vk);
        char GetPressedKeyChar();
        void GetUserInput(const char* option, char* userInput, int maxLength, bool* enterpressed);
        void DisableControls();
        void ControlTick();
    }
}