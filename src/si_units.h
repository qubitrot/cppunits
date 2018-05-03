#pragma once

#include "units.h"

UNIT_SYSTEM(SI_Units);

using Meters    = SI_Units<double, Dim_Length>;
using Seconds   = SI_Units<double, Dim_Time>;
using Kilograms = SI_Units<double, Dim_Mass>;
using Ampere    = SI_Units<double, Dim_Current>;
using Kelvin    = SI_Units<double, Dim_Temperature>;
using Mole      = SI_Units<double, Dim_Amount>;
using Candela   = SI_Units<double, Dim_Intensity>;
using Radian    = SI_Units<double, Dim_Angle>;


