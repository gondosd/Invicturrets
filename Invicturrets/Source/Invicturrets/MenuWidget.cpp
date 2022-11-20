// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InvicturretsGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Misc/Paths.h"

void UMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    InvicturretsGameInstanceRef = Cast<UInvicturretsGameInstance>(UGameplayStatics::GetGameInstance(this));

    LevelEntryBox->OnTextChanged.AddDynamic(this, &UMenuWidget::OnLevelEntryBoxChanged);
    PlayBtn->OnClicked.AddDynamic(this, &UMenuWidget::OnPlayButtonClicked);
    QuitBtn->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitButtonClicked);
}

void UMenuWidget::OnLevelEntryBoxChanged(const FText &Text)
{
    FString IncomingTextString = Text.ToString();

    if (!IncomingTextString.IsEmpty())
    {

        TArray<FString> StringArray = UKismetStringLibrary::GetCharacterArrayFromString(IncomingTextString);

        if (!Numbers.Contains(StringArray[StringArray.Num() - 1]))
        {
            LevelEntryBox->SetText(FText::FromString(UKismetStringLibrary::LeftChop(IncomingTextString, 1)));
        }
    }
}

void UMenuWidget::OnPlayButtonClicked()
{
    FText TypedName = NameEntryBox->GetText();
    FString LevelName = LevelEntryBox->GetText().ToString();
    if(LevelName.IsEmpty()|| FCString::Atoi(*LevelName) > 5 || FCString::Atoi(*LevelName) == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("pick an existing level"));
        return;
    }

    if (!TypedName.IsEmpty())
    {
        InvicturretsGameInstanceRef->SetPlayerName(TypedName.ToString());
        FString LevelPrefix = "lvl";
        FName NextLevelName = FName(*LevelPrefix.Append(LevelEntryBox->GetText().ToString()));
        UGameplayStatics::OpenLevel(this, NextLevelName);
        
    }
    else 
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Name field is empty"));
    }


    
}

void UMenuWidget::OnQuitButtonClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}