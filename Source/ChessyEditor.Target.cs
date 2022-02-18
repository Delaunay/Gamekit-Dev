using UnrealBuildTool;
using System.Collections.Generic;

public class ChessyEditorTarget : TargetRules
{
	public ChessyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"Gamekit", "Chessy" });
	}
}
