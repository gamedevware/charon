#pragma once

#include "EImportMode.generated.h"

UENUM()
enum class EImportMode
{
	Default = 0,
	CreateAndUpdate = 0,
	Create,
	Update,
	SafeUpdate,
	Replace,
	Delete
};