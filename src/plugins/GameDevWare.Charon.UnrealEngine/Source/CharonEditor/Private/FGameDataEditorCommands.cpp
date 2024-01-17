#include "FGameDataEditorCommands.h"

#define LOCTEXT_NAMESPACE "GameDataEditorCommands"

void FGameDataEditorCommands::RegisterCommands()
{
	UI_COMMAND(BrowserBack, "Back", "Back to previous page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Left));
	UI_COMMAND(BrowserForward, "Forward", "Forward to next page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Right));
	UI_COMMAND(BrowserReload, "Reload", "Reloads current page in browser.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F5));

	UI_COMMAND(Reimport, "Reimport", "Reimport game data from source file or web.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(GenerateSourceCode, "Generate Source Code", "Regenerate C++ Source for this game data asset.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Connect, "Connect", "Connect this asset to remote game data source (web).", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Disconnect, "Disconnect", "Disconnect this asset from remote game data source (web).", EUserInterfaceActionType::Button, FInputChord());
}
#undef LOCTEXT_NAMESPACE