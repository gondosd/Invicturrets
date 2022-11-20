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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayMusic();

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString InPlayerName);

	UFUNCTION(BlueprintCallable)
	FString GetPlayerName() const;


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	USoundBase* Music;

	UPROPERTY(BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	UAudioComponent* MySoundComponent;

	FString PlayerName;
};
