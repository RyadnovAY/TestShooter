// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestShooter/TestShooterCharacter.h"
#include "HealthComponent.generated.h"


DECLARE_DELEGATE(FCharDeadDelegate);

UCLASS(Blueprintable)
class TESTSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	/*Who owns the HealthComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		ATestShooterCharacter* OwnerCharacter;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DefaultHealth;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Health)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MaxArmour;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Health)
		float Armour;

	UPROPERTY(ReplicatedUsing = OnRep_IsDead, BlueprintReadOnly, Category = Health)
		bool IsDead;

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		virtual void OnRep_IsDead();

public:

	//Returns properties that are replicated for the lifetime of the actor channel
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FCharDeadDelegate OnCharDead;
};
