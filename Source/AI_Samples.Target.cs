// Made by Luccas Machado. Feel free to use the code anyway you like!

using UnrealBuildTool;
using System.Collections.Generic;

public class AI_SamplesTarget : TargetRules
{
	public AI_SamplesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "AI_Samples" } );
	}
}
