#pragma once

#include "EExportMode.generated.h"

UENUM()
enum class EExportMode
{
	Default = 0,
	Publication = 1,
	Localization = 2,
	Extraction = 3
};