// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu/StartMenuUserWidget.h"
#include "Components/Button.h"
#include "TestShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UStartMenuUserWidget::Initialize()
{
	Super::Initialize();

	/*Define actions for Buttons*/

	CreateServer->OnReleased.AddDynamic(this, &UStartMenuUserWidget::CreateServerPressed);
	JoinGame->OnReleased.AddDynamic(this, &UStartMenuUserWidget::JoinGamePressed);
	Quit->OnReleased.AddDynamic(this, &UStartMenuUserWidget::QuitPressed);

	return true;
}

void UStartMenuUserWidget::CreateServerPressed()
{
	/*Create Listening Server and change InputeMode*/

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("FirstPersonExampleMap"), true, TEXT("listen"));

	UTestShooterGameInstance* GameInstanceRef = Cast<UTestShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstanceRef->SetMainGameplayInput();
}

void UStartMenuUserWidget::JoinGamePressed()
{
	/*Connecting to the created server by IP address*/

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1"), true, TEXT(""));

	UTestShooterGameInstance* GameInstanceRef = Cast<UTestShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstanceRef->SetMainGameplayInput();
}

void UStartMenuUserWidget::QuitPressed()
{
	/*Quit Game*/

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
