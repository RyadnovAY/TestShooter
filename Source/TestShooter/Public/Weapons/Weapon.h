// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/WeaponsEnum.h"
#include "Weapon.generated.h"

UCLASS()
class TESTSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()

	
public:	

	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TEnumAsByte<E_WeaponType> WeaponType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The amount of ammunition in a weapon clip (or in the hands)
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int CurrentAmmo;

	//The amount of ammunition for this weapon the player has
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int TotalAmmo;

	//How often we can use this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float UseRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool UseFreezedByRate;

	//Is autofire mode ON
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool Autofire;

	//Is there a shooting going on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool FireActive;

	//Damage amount for this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float Damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Is weapon able to use
	virtual bool AbleToUse();

	//Sets "UseFreezedByRate = false" so we can use weapon again
	virtual void StopRateDelay();

	//Returns properties that are replicated for the lifetime of the actor channel
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Use current weapon
	UFUNCTION(BlueprintCallable)
		virtual bool UseWeapon();

	//Stop shooting for weapon with autofire
	UFUNCTION(BlueprintCallable)
		void StopUseWeapon();
};
