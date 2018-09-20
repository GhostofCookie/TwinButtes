// Fill out your copyright notice in the Description page of Project Settings.

#include "CampStart.h"
#include "ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "BaseCharacter.h"
#include "CloudGameInstance.h"


// Sets default values
ACampStart::ACampStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(300.0f);
	CollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = CollisionSphere;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	Fire->SetupAttachment(MeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT(
		"/Game/Assets/CampFire_proto.CampFire_proto"));
	if (MeshAsset.Succeeded())
		MeshComponent->SetStaticMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireAsset(TEXT(
		"/Game/Particles/P_Smoke.P_Smoke"));
	if (FireAsset.Succeeded())
		Fire->SetTemplate(FireAsset.Object);

	bShowInstructions = false;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACampStart::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ACampStart::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACampStart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACampStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACampStart::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && Cast<ABaseCharacter>(OtherActor))
	{
		FStringAssetReference FireAsset(TEXT("/Game/Particles/P_Fire.P_Fire"));
		Fire->SetTemplate(Cast<UParticleSystem>(FireAsset.TryLoad()));

		if(bShowInstructions)
			Cast<UCloudGameInstance>(GetGameInstance())->ShowInstructions();
		Cast<UCloudGameInstance>(GetGameInstance())->SetCheckpoint(OtherActor->GetActorTransform());
	}
}

void ACampStart::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FStringAssetReference FireAsset(TEXT("/Game/Particles/P_Smoke.P_Smoke"));
	Fire->SetTemplate(Cast<UParticleSystem>(FireAsset.TryLoad()));
	
	if (bShowInstructions)
		Cast<UCloudGameInstance>(GetGameInstance())->ShowInstructions();
}

