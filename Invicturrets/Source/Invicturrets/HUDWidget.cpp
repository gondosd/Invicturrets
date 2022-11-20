// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InvicturretsGameModeBase.h"
#include "InvicturretsGameInstance.h"
#include "Components/TextBlock.h"

void UHUDWidget::NativeConstruct()
{
    
    InvicturretsGMRef = Cast<AInvicturretsGameModeBase>(UGameplayStatics::GetGameMode(this));
    InvicturretsGMRef->OnEnemyKilled.AddDynamic(this, &UHUDWidget::KillCountChanged);
    PlayerNameVartxt->SetText(FText::FromString(Cast<UInvicturretsGameInstance>(UGameplayStatics::GetGameInstance(this))->GetPlayerName()));

    LevelNumVartxt->SetText(FText::FromString(UGameplayStatics::GetCurrentLevelName(this)));
    TargetEnemyCountVartxt->SetText(FText::AsNumber(InvicturretsGMRef->GetLevelsEnemyCount()));

}

void UHUDWidget::KillCountChanged(int32 NewKillCount)
{
    KilledEnemyCountVartxt->SetText(FText::AsNumber(NewKillCount));
}