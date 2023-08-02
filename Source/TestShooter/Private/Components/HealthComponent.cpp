// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//Allow Replication
	SetIsReplicated(true);

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

		//Set owner for Health Component
		OwnerCharacter = Cast<ATestShooterCharacter>(GetOwner());

	if (GetWorld()->IsServer()) {

		//Set Health and Armour parameters
		DefaultHealth = 100.0f;
		MaxArmour = 100.0f;
		Health = DefaultHealth;
		Armour = MaxArmour;
		IsDead = false;

		OwnerCharacter->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}


	// ...
	
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0) {
		//Reduce Health Damage based on armor
		float HealthDamage = Damage * (1 - (Armour / 200.0f));

		//Decrease health and armor
		Health = FMath::Clamp(Health - HealthDamage, 0.0f, DefaultHealth);
		Armour = FMath::Clamp(Armour - Damage * 2.0f, 0.0f, MaxArmour);

		//Debug message
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Damage! Armour: %f"), Armour));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Damage! Health: %f"), Health));

		if (Health <= 0) { 

			if (GetWorld()->IsServer() && !IsDead) { OnRep_IsDead(); }
			IsDead = true;
		
		}
	}
}

void UHealthComponent::OnRep_IsDead()
{
	OnCharDead;

	//Disaple Player Input
	OwnerCharacter->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (GetWorld()->IsServer()) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("OH NO, HE IS DEAD!!!"));
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHealthComponent, Health, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UHealthComponent, Armour, COND_OwnerOnly);
	DOREPLIFETIME(UHealthComponent, IsDead);

}
// Called every frame
//void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

