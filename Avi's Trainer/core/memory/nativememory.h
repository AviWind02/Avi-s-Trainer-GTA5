#pragma once
namespace core::memory {
    namespace nativememory {

        inline uintptr_t(*GetAddressOfEntity)(int entity) = nullptr;
        inline std::uint64_t(*GetModelInfo)(unsigned int modelHash, int* index) = nullptr;

        inline std::uint64_t getModelInfo{};

        // Gear offsets
        inline int nextGearOffset{ 0 };
        inline int currentGearOffset{ 0 };
        inline int topGearOffset{ 0 };
        inline int gearRatiosOffset{ 0 };

        // Gravity offset
        inline float* gravityOffsetWrite{ 0 };
        inline float* gravityOffsetRead{ 0 };

        // Wheel offsets
        inline int wheelSteerMultOffset{ 0 };
        inline int wheelPowerOffset{ 0 };
        inline int wheelBrakeOffset{ 0 };

        // Miscellaneous Vehicle offsets
        inline int engineTempOffset{ 0 };
        inline int dashSpeedOffset{ 0 };
        inline int wheelsPtrOffset{ 0 };
        inline int numWheelsOffset{ 0 };
        inline int modelTypeOffset{ 0 };

        void InitOffsets();
    }
}
