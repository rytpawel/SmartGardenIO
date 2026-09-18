#include "soil-moisture.calculator.h"

namespace SmartGardenIO::Calculators
{
    uint8_t calculateSoilMoisturePercentage(
        int rawValue,
        int dryValue,
        int wetValue
    ) {
        if (rawValue >= dryValue) {
            return 0;
        }

        if (rawValue <= wetValue) {
            return 100;
        }

        return static_cast<uint8_t>(
            (dryValue - rawValue) * 100L / (dryValue - wetValue)
        );
    }
}