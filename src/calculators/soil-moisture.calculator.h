#pragma once

#include <stdint.h>

namespace SmartGardenIO::Calculators
{
    uint8_t calculateSoilMoisturePercentage(
        int rawValue,
        int dryValue,
        int wetValue
    );
}