// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVICTURRETS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* NameEntryBox;

	
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* LevelEntryBox;

	UFUNCTION()
	void OnLevelEntryBoxChanged(const FText& Text);

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayBtn;

	UFUNCTION()
	void OnPlayButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitBtn;

	UFUNCTION()
	void OnQuitButtonClicked();

	class UInvicturretsGameInstance* InvicturretsGameInstanceRef;

	TArray<FString> Numbers = {"0","1","2","3","4","5","6","7","8","9"};
};
