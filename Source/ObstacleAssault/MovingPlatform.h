#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetStartLocation() const { return StartLocation; }
    float GetMoveDistance() const { return MoveDistance; }
	FVector GetPlatformVelocity() const { return PlatformVelocity; }
    FRotator GetRotationVelocity() const { return RotationVelocity; }
	FVector GetCurrentLocation() const { return CurrentLocation; }
    FRotator GetCurrentRotation() const { return CurrentRotation; }


	// For testing
	void InitializePlatform(const FVector& NewStartLocation, float NewMoveDistance, const FVector& NewVelocity, const FRotator& NewRotation);
	
private:
	UPROPERTY(EditAnywhere, Category = "Moving")
	FVector PlatformVelocity = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Moving")
	float MoveDistance = 0.f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationVelocity = FRotator(0,0,0);

	FVector StartLocation = FVector(0, 0, 0);

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformReturn() const;
	float GetDistanceMoved() const;

	FVector CurrentLocation = FVector(0, 0, 0);

	FRotator CurrentRotation = FRotator(0,0,0);
};
