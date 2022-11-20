// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvicturretsGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyKilledSignature, int32, NewKillCount);

UCLASS()
class INVICTURRETS_API AInvicturretsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UPDALevelData* LevelData;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 KillCount;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 SpawnCount;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float InitialSpawnDelay = 2.f;
	
	FTimerHandle SpawnTimerHandle;

	class AHUDBase* InvicturretsHUDRef;


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EnemyKilled();

	UFUNCTION(BlueprintCallable)
	void GameWon();	

	UFUNCTION(BlueprintCallable)
	void GameOver();	

	UFUNCTION(BlueprintCallable)
	int32 GetLevelsEnemyCount() const;	

	UPROPERTY(BlueprintAssignable)
	FEnemyKilledSignature OnEnemyKilled;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBase> EnemyTypeToSpawn ;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UWorld> MenuLevel;

	void SpawnEnemy();

	void WaypointIsLoaded();

	void TimerElapsed();


};
