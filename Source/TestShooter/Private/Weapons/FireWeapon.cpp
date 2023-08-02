// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FireWeapon.h"
#include "Net/UnrealNetwork.h"
#include "TestShooter/TestShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFireWeapon::AFireWeapon() {

	//Set this actor replicated
	//SetReplicates(true);

	//Sets start ammo parameters and use rate
	ClipSize = 30;
	CurrentAmmo = ClipSize;
	TotalAmmo = 60;
	AmmoToReload = 0;
	ReloadTime = 3.0f;
	Damage = 10.0f;

	UseRate = 0.1;

	//Sets bool variables for starting
	Autofire = true;
	Reloading = false;
}

bool AFireWeapon::UseWeapon()
{
	if (AWeapon::UseWeapon()) {

		if (!FireProjectile->IsValidLowLevel()) {
			FHitResult FireHit = GetFireTrace();

			UGameplayStatics::ApplyPointDamage(FireHit.GetActor(), Damage, UKismetMathLibrary::GetDirectionUnitVector(FireHit.TraceEnd, FireHit.TraceStart), FireHit, 
				GetInstigatorController(), this, nullptr);
		}

		return true;
	} 
	else {
		if ((CurrentAmmo <= 0) && AbleToReload()) {

			//Weapon reload for listening server player ...
			if (GetWorld()->IsServer()) { 
					Reloading = true;
					OnRep_Reloading();
			}
			// for clients
			else {
				 Reloading = true;
			}
		}
		return false;
	}
}

FHitResult AFireWeapon::GetFireTrace()
{
	//Get CameraComponent location for Fire tracing
	FHitResult HitResult;
	ATestShooterCharacter* Shooter = Cast<ATestShooterCharacter>(GetInstigator());
	UCameraComponent* ShooterCamera = Shooter->GetFirstPersonCameraComponent();

	FVector StartPoint = ShooterCamera->GetComponentLocation();
	FVector EndPoint = (ShooterCamera->GetForwardVector()) * 10000.0f + StartPoint;

	//Set Ignore List for collision
	TArray<const AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	IgnoredActors.Add(GetInstigator());

	FCollisionQueryParams Params;
	Params.AddIgnoredActors(IgnoredActors);

	//Set Objects for which a collision is possible
	FCollisionObjectQueryParams ObjectsToCollision;
	ObjectsToCollision.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectsToCollision.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectsToCollision.AddObjectTypesToQuery(ECC_Pawn);

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectsToCollision, Params)) {

		DebugDrawTrace(HitResult.TraceStart, HitResult.TraceEnd, HitResult.ImpactPoint);
	}

	return HitResult;
}

void AFireWeapon::OnRep_Reloading()
{
	if (HasAuthority()) {
		if (Reloading) {
				
				//Ammo quantity for reloading
				AmmoToReload = FMath::Min((ClipSize - CurrentAmmo), TotalAmmo);

				//Delay for reloading weapon
				FTimerHandle ReloadTimer;
				GetWorldTimerManager().SetTimer(ReloadTimer, this, &AFireWeapon::ReloadFinished, ReloadTime, false, -1.0f);

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Reloading on Server"));
		}
	}
	else {
		if (Reloading) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Reloading on Client")); }
	}
}

bool AFireWeapon::AbleToReload()
{
	return !Reloading && (CurrentAmmo < ClipSize) && (TotalAmmo > 0);
}

void AFireWeapon::ReloadFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Reload Finished"));
	CurrentAmmo += AmmoToReload;
	TotalAmmo -= AmmoToReload;

	Reloading = false;
}

bool AFireWeapon::AbleToUse()
{
	return AWeapon::AbleToUse() && !Reloading;
}

void AFireWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFireWeapon, TotalAmmo, COND_OwnerOnly);
	DOREPLIFETIME(AFireWeapon, Reloading);
}

void AFireWeapon::DebugDrawTrace(FVector Start, FVector End, FVector Hit)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 5.0f, 0U, 2.0f);
	DrawDebugSphere(GetWorld(), Hit, 40.0f, 8, FColor::Red, false, 5.0f, 0U, 2.0f);
}

