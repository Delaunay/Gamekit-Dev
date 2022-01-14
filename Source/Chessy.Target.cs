using UnrealBuildTool;
using System.Collections.Generic;

public class ChessyTarget : TargetRules
{
	public ChessyTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"Gamekit", "Chessy"});
	}
}
