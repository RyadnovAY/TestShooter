// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "WeaponsEnum.generated.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	Main UMETA(DisplaName="Main Weapon"),
	Secondary UMETA(DisplaName = "Secondary Weapon"),
	Special UMETA(DisplaName = "Special Purpouse Weapon"),
	Grenade UMETA(DisplaName = " Grenade"),
	Melee UMETA(DisplaName = "Melee Weapon")
};