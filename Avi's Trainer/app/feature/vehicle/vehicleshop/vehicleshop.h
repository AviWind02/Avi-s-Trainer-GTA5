#pragma once
namespace feature {
	namespace vehicleshop {
        //Harcode values for some Mainly 11-24
        inline std::string GetVehicleModName(int mod) {
            switch (mod) {
                case VehicleModSpoilers: return "Spoilers";
                case VehicleModFrontBumper: return "Front Bumper";
                case VehicleModRearBumper: return "Rear Bumper";
                case VehicleModSideSkirt: return "Side Skirt";
                case VehicleModExhaust: return "Exhaust";
                case VehicleModFrame: return "Frame";
                case VehicleModGrille: return "Grille";
                case VehicleModHood: return "Hood";
                case VehicleModFender: return "Fender";
                case VehicleModRightFender: return "Right Fender";
                case VehicleModRoof: return "Roof";
                case VehicleModEngine: return "Engine";
                case VehicleModBrakes: return "Brakes";
                case VehicleModTransmission: return "Transmission";
                case VehicleModHorns: return "Horns";
                case VehicleModSuspension: return "Suspension";
                case VehicleModArmor: return "Armor";
                case VehicleModUnknown17: return "Unknown17";
                case VehicleModTurbo: return "Turbo";
                case VehicleModUnknown19: return "Unknown19";
                case VehicleModTireSmoke: return "Tire Smoke";
                case VehicleModUnknown21: return "Unknown21";
                case VehicleModXenonHeadlights: return "Xenon Headlights";
                case VehicleModFrontWheels: return "Front Wheels";
                case VehicleModBackWheels: return "Back Wheels";
                case VehicleModPlateholder: return "Plateholder";
                case VehicleModVanityPlate: return "Vanity Plate";
                case VehicleModTrimDesign: return "Trim Design";
                case VehicleModOrnament: return "Ornament";
                case VehicleModDash: return "Dash";
                case VehicleModDialDesign: return "Dial Design";
                case VehicleModSpeakersDoor: return "Speakers Door";
                case VehicleModLeatherSeats: return "Leather Seats";
                case VehicleModSteeringWheel: return "Steering Wheel";
                case VehicleModColumnShifterLever: return "Column Shifter Lever";
                case VehicleModPlaque: return "Plaque";
                case VehicleModSpeakers: return "Speakers";
                case VehicleModTrunk: return "Trunk";
                case VehicleModHydraulics: return "Hydraulics";
                case VehicleModEngineBlock: return "Engine Block";
                case VehicleModAirFilter: return "Air Filter";
                case VehicleModStruts: return "Struts";
                case VehicleModArchCover: return "Arch Cover";
                case VehicleModAerials: return "Aerials";
                case VehicleModTrim: return "Trim";
                case VehicleModTank: return "Tank";
                case VehicleModWindows: return "Windows";
                case VehicleModUnknown47: return "Unknown47";
                case VehicleModLivery: return "Livery";
                default: return "Invalid Mod";
            }
        }

	

	}
}