#pragma once

#include "ServerApi/FProject.h"
#include "ServerApi/FBranch.h"

struct FConnectGameDataParameters
{
public:
	TSharedRef<FProject> Project;
	TSharedRef<FBranch> Branch;
	FString ApiKey;
	FString ServerAddress;
	int32 InitialSyncDirection; // 1 -> Upload, -1 Download
};
