// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InvicturretsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API UInvicturretsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	void PlayMusic();
};
