// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Math/Vector.h"
#include "Damageable.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ProjectileSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Static Mesh"));
	ProjectileSM->SetupAttachment(Root);
	ProjectileSM->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ProjectileSM->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);

	ProjectileSpeed = 5.f;

	Damage = 10.f;
}

void AProjectileBase::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	if (OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_DoDamage(OtherActor, Damage);
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target && !Target->IsPendingKill())
	{
		
		//IDamageable::Execute_DoDamage(Target, Damage);

		FVector CurrentLoc = GetActorLocation();

		FVector TargetLoc = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, CurrentLoc.Z);

		Root->SetWorldLocation(UKismetMathLibrary::VInterpTo(CurrentLoc, TargetLoc, DeltaTime, ProjectileSpeed));

	}
	else
	{
		this->Destroy();
	}
}
