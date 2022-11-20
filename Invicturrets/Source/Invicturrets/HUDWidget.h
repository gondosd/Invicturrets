// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNameVartxt;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelNumVartxt;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KilledEnemyCountVartxt;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TargetEnemyCountVartxt;

	class AInvicturretsGameModeBase* InvicturretsGMRef;

	UFUNCTION()
	void KillCountChanged(int32 NewKillCount);
};
