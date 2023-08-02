// Fill out your copyright notice in the Description page of Project Settings.


#include "TestShooterGameInstance.h"
#include "StartMenu/StartMenuUserWidget.h"
#include "UObject/COnstructorHelpers.h"

UTestShooterGameInstance::UTestShooterGameInstance(const FObjectInitializer& ObjectInitializer) {

	static ConstructorHelpers::FClassFinder<UUserWidget> StartMenuWidget(TEXT("/Game/Blueprints/StartMenu/StartMenuUserWidget_BP"));
	if (!ensure(StartMenuWidget.Class != nullptr)) return;

}

UUserWidget* UTestShooterGameInstance::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	/* Created User Widget and added Widget to vieport */

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(this, WidgetClass);
	NewWidget->AddToViewport();

	/* Get Player Controller */

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	/* Setup input parameters */

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(NewWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);

	PlayerController->bShowMouseCursor = true;

	return NewWidget;
}

void UTestShooterGameInstance::SetMainGameplayInput()
{
	/* Get Player Controller */

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	/* Setup input parameters */

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);

	PlayerController->bShowMouseCursor = false;
}


