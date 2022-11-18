// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "InvicturretsGameModeBase.h"
#include "Containers/Array.h"
#include "Engine/StreamableManager.h"
#include "UObject/SoftObjectPtr.h"
#include "RoadTileBase.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Static Mesh"));
	EnemyMesh->SetupAttachment(Root);

	WaypointIndex = 0;
	Movespeed = 5.f; 
	NextWaypointCoord = FVector(0.f, 0.f, 0.f);
	MaxHealth = 100.f;
	CurrentHealth = 0.f;


}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	InvicturretGMRef = Cast<AInvicturretsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentHealth = MaxHealth;
	MoveToNextWaypoint();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLoc = this->GetActorLocation();

	if(NextWaypointCoord.Equals(CurrentLoc, 0.f))
	{
		MoveToNextWaypoint();
	}else
	{
		Root->SetWorldLocation(UKismetMathLibrary::VInterpTo_Constant(CurrentLoc, NextWaypointCoord, DeltaTime, Movespeed));
	}
	
}

void AEnemyBase::DoDamage_Implementation(float Damage)
{
	CurrentHealth-=Damage;

	if(CurrentHealth<= 0.f)
	{
	
		InvicturretGMRef->EnemyKilled();

		this->Destroy();
	}

}

void AEnemyBase::MoveToNextWaypoint()
{
	WaypointIndex++;

	if (WaypointsSoftRef.Num()==0)
	{
		//not enough waypoints on this level
		return;
	}
	

	if(WaypointIndex >= WaypointsSoftRef.Num())
	{
		InvicturretGMRef->GameOver();
		return;
	} 

		FStreamableManager AssetLoader;
		AssetLoader.RequestAsyncLoad(WaypointsSoftRef[WaypointIndex].ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AEnemyBase::WaypointIsLoaded));

}

void AEnemyBase::WaypointIsLoaded()
{
	ARoadTileBase* LoadedWaypoint = WaypointsSoftRef[WaypointIndex].Get();

	if(LoadedWaypoint)
	{
		NextWaypointCoord = LoadedWaypoint->GetActorLocation();
	}
}


