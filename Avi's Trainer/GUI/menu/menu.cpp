#include "pch.h"
#include "menu.h"
// This page has the main menu elements the core you can say. 
//Here is where the Title, Option, and other UI methods are

namespace GUI {
    namespace menu {
        namespace colours {
            Colour optionText = { 255, 255, 255, 255 };
            Colour optionRect = { 0, 0, 0, 225 };
            Colour scrollerColor = { 255, 223, 0, 175 };
            Colour scrollerColorHover = { 255, 255, 255, 50 };
            Colour hoverColor = { 100, 100, 100, 190 };
            Colour toggleOff = { 255, 0, 0, 255 };
            Colour toggleOn = { 0, 255, 0, 255 };
            Colour footerRect = { 0, 0, 0, 255 };
            Colour headerRect = { 0, 0, 0, 255 };
        }

        int maxOptions = 10;
        int hoveredOption;

        Vector2 menuPosition = { 0.15f, 0.125f };
        Vector2 optionSize = { 0.17f, 0.025f };
        Vector2 optionOffset = { 0.0f, 0.010f };
        Vector2 headerSize = { optionSize.x, 0.047f };
        Vector2 headerTextOffset = { optionSize.x, 0.065f };
        Vector2 footerSize = { optionSize.x, 0.025f };

        Vector2 textOffset = { 0.08f, 0.0025f };
        Vector2 rightTextOffset = { 0.0f, 0.005f };
        Vector2 footerTextOffset = { 0.08f, 0.0025f };
        Vector2 spriteOffset = { 0.008, 0.0142 };

        float scrollerY = menuPosition.y + 0.125f;
        float scrollerSpeed = 0.10f;
        float textScale = 0.25f;
        float screenWidth = 1920.0f;
        float screenHeight = 1080.0f;


        // Debug variables
        Vector2 debugMouseCoords = { 0.0f, 0.0f };
        Vector2 debugMouseScreenCoords = { 0.0f, 0.0f };
        bool debugIsDragging;
        Vector2 debugDragOffset = { 0.0f, 0.0f };
        Vector2 debugMenuPosition = { 0.0f, 0.0f };
        bool debugMouseInOption;
        int debugHoveredOption = -1;
        float debugMouseDistanceFromOption = -1.0f;

        void EnableMouse()//Meh
        {
            if (controls::cursorVisible)
            {
                HUD::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
                PAD::IS_USING_CURSOR(2);
                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_Normal);
            }
            else
                return;
        }

        Vector2 GetScreenCoords(float normalizedX, float normalizedY) {
            Vector2 screenCoords{0.f, 0.f};
            screenCoords.x = normalizedX * screenWidth;
            screenCoords.y = normalizedY * screenHeight;
            return screenCoords;
        }

        bool IsMouseInBounds(float x, float y, float width, float height) {
            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            Vector2 mouseCoords = GetScreenCoords(mouseX, mouseY);

            x = x - width / 2;
            y = y - height / 2;

            Vector2 topLeft = GetScreenCoords(x, y);
            Vector2 bottomRight = GetScreenCoords(x + width, y + height);

            return mouseCoords.x >= topLeft.x && mouseCoords.x <= bottomRight.x && mouseCoords.y >= topLeft.y && mouseCoords.y <= bottomRight.y;
        }



