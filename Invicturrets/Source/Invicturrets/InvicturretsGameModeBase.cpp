// Copyright Epic Games, Inc. All Rights Reserved.


#include "InvicturretsGameModeBase.h"
#include "PDALevelData.h"
#include "Kismet/GameplayStatics.h"
#include "HUDBase.h"
#include "InvicturretsGameInstance.h"
#include "Engine/StreamableManager.h"
#include "RoadTileBase.h"
#include "EnemyBase.h"
#include "UObject/SoftObjectPtr.h"

void AInvicturretsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    
    InvicturretsHUDRef = Cast<AHUDBase> (UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
    //Cast<UInvicturretsGameInstance>(GetGameInstance())->PlayMusic();

    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AInvicturretsGameModeBase::TimerElapsed, InitialSpawnDelay, false);
	
}

void AInvicturretsGameModeBase::EnemyKilled()
{
    KillCount++;
    OnEnemyKilled.Broadcast(KillCount);
    

    if(KillCount>= LevelData->EnemyCountOnThisLevel)
    {
        GameWon();
    }
}

void AInvicturretsGameModeBase::GameWon()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("YOU WON!"));

    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

    if(!LevelData->NextLevel.IsNull())
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelData->NextLevel);
    }else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("No more maps"));
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
    }
}

void AInvicturretsGameModeBase::GameOver()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("GAME OVER"));
    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

    if(!MenuLevel.IsNull())
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
    }
}

int32 AInvicturretsGameModeBase::GetLevelsEnemyCount() const
{
    return LevelData->EnemyCountOnThisLevel;
}

void AInvicturretsGameModeBase::SpawnEnemy()
{
    if(!LevelData)
    {
        return;
    }
    FStreamableManager AssetLoader;
	AssetLoader.RequestAsyncLoad(LevelData->Waypoints[0].ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInvicturretsGameModeBase::WaypointIsLoaded));
}

void AInvicturretsGameModeBase::WaypointIsLoaded()
{
    if(!LevelData||!EnemyTypeToSpawn)
    {
        return;
    }

    SpawnCount++;

    if(SpawnCount>GetLevelsEnemyCount())
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

    }else
    {

        ARoadTileBase* LoadedWaypoint = LevelData->Waypoints[0].Get();
        
        AEnemyBase* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyTypeToSpawn, LoadedWaypoint->GetTransform());
        SpawnedEnemy->WaypointsSoftRef = LevelData->Waypoints;
    }
}

void AInvicturretsGameModeBase::TimerElapsed()
{

    if(!LevelData)
    {
        return;
    }
    
    SpawnEnemy();
    
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AInvicturretsGameModeBase::SpawnEnemy, LevelData->EnemySpawnFrequency, true);
}
