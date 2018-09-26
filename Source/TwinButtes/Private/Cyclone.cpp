
// Fill out your copyright notice in the Description page of Project Settings.

#include "Cyclone.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Character.h"


// Sets default values
ACyclone::ACyclone()
	: Angle{ 0 }, CircleRadius{ 5.f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionSphere->InitSphereRadius(200.f);
	RootComponent = CollisionSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Assets/Cyclone.Cyclone"));
	if (MeshAsset.Succeeded())
		Mesh->SetStaticMesh(MeshAsset.Object);
	Mesh->SetupAttachment(RootComponent);

	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACyclone::OnOverlapBegin);


}

// Called when the game starts or when spawned
void ACyclone::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = UGameplayStatics::GetPlayerCharacter(this, 0);
}

// Called every frame
void ACyclone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!PlayerRef)
		PlayerRef = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (GetDistanceTo(PlayerRef) <= 1000.f)
	{
		FVector NewLocation = GetActorLocation() - PlayerRef->GetActorLocation();

		if (NewLocation.Normalize())
			NewLocation = (NewLocation * DeltaTime) * -200.f;
		NewLocation += GetActorLocation();

		SetActorLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FVector(GetActorLocation().X + FMath::Cos(Angle * (PI/180)) * CircleRadius, GetActorLocation().Y + FMath::Sin(Angle * (PI / 180)) * CircleRadius, GetActorLocation().Z);
		SetActorLocation(NewLocation);
		Angle = (Angle + 1) % 360;
	}

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 750.f * DeltaTime;

	SetActorRotation(NewRotation);

}

void ACyclone::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && PlayerRef)
	{
		if (Cast<ACharacter>(OtherActor) == PlayerRef)
		{
			PlayerRef->LaunchCharacter((GetActorForwardVector() + (GetActorUpVector()*-1)) * -1000, true, true);
		}
	}
}

