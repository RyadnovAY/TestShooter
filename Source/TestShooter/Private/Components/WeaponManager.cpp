// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManager.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	OwnerCharacter = nullptr;

	//Allow Replication
	SetIsReplicated(true);
}

AWeapon* UWeaponManager::CreateWeapon(TSubclassOf<AWeapon> AWeaponClass)
{
	if (IsValid(AWeaponClass)) {

		UWorld* OpenLevel = GetWorld();

		if (IsValid(OpenLevel)) {

			if(GetWorld()->IsServer()){

				FActorSpawnParameters SpawnParam;

				/*Set Invistigator, Owner and CollisionCheck*/
				SpawnParam.Instigator = OwnerCharacter;
				SpawnParam.Owner = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				AWeapon* LocalWeapon = OpenLevel->SpawnActor<AWeapon>(AWeaponClass, SpawnParam);

				/*Assign weapons depending on the type*/
				switch (LocalWeapon->WeaponType)
				{
				case E_WeaponType::Main:
					MainWeapon = LocalWeapon;
					break;

				case E_WeaponType::Secondary:
					SecondaryWeapon = LocalWeapon;
					break;

				case E_WeaponType::Melee:
					MeleeWeapon = LocalWeapon;
					break;

				case E_WeaponType::Special:
					Specials.Add(LocalWeapon);
					break;

				case E_WeaponType::Grenade:
					Grenades.Add(LocalWeapon);
					break;
				}

				/*Attach Weapon to Owner Player*/
				FAttachmentTransformRules WeaponAttachmentRules(EAttachmentRule::KeepRelative, true);
				LocalWeapon->AttachToComponent(OwnerCharacter->GetVisibleMesh(), WeaponAttachmentRules, FName("weapon_skt"));

				return LocalWeapon;
			}

		}
	}
	return nullptr;
}

void UWeaponManager::OnRep_CurrentWeapon()
{
	/*Attach Weapon to socket depending on visible mesh*/
	FAttachmentTransformRules WeaponAttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentWeapon->AttachToComponent(OwnerCharacter->GetVisibleMesh(), WeaponAttachmentRules, FName("weapon_skt"));
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	/*Get Owner Character Reference*/

	OwnerCharacter = Cast<ATestShooterCharacter>(GetOwner());
	
}


// Called every frame
//void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

//Returns properties that are replicated for the lifetime of the actor channel
void UWeaponManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponManager, OwnerCharacter);
	DOREPLIFETIME(UWeaponManager, MainWeapon);
	DOREPLIFETIME(UWeaponManager, SecondaryWeapon);
	DOREPLIFETIME(UWeaponManager, MeleeWeapon);
	DOREPLIFETIME(UWeaponManager, Specials);
	DOREPLIFETIME(UWeaponManager, Grenades);
	DOREPLIFETIME(UWeaponManager, CurrentWeapon);
}