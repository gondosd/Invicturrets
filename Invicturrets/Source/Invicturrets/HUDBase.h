// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API AHUDBase : public AHUD
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

private:

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHUDWidget> HUDWidgetType;

};
