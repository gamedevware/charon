#pragma once

#include "EImportReportDocumentChangeStatus.generated.h"

UENUM()
enum class EImportReportDocumentChangeStatus
{
	Created = 0,
	Updated = 1,
	Deleted = 2,
	Skipped = 3,
	Unchanged = 4,
	Error = 5,
};