        bool SetOption(const char* leftText, const char* centerText, const char* rightText)
        {
            controls::optionCount++;

            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int endOption = startOption + maxOptions - 1;

            if (controls::optionCount >= startOption && controls::optionCount <= endOption) {
                float yPos = (optionSize.y * (controls::optionCount - startOption + 1) + optionOffset.y) + menuPosition.y;

                static float smoothScrollYPosition = yPos;//Had to create two or it does some odd stuff
                static float smoothScrollYPositionMouse = yPos;
                float scrollSpeed = 0.10f;

                Vector2 smoothTextPos = { menuPosition.x, smoothScrollYPosition };
                if (controls::cursorVisible)
                {
                    //bool isMouseInOption = (mouseX >= optionLeft && mouseX <= optionRight) && (mouseY >= optionTop && mouseY <= optionBottom);
                    bool isMouseInOption = IsMouseInBounds(menuPosition.x, yPos, optionSize.x, optionSize.y);

                    if (isMouseInOption) {
                        hoveredOption = controls::optionCount;
                        debugHoveredOption = hoveredOption;
                        HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_MiddleFinger);

                        if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 237)) {
                            controls::currentOption = hoveredOption;
                        }

                        debugMouseDistanceFromOption = 0.0f;
                    }
                    else {
                        debugMouseDistanceFromOption = fabsf(PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y) - yPos);
                    }

                    debugMouseInOption = isMouseInOption;

                }
                bool isCurrentOption = controls::currentOption == controls::optionCount;
                bool isHoveredOption = hoveredOption == controls::optionCount;



                if (leftText != NULL) {
                    Vector2 leftTextPos = { (menuPosition.x - textOffset.x) + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(leftText, colours::optionText, leftTextPos, { textScale, textScale }, false, false);
                }

                if (centerText != NULL) {
                    Vector2 centerTextPos = { menuPosition.x + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(centerText, colours::optionText, centerTextPos, { textScale, textScale }, true, false);
                }

                if (rightText != NULL) {
                    Vector2 rightTextPos = { ((menuPosition.x + textOffset.x) + rightTextOffset.x) + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(rightText, colours::optionText, rightTextPos, { textScale, textScale }, false, true);
                }

                if (isHoveredOption && controls::cursorVisible)
                {
                    smoothScrollYPositionMouse += (yPos - smoothScrollYPositionMouse) * scrollSpeed;
                    draw::Rect_Center(colours::scrollerColorHover, { menuPosition.x, smoothScrollYPositionMouse }, optionSize);
                }
                if (isCurrentOption) {
                    smoothScrollYPosition += (yPos - smoothScrollYPosition) * scrollSpeed;
                    draw::Rect_Center(colours::scrollerColor, { menuPosition.x, smoothScrollYPosition }, optionSize);


                    if (controls::selectPressed) {
                        return true;
                    }
                }

            }

            return false;
        }

        void SetSpriteOnOption(const std::string& textureDict, const std::string& textureName, Vector2 size, float rotation, Colour color)
        {
            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int endOption = startOption + maxOptions - 1;

            if (controls::optionCount >= startOption && controls::optionCount <= endOption)
            {
                float yPos = (optionSize.y * (controls::optionCount - startOption + 1) + optionOffset.y) + menuPosition.y;

                Vector2 spritePos = { ((menuPosition.x + textOffset.x) + optionOffset.x) - spriteOffset.x,  yPos - optionSize.y / 2.0f + spriteOffset.y };

                draw::Sprite(textureDict, textureName, spritePos, size, rotation, color);
            }
        }

        void DragMenuWithMouse() {

            EnableMouse();

            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            debugMouseCoords = { mouseX, mouseY };

            Vector2 mouseCoords = GetScreenCoords(mouseX, mouseY);

            debugMouseScreenCoords = mouseCoords;


            bool isLeftClickHeld = PAD::IS_DISABLED_CONTROL_PRESSED(0, 237);

            static bool isDragging = false;
            static Vector2 dragOffset = { 0.0f, 0.0f };

            bool isMouseWithinHeader = IsMouseInBounds(menuPosition.x, menuPosition.y, headerSize.x, headerSize.y);

            if (isMouseWithinHeader)
                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_PreGrab);

            if (isMouseWithinHeader && isLeftClickHeld && !isDragging) {


                isDragging = true;
                dragOffset = { mouseX - menuPosition.x, mouseY - menuPosition.y };
            }

            if (isDragging && isLeftClickHeld) {

                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_Grab);

                menuPosition.x = mouseX - dragOffset.x;
                menuPosition.y = mouseY - dragOffset.y;
            }

            if (!isLeftClickHeld) {
                isDragging = false;
            }

            debugIsDragging = isDragging;
            debugDragOffset = dragOffset;
            debugMenuPosition = menuPosition;
        }

        void Title()
        {

            DragMenuWithMouse();//You can drag the menu to any Pos on the screen
            const char* titleText = "Avi";

            Vector2 titlePos = { menuPosition.x, menuPosition.y };
            draw::Rect_Center(colours::headerRect, titlePos, headerSize);

            Vector2 textPos = { (menuPosition.x + (headerSize.x - headerTextOffset.x)), (menuPosition.y + (headerSize.y - headerTextOffset.y)) };
            draw::Text(titleText, colours::optionText, textPos, { 0.65f, 0.65f }, true, false);

            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int displayedOptions = controls::optionCount - startOption + 1;
            displayedOptions = (displayedOptions > maxOptions) ? maxOptions : displayedOptions;

            float rectHeight = (optionSize.y * displayedOptions) - (optionOffset.y / 2) + 0.04f;
            float rectYPos = menuPosition.y + 0.02f + rectHeight / 2 - optionSize.y / 2;

            Vector2 rectPos = { menuPosition.x, rectYPos };
            Vector2 rectSize = { optionSize.x, rectHeight };

            draw::Rect_Center(colours::optionRect, rectPos, rectSize);
        }

        void End()
        {
            int currentPage = (controls::currentOption - 1) / maxOptions + 1;
            int startOption = (currentPage - 1) * maxOptions + 1;
            int displayedOptions = controls::optionCount - startOption + 1;
            displayedOptions = (displayedOptions > maxOptions) ? maxOptions : displayedOptions;

            float targetYPosition = (optionSize.y * displayedOptions + optionSize.y + optionOffset.y) + menuPosition.y;

            static float currentYPosition = targetYPosition;
            float speed = 0.1f;
            currentYPosition += (targetYPosition - currentYPosition) * speed;

            Vector2 endPos = { menuPosition.x, currentYPosition };

            draw::Rect_Center(colours::footerRect, endPos, footerSize);

            int totalPages = (controls::optionCount + maxOptions - 1) / maxOptions;
            char footerText[32];
            snprintf(footerText, sizeof(footerText), "Page %d/%d", currentPage, totalPages);
            std::string lText = (controls::cursorVisible ? "Cursor: On | " : "");
            Vector2 leftTextPos = { menuPosition.x - footerTextOffset.x, endPos.y - optionSize.y / 2.0f + footerTextOffset.y };
            draw::Text((lText + "v2").c_str(), colours::optionText, leftTextPos, {textScale, textScale}, false, false);

            Vector2 rightTextPos = { menuPosition.x + footerTextOffset.x, endPos.y - optionSize.y / 2.0f + footerTextOffset.y };
            draw::Text(footerText, colours::optionText, rightTextPos, { textScale, textScale }, false, true);
        }
    }
}

