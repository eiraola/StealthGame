// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "BlackHole.h"
#include "Components/PrimitiveComponent.h"
// Sets default values
ABlackHole::ABlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetSphereRadius(100);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	SphereComp->SetupAttachment(MeshComp);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetupAttachment(MeshComp);
	OuterSphereComp->SetSphereRadius(3000);

	OuterSphereComp->SetupAttachment(MeshComp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();


	//

}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> Components;
	OuterSphereComp->GetOverlappingComponents(Components);

	for (int32 i = 0; i < Components.Num(); i++)
	{
		UPrimitiveComponent* StaticMeshComponent = Components[i];
		if (StaticMeshComponent && StaticMeshComponent->IsSimulatingPhysics())
		{
			const float Sphereradius = OuterSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000;
			//StaticMeshComponent->AddForce(this->GetActorLocation());
			StaticMeshComponent->AddRadialForce(GetActorLocation(), Sphereradius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
		//UPrimitiveComponent* StaticMesh = StaticMeshComponent->GetStaticMesh();
		

	}

}

/*void ABlackHole::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	TArray<UPrimitiveComponent*> Components;
	OtherActor->GetComponents<UPrimitiveComponent>(Components);

	for (int32 i = 0; i < Components.Num(); i++)
	{
		UPrimitiveComponent* StaticMeshComponent = Components[i];
		UPrimitiveComponent* StaticMesh = StaticMeshComponent->GetStaticMesh();
		StaticMeshComponent->AddForce(this->GetActorLocation());

	}


}*/



void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor) {
	
		OtherActor->Destroy();
	}
}