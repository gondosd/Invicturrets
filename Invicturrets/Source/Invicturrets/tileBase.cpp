// Fill out your copyright notice in the Description page of Project Settings.

#include "tileBase.h"
#include "TowerBase.h"

// Sets default values
AtileBase::AtileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile SM"));
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	BaseMesh->OnClicked.AddDynamic(this, &AtileBase::OnClicked);
}

// Called when the game starts or when spawned
void AtileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AtileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AtileBase::OnClicked(UPrimitiveComponent *pComponent, FKey inKey)
{

	if (Tower && !bOccupied)
	{
		GetWorld()->SpawnActor<AActor>(Tower, this->GetActorLocation(), this->GetActorRotation());
		bOccupied = true;
	}
	
}