// Was trying to create those lil boxes Rampage has in their trainer 
/*
   Vector2 squarePosition = { 0.99f, 0.f };
        Vector2 squareTextPosition = { squarePosition.x, squarePosition.y };
        Vector2 squareSize = { 0.022f, 0.034f };
        Vector2 spriteSize = { 0.014f, 0.025f };
        Vector2 squareoffset = { 0.f, 1.2f };
        Vector2 infoRectOffset = { 0.1245f, 0.1027f };  // X and Y offset for the rectangle

        Vector2 textOffsetInfo = { 0.02f, 0.015f };  // X and Y offsets for positioning the text
        float ySpacingFromTopInfo = 0.025f;           // Y spacing from the top of the rectangle
        float ySpacingPerLineInfo = 0.03f;            // Y spacing between each line
        float gapLeftToCenterInfo;  // Horizontal gap between left and center text
        float gapRightToCenterInfo; // Horizontal gap between right and center text


        float squareGrowth = 0.001f;

        // Variables to track click and growth
        int activeSquare = -1;          // Track the active square (currently growing)
        float growthAmount = 0.0f;      // Amount the rectangle has grown
        float maxGrowthSize = 0.2f;     // Maximum size the rectangle can grow to
        float growthSpeed = 0.005f;     // Speed at which the rectangle grows
        bool isClosing = false;         // Whether the rectangle is closing

        bool debugMouseInSquare = false;


        void DrawSquareWithSprite(const std::string& textureDict, const std::string& textureName, float rotation, Colour color, int count) {
            // Get the current mouse position (normalized)
            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            // Variables to store the modified size if the mouse is within bounds
            Vector2 modifiedSquareSize = squareSize;

            // Adjust the Y-position based on the count to space each square vertically
            float adjustedYPosition = squarePosition.y + (count * squareSize.y * squareoffset.y);

            // Check if the mouse is within the square's bounds
            bool isMouseInSquare = IsMouseInBounds(squarePosition.x, adjustedYPosition, squareSize.x, squareSize.y);

            if (isMouseInSquare) {
                // Increase the width and height slightly when the mouse is inside
                modifiedSquareSize.x += squareGrowth;
                modifiedSquareSize.y += squareGrowth;
                debugMouseInSquare = true;

                // Handle click behavior for toggling open/close
                if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, 237)) {
                    if (activeSquare == count) {
                        // If the clicked square is already open, start closing it
                        isClosing = true;
                        INFO("Clicked to close");
                    }
                    else {
                        // If a different square is clicked, reset and open the new one
                        activeSquare = count;
                        isClosing = false;  // Don't set closing since we are opening a new square
                        growthAmount = 0.0f;  // Reset growth for the new square
                        INFO("Clicked to open");
                    }
                }
            }
            else {
                debugMouseInSquare = false;
            }

            // Calculate the top-left corner of the square based on the position and size
            Vector2 topLeftPos = { squarePosition.x - modifiedSquareSize.x / 2, adjustedYPosition - modifiedSquareSize.y / 2 };

            // Draw the square (using a rectangle to represent the square)
            draw::Rect({ 0, 0, 0, 150 }, topLeftPos, modifiedSquareSize);

            // Draw the sprite in the center of the square
            Vector2 spritePos = { squarePosition.x, adjustedYPosition };  // Center the sprite within the square
            draw::Sprite(textureDict, textureName, spritePos, spriteSize, rotation, color);

            // Handle the rectangle growth and closing logic
            if (activeSquare == count) {
                if (isClosing) {
                    // Close the rectangle
                    if (growthAmount > 0) {
                        growthAmount -= growthSpeed;  // Decrease the size gradually
                    }
                    else {
                        isClosing = false;  // Fully closed, stop closing
                        activeSquare = -1;  // Reset activeSquare to indicate no square is open
                    }
                }
                else {
                    // Open the new rectangle
                    if (growthAmount < maxGrowthSize) {
                        growthAmount += growthSpeed;  // Increase the size gradually
                    }
                }

                // Calculate the position and size of the growing rectangle
                Vector2 growthPos = { squarePosition.x - (squareSize.x / 2) - growthAmount / 2 - infoRectOffset.x,
                                     adjustedYPosition - (squareSize.y / 2) - growthAmount / 2 + infoRectOffset.y };
                Vector2 growthSize = { squareSize.x + growthAmount, squareSize.y + growthAmount };

                // Draw the expanding rectangle
                draw::Rect({ 0, 0, 0, 255 }, growthPos, growthSize);  // Example color and transparency
            }
        }

        void SetTextOptionInfoBox(int count, const char* LText, int line) {
            // Get the top-left Y-position from the opened rectangle of DrawSquareWithSprite
            float adjustedYPosition = squarePosition.y + (count * squareSize.y * squareoffset.y) + ySpacingFromTopInfo;

            // Adjust the Y-position based on the line number and spacing for each line
            float lineYPosition = (adjustedYPosition + (line * ySpacingPerLineInfo)) + textOffsetInfo.y;

            // Calculate positions for left, center, and right text based on the offsets
            Vector2 leftTextPos = { (squareTextPosition.x - textOffsetInfo.x), lineYPosition };

            // Draw left, center, and right text
            if (LText) {
                draw::Text(LText, { 255, 255, 255, 255 }, leftTextPos, { textScale, textScale }, false, false);
            }
        }

*/