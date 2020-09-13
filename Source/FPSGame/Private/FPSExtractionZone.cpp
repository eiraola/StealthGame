// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "FPSExtractionZone.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "FPSGameMode.h"
#include "FPSCharacter.h"
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));

	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;
	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	UE_LOG(LogTemp, Log, TEXT("Overlap with extraction zone!"));
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (MyPawn && MyPawn->bIsCarryngObjetive) {

		AFPSGameMode* GM = Cast<AFPSGameMode>( GetWorld()->GetAuthGameMode());

		if (GM) {
			UE_LOG(LogTemp, Log, TEXT("Overlap with extraction zone!"));
			GM->CompleteMission(MyPawn);
		}

	}
	if (MyPawn && !MyPawn->bIsCarryngObjetive) { UE_LOG(LogTemp, Log, TEXT("Nigga!")); }

}