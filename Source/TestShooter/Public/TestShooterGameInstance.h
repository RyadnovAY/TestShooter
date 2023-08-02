// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTSHOOTER_API UTestShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTestShooterGameInstance(const FObjectInitializer& ObjectInitializer);

	//virtual void Init();


	UFUNCTION(BlueprintCallable)
	void SetMainGameplayInput();

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(TSubclassOf<UUserWidget> WidgetClass);
	
};
