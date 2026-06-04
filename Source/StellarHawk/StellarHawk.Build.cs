// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class StellarHawk : ModuleRules
{
	public StellarHawk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore" });

		// Añade esto en el constructor de tu StellarHawk.Build.cs
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Combate"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Core"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ElementosAmbiente"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Enemigos/EnemigosClases"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Enemigos/Factory"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Enemigos/State"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Items"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Items/PowerUps"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Jugador"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Jugador/Mejoras"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "SistemaNiveles"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Enemigos/Strategy"));
    }
}
