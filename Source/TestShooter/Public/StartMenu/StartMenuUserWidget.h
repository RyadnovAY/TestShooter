// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTSHOOTER_API UStartMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		virtual bool Initialize();

		//UStartMenuUserWidget(const FObjectInitializer& ObjectInitializer);

		/*Define Widget Buttons*/

		UPROPERTY(meta = (BindWidget))
		class UButton* CreateServer;

		UPROPERTY(meta = (BindWidget))
			class UButton* JoinGame;

		UPROPERTY(meta = (BindWidget))
			class UButton* Quit;

		/*Define Functions for Buttons*/

		UFUNCTION()
			void CreateServerPressed();

		UFUNCTION()
			void JoinGamePressed();

		UFUNCTION()
			void QuitPressed();

private:

	//UTestShooterGameInstance* GameInstanceRef;
};
