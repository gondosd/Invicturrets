// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicturretsMenuGameModeBase.h"
#include "MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InvicturretsGameInstance.h"

void AInvicturretsMenuGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if(!MenuWidgetType)
    {
        return;
    }

    UMenuWidget* WidgetRef = Cast<UMenuWidget>(CreateWidget(GetWorld(), MenuWidgetType));
    WidgetRef->AddToViewport();

    UInvicturretsGameInstance* GameInstanceRef = Cast<UInvicturretsGameInstance>(UGameplayStatics::GetGameInstance(this));
    GameInstanceRef->PlayMusic();
}