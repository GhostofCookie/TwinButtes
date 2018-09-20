// Fill out your copyright notice in the Description page of Project Settings.

#include "KillBox.h"
#include "BaseCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AKillBox::AKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Box Collision"));
	CollisionBox->SetBoxExtent(FVector(1000.f, 3000.f, 10.f));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OnOverlapBegin);
//	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AKillBox::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AKillBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillBox::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<ABaseCharacter>(OtherActor))
	{
		Cast<ABaseCharacter>(OtherActor)->AffectHealth(1000.f);
	}
}

void AKillBox::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

