// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageable.h"
#include "EnemyBase.generated.h"

UCLASS()
class INVICTURRETS_API AEnemyBase : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoDamage(float Damage);

	virtual void DoDamage_Implementation(float Damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (ExposeOnSpawn = "true"))
	TArray<TSoftObjectPtr<class ARoadTileBase>> WaypointsSoftRef;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", Meta = (AllowPrivateAccess = "true"))
	USceneComponent *Root;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *EnemyMesh;

	int32 WaypointIndex;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Movespeed;

	FVector NextWaypointCoord;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	float CurrentHealth;

	class AInvicturretsGameModeBase* InvicturretGMRef;

	void MoveToNextWaypoint();

	void WaypointIsLoaded();
};
