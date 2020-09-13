// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn) {

	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);
		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		

		TArray<AActor*> returnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, returnedActors);

		AActor* NewViewTarget;
		if (returnedActors.Num() > 0) { 
			
			NewViewTarget = returnedActors[0]; 

			if (PC) {
				PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}	
		}	
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay nuevo cv"));
		}
	}
	
	

	OnMissionCompleted(InstigatorPawn);
}
