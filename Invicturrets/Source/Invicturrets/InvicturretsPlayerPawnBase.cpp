// Fill out your copyright notice in the Description page of Project Settings.

#include "InvicturretsPlayerPawnBase.h"

// Sets default values
AInvicturretsPlayerPawnBase::AInvicturretsPlayerPawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AInvicturretsPlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("EEEEEEEEEEEEEEEEE"));
	
}

// Called every frame
void AInvicturretsPlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AInvicturretsPlayerPawnBase::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}



