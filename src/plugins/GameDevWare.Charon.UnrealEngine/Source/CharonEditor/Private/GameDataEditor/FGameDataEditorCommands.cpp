#pragma once

#include "FGameDataEditorCommands.h"

#define LOCTEXT_NAMESPACE "GameDataEditorCommands"

void FGameDataEditorCommands::RegisterCommands()
{
	UI_COMMAND(BrowserBack, "Back", "Back to previous page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Left));

	UI_COMMAND(BrowserForward, "Forward", "Forward to next page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Right));
	UI_COMMAND(BrowserReload, "Reload", "Reloads current page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F5));

	UI_COMMAND(GenerateSourceCode, "Generate Source Code", "Regenerate C++ Source for this game data asset.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Reimport, "Reimport", "Reimport this game data asset and update it from an online source if available.", EUserInterfaceActionType::Button, FInputChord());
	
	UI_COMMAND(Connect, "Connect...", "Sync your local game data with online project data.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Disconnect, "Disconnect...", "Stop syncing local and online game data.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Synchronize, "Synchronize", "Update local game data from an online source and then reimport it into your assets.", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(SetApiKey, "Set Api Key...", "Update API Key for a connected game data.", EUserInterfaceActionType::Button, FInputChord());
}
#undef LOCTEXT_NAMESPACE