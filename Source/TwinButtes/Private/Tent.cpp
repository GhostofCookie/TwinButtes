// Fill out your copyright notice in the Description page of Project Settings.

#include "Tent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"


// Sets default values
ATent::ATent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Assets/Tent.Tent"));
	if (MeshAsset.Succeeded())
		Mesh->SetStaticMesh(MeshAsset.Object);

	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collison"));
	Collision->InitBoxExtent(FVector(100.f));
	
	

}

// Called when the game starts or when spawned
void ATent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

