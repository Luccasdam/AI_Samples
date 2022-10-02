// Made by Luccas Machado. Feel free to use the code anyway you like!

using UnrealBuildTool;
using System.Collections.Generic;

public class AI_SamplesEditorTarget : TargetRules
{
	public AI_SamplesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "AI_Samples" } );
	}
}
