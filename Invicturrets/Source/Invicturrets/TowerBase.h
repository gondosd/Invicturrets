// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

UCLASS()
class INVICTURRETS_API ATowerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Shoot();

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Base;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MiddlePart;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RotationRoot;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CannonBase;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Cannon;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* FireLoc;

	FTimerHandle TimerHandle;
protected:

	UPROPERTY(EditAnywhere)
	float Range;


	UPROPERTY(VisibleAnywhere)
	float ClosestDistance;

	UPROPERTY(VisibleAnywhere)
	AActor* ActiveTargetPtr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShootFrequency;

	UPROPERTY(VisibleAnywhere)
	float TurretRotationSpeed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectileBase> Projectile;


};
