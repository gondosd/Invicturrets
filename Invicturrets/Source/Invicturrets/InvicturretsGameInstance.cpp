// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicturretsGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UInvicturretsGameInstance::SetPlayerName(FString InPlayerName)
{
    PlayerName = InPlayerName;
}

FString UInvicturretsGameInstance::GetPlayerName() const
{
    return PlayerName;
}

/*
# The CreateSound2D function seems to work differently in C++ as in blueprints. So implementation is moved to blueprints.
#
# tried code:

void UInvicturretsGameInstance::PlayMusic()
{
    UE_LOG(LogTemp, Error, TEXT("try start"));
    if(!Music )
    {
        return;
    }
    
    if(!MySoundComponent)
    {
        
        MySoundComponent = UGameplayStatics::CreateSound2D(GetWorld(), Music, 1.f, 1.f, 0.0f, nullptr, true, true);
            
        //MySoundComponent->Play(0.f);
    }
    
}*/