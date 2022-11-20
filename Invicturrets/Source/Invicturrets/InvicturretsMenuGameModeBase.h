// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvicturretsMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API AInvicturretsMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> MenuWidgetType;


	
};
