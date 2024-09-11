#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	CurrentLocation = StartLocation;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() >= MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, CurrentLocation);
}

void AMovingPlatform::InitializePlatform(const FVector& NewStartLocation, float NewMoveDistance, const FVector& NewVelocity, const FRotator& NewRotation)
{
	StartLocation = NewStartLocation;
	MoveDistance = NewMoveDistance;
	PlatformVelocity = NewVelocity;
	RotationVelocity = NewRotation;
}
