// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDBase.h"
#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"

void AHUDBase::BeginPlay()
{
    Super::BeginPlay();

    if(!HUDWidgetType)
    {
        return;
    }

    UHUDWidget* WidgetRef = Cast<UHUDWidget>(CreateWidget(GetWorld(), HUDWidgetType));
    WidgetRef->AddToViewport();

}