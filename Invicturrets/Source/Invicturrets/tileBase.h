// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tileBase.generated.h"

UCLASS()
class INVICTURRETS_API AtileBase : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AtileBase();

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* pComponent, FKey inKey); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOccupied = false;


private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Combat", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Tower;

};
