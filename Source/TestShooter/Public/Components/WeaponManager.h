// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestShooter/TestShooterCharacter.h"
#include "Weapons/Weapon.h"
#include "WeaponManager.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

UCLASS(Blueprintable)
class TESTSHOOTER_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UWeaponManager();

	/*Who owns the weapon*/
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		ATestShooterCharacter* OwnerCharacter;

	/*Player's main weapon (like a rifle or a shotgun)*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AWeapon* MainWeapon;

	/*Player's secondary weapon (like a gun)*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AWeapon* SecondaryWeapon;

	/*Player's melee weapon (like a knife)*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AWeapon* MeleeWeapon;

	/*Player's special stuff (like a turret or first aid kit)*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TArray<AWeapon*> Specials;

	/*Player's grenades*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TArray<AWeapon*> Grenades;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon, BlueprintReadWrite, Category = Weapon)
		AWeapon* CurrentWeapon;

	// Spawns Weapon Actor and returns pointer to it
	UFUNCTION(BlueprintCallable)
		AWeapon* CreateWeapon(TSubclassOf<AWeapon> AWeaponClass);

	UFUNCTION()
		virtual void OnRep_CurrentWeapon();
	 

	//UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	//	TSubclassOf<AWeapon> AWeaponClass;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
