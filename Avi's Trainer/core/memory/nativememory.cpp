#include "pch.h"
#include "nativememory.h"

namespace core::memory {
    namespace nativememory {


        using namespace patterns;


        int StreamRenderGfxPtrOffset = 0;
        int DrawHandlerPtrOffset = 0;
        uint32_t StreamRenderWheelWidthOffset = 0;
        uint8_t StreamRenderWheelSizeOffset = 0;

        void InitOffsets() {//Found some of these patterns from Menyoo, and vStance

            auto address = FindPattern("\x83\xF9\xFF\x74\x31\x4C\x8B\x0D\x00\x00\x00\x00\x44\x8B\xC1\x49\x8B\x41\x08", "xxxxxxxx????xxxxxxx");
            if (!address) {
                LOG_TAG("ERROR") << "Couldn't find GetAddressOfEntity pattern";
            }
            else {
                GetAddressOfEntity = reinterpret_cast<uintptr_t(*)(int)>(address);
                LOG_TAG("Debug") << "GetAddressOfEntity pattern found at: " << address;
            }

            address = FindPattern("\x0F\xB7\x05\x00\x00\x00\x00\x45\x33\xC9\x4C\x8B\xDA\x66\x85\xC0\x0F\x84\x00\x00\x00\x00\x44\x0F\xB7\xC0\x33\xD2\x8B\xC1\x41\xF7\xF0\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\x14\xD0\xEB\x09\x41\x3B\x0A\x74\x54",
                "xxx????xxxxxxxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxx");
            if (!address) {
                LOG_TAG("ERROR") << "Couldn't find GetModelInfo pattern";
            }
            else {
                GetModelInfo = reinterpret_cast<uintptr_t(*)(unsigned int modelHash, int* index)>(address);
                LOG_TAG("Debug") << "GetModelInfo pattern found at: " << address;
            }

            address = FindPattern("\x48\x63\xC1\x48\x8D\x0D\x00\x00\x00\x00\xF3\x0F\x10\x04\x81\xF3\x0F\x11\x05\x00\x00\x00\x00", "xxxxxx????xxxxxxxxx????");
            gravityOffsetWrite = reinterpret_cast<float*>(*reinterpret_cast<int*>(address + 6) + address + 10);
            LOG_TAG(gravityOffsetWrite == 0 ? "WARN" : "Debug") << "Gravity Offset: " << gravityOffsetWrite;
            gravityOffsetRead = reinterpret_cast<float*>(*reinterpret_cast<int*>(address + 19) + address + 23);
            LOG_TAG(gravityOffsetRead == 0 ? "WARN" : "Debug") << "Gravity Offset: " << gravityOffsetRead;


            {//Gears
                address = FindPattern("\x48\x8D\x8F\x00\x00\x00\x00\x4C\x8B\xC3\xF3\x0F\x11\x7C\x24", "xxx????xxxxxxxx");
                nextGearOffset = address == 0 ? 0 : *(int*)(address + 3);
                LOG_TAG(nextGearOffset == 0 ? "WARN" : "Debug") << "Next Gear Offset: " << nextGearOffset;

                currentGearOffset = address == 0 ? 0 : *(int*)(address + 3) + 2;
                LOG_TAG(currentGearOffset == 0 ? "WARN" : "Debug") << "Current Gear Offset: " << currentGearOffset;

                topGearOffset = address == 0 ? 0 : *(int*)(address + 3) + 6;
                LOG_TAG(topGearOffset == 0 ? "WARN" : "Debug") << "Top Gear Offset: " << topGearOffset;

                gearRatiosOffset = address == 0 ? 0 : *(int*)(address + 3) + 8;
                LOG_TAG(gearRatiosOffset == 0 ? "WARN" : "Debug") << "Gear Ratios Offset: " << gearRatiosOffset;
            }



            {//Wheels
                address = FindPattern("\x0F\xBA\xAB\xEC\x01\x00\x00\x09\x0F\x2F\xB3\x40\x01\x00\x00\x48\x8B\x83\x20\x01\x00\x00", "xx?????xxx???xxxx?????");
                wheelSteerMultOffset = address == 0 ? 0 : *(int*)(address + 11);
                LOG_TAG(wheelSteerMultOffset == 0 ? "WARN" : "Debug") << "Wheel Steering Multiplier Offset: " << wheelSteerMultOffset;

                wheelPowerOffset = address == 0 ? 0 : *(int*)(address + 6) + 0x08;
                LOG_TAG(wheelPowerOffset == 0 ? "WARN" : "Debug") << "Wheel Power Offset: " << wheelPowerOffset;

                address = FindPattern("\x0F\x29\x7C\x24\x30\x0F\x85\xE3\x00\x00\x00\xF3\x0F\x10\xB9\x68\x09\x00\x00", "xx???xx????xxxx????");
                wheelBrakeOffset = address == 0 ? 0 : *(int*)(address + 0xF);
                LOG_TAG(wheelBrakeOffset == 0 ? "WARN" : "Debug") << "Wheel Brake Offset: " << wheelBrakeOffset;

                address = FindPattern("\x3B\xB7\x48\x0B\x00\x00\x7D\x0D", "xx????xx");
                wheelsPtrOffset = address == 0 ? 0 : *(int*)(address + 2) - 8;
                LOG_TAG(wheelsPtrOffset == 0 ? "WARN" : "Debug") << "Wheels Pointer Offset: " << wheelsPtrOffset;
                numWheelsOffset = address == 0 ? 0 : *(int*)(address + 2);
                LOG_TAG(numWheelsOffset == 0 ? "WARN" : "Debug") << "Number of Wheels Offset: " << numWheelsOffset;


            }

            {//misc

                address = FindPattern("\xF3\x0F\x11\x9B\xDC\x09\x00\x00\x0F\x84\xB1\x00\x00\x00", "xxxx????xxx???");
                engineTempOffset = address == 0 ? 0 : *(int*)(address + 4);
                LOG_TAG(engineTempOffset == 0 ? "WARN" : "Debug") << "Engine Temperature Offset: " << engineTempOffset;

                address = FindPattern("\xF3\x0F\x10\x8F\x10\x0A\x00\x00\xF3\x0F\x59\x05\x5E\x30\x8D\x00", "xxxx????xxxx????");
                dashSpeedOffset = address == 0 ? 0 : *(int*)(address + 4);
                LOG_TAG(dashSpeedOffset == 0 ? "WARN" : "Debug") << "Dashboard Speed Offset: " << dashSpeedOffset;

            }


            {//GFX
                address = FindPattern("4C 8D 48 ? 80 E1 01");
                StreamRenderGfxPtrOffset = address == 0 ? 0 : *(uint32_t*)(address - 4);
                LOG_TAG(StreamRenderGfxPtrOffset == 0 ? "WARN" : "Debug") << "StreamRenderGfxPtrOffset: " << StreamRenderGfxPtrOffset;

                address = FindPattern("44 0F 2F 43 48 45 8D");
                DrawHandlerPtrOffset = address == 0 ? 0 : *(uint8_t*)(address + 4);
                LOG_TAG(DrawHandlerPtrOffset == 0 ? "WARN" : "Debug") << "DrawHandlerPtrOffset: ", DrawHandlerPtrOffset;

                address = FindPattern("48 89 01 B8 00 00 80 3F 66 44 89 51");
                StreamRenderWheelWidthOffset = address == 0 ? 0 : *(uint32_t*)(address + 23);
                LOG_TAG(StreamRenderWheelWidthOffset == 0 ? "WARN" : "Debug") << "StreamRenderWheelWidthOffset: " << StreamRenderWheelWidthOffset;

                StreamRenderWheelSizeOffset = address == 0 ? 0 : *(uint8_t*)(address + 20);
                LOG_TAG(StreamRenderWheelSizeOffset == 0 ? "WARN" : "Debug") << "StreamRenderWheelSizeOffset: " << StreamRenderWheelSizeOffset;
            }


        }

    }
}
