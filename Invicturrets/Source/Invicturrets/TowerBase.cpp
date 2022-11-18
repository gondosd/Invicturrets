// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectileBase.h"
#include "EnemyBase.h"
#include "TimerManager.h"

// Sets default values
ATowerBase::ATowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(Root);

	MiddlePart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Part"));
	MiddlePart->SetupAttachment(Base);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Root);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	RotationRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationRoot"));
	RotationRoot->SetupAttachment(Root);

	CannonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Base"));
	CannonBase->SetupAttachment(RotationRoot);

	Cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	Cannon->SetupAttachment(CannonBase);

	FireLoc = CreateDefaultSubobject<USceneComponent>(TEXT("FireLoc"));
	FireLoc->SetupAttachment(Cannon);

	Range = 20.0f;
	ClosestDistance = -1.f;
	ShootFrequency = 0.5f;
	TurretRotationSpeed = 20.f;

	Sphere->SetSphereRadius(Range);
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATowerBase::Shoot, ShootFrequency, true);
	
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ActiveTargetPtr)
		return;

	const float CurrentRotYaw = RotationRoot->GetRelativeRotation().Yaw;

	const FVector TargetLocation = ActiveTargetPtr->GetRootComponent()->GetComponentLocation();
	const float TargetRotYaw = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), TargetLocation).Yaw;

	bool bPointsAtTarget = UKismetMathLibrary::NearlyEqual_FloatFloat(CurrentRotYaw, TargetRotYaw, 1.0f);

	if (bPointsAtTarget)
	{
		AProjectileBase* BulletRef = GetWorld()->SpawnActor<AProjectileBase>(Projectile, FireLoc->GetComponentLocation(), FireLoc->GetComponentRotation());
		BulletRef->Target = ActiveTargetPtr;
		ClosestDistance = -1.f;
		ActiveTargetPtr = NULL;
		
		UE_LOG(LogTemp, Warning, TEXT("Targets"));
	}
	else
	{
		const FRotator NewRotation = UKismetMathLibrary::RInterpTo(FRotator(0.f, CurrentRotYaw, 0.f), FRotator(0.f, TargetRotYaw, 0.f), DeltaTime, TurretRotationSpeed);
		RotationRoot->SetRelativeRotation(NewRotation);
		
	}
}

void ATowerBase::Shoot()
{

	TArray<AActor *> overlappedActors;
	Sphere->GetOverlappingActors(OUT overlappedActors, TSubclassOf<AActor>());

	DrawDebugSphere(GetWorld(), GetActorLocation(), Range, 12, FColor::Red, false, 0.1f);

	for (auto *Actor : overlappedActors)
	{
		if (Actor->IsA(AEnemyBase::StaticClass()))
		{

			float localDist = Actor->GetDistanceTo(this);
			if (localDist <= ClosestDistance || (ClosestDistance == -1.0f))
			{
				ClosestDistance = localDist;
				ActiveTargetPtr = Actor;
			}
		}
	}
}

