// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this actor replicated
	SetReplicates(true);

	UseFreezedByRate = false;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::AbleToUse()
{
	return (!UseFreezedByRate && (CurrentAmmo > 0));
}

void AWeapon::StopRateDelay()
{
	UseFreezedByRate = false;
	if (Autofire && FireActive) { UseWeapon(); }
}

bool AWeapon::UseWeapon()
{
	if(AbleToUse()) {
		
		CurrentAmmo--;

		//Delay between shots
		FTimerHandle WeaponTimer;
		GetWorldTimerManager().SetTimer(WeaponTimer, this, &AWeapon::StopRateDelay, UseRate, false, -1.0f);
		UseFreezedByRate = true;

		if (Autofire) { FireActive = true; }

		return true;
	}
	else{
		FireActive = false;
		return false;
	}
}

void AWeapon::StopUseWeapon() 
{
	FireActive = false;
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AWeapon, CurrentAmmo, COND_OwnerOnly);
}
