// Fill out your copyright notice in the Description page of Project Settings.

#include "FlagGoal.h"
#include "Components/SphereComponent.h"
#include "Animation/AnimSequence.h"
#include "CloudGameInstance.h"
#include "ConstructorHelpers.h"
#include "BaseCharacter.h"
#include "Engine/Engine.h"


// Sets default values
AFlagGoal::AFlagGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionSphere->InitSphereRadius(300.f);
	RootComponent = CollisionSphere;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/FlagAnimation.FlagAnimation"));
	if (MeshAsset.Succeeded())
		Mesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimAsset(TEXT("/Game/Assets/FlagAnimation_Anim.FlagAnimation_Anim"));
	if (AnimAsset.Succeeded())
		FlagAnim = AnimAsset.Object;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFlagGoal::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFlagGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlagGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlagGoal::PlantFlag()
{
}

void AFlagGoal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<ABaseCharacter>(OtherActor))
	{
		if(FlagAnim) Mesh->PlayAnimation(FlagAnim, false);
		Cast<UCloudGameInstance>(GetGameInstance())->bGameOver = true;
	}
}

