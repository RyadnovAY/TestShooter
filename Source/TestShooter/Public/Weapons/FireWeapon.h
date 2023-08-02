// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapons/Projectiles/WeaponProjectile.h"
#include "FireWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TESTSHOOTER_API AFireWeapon : public AWeapon
{
	GENERATED_BODY()

protected:

	//Amount of ammo subtracted from Total Ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponReload)
		int AmmoToReload;

	//Time for ammo reloading
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponReload)
		float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int ClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AWeaponProjectile* FireProjectile;

public:

	//Is reloading going on
	UPROPERTY(ReplicatedUsing = OnRep_Reloading, BlueprintReadWrite, Category = WeaponReload)
		bool Reloading;

public:
	
	AFireWeapon();

	//Sets trace for shot
	FHitResult GetFireTrace();

	//Returns properties that are replicated for the lifetime of the actor channel
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Draws FireTrace for debugging
	void DebugDrawTrace(FVector Start, FVector End, FVector Hit);

	//Use current Fire Weapon
	virtual bool UseWeapon() override;

	//Is weapon able to use
	virtual bool AbleToUse();
	
	void ReloadFinished();

	UFUNCTION(BlueprintCallable)
		void OnRep_Reloading();

	//Is weapon able to reload
	UFUNCTION(BlueprintPure)
		virtual bool AbleToReload();
};
