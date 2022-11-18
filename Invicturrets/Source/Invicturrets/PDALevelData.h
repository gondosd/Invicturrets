// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDALevelData.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API UPDALevelData : public UPrimaryDataAsset
{
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 EnemyCountOnThisLevel;

	UPROPERTY(EditAnywhere)
	float EnemySpawnFrequency;
	
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<class ARoadTileBase>> Waypoints;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> NextLevel;



	
};
