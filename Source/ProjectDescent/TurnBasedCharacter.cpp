// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedCharacter.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATurnBasedCharacter::ATurnBasedCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurnBasedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnBasedCharacter::SetTurnOrder(int32 order)
{
	StatsStruct.TurnStruct.TurnOrder = order;
}

//FStatsStruct ATurnBasedCharacter::GetStatsStruct()
//{
//	return this->StatsStruct;
//}

FTurnStruct ATurnBasedCharacter::GetTurnStruct()
{
	return StatsStruct.TurnStruct;
}

int32 ATurnBasedCharacter::TakeDamage(int32 damage)
{
	if (damage == 0)
		return 0;

	if (damage >= StatsStruct.Armor)
	{
		damage -= StatsStruct.Armor;
		StatsStruct.CurrentHealthPoints -= damage;

		if (StatsStruct.CurrentHealthPoints <= 0)
		{
			Destroy();
		}

		if(StatsStruct.Armor > 0)
			UE_LOG(LogTemp, Warning, TEXT("Reduced Damage Taken Due To Armor" ))
		else
			UE_LOG(LogTemp, Warning, TEXT("Full Damage Taken"))

		StatsStruct.Armor = 0;
		return damage;
	}
	else if (StatsStruct.Armor > damage)
	{
		this->StatsStruct.Armor -= damage;

		UE_LOG(LogTemp, Warning, TEXT("Damage Blocked By Armor"))
		damage = 0;
		return damage;
	}
	

	//UE_LOG(LogTemp, Warning, TEXT("Damage Dealt: "))
	return damage;
}

void ATurnBasedCharacter::BeginTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginTurn was played!!"))
	StatsStruct.CurrentActionPoints = StatsStruct.MaxActionPoints;
	//ModStruct.AttackMod = ModStruct.DexterityMod = ModStruct.IntelligenceMod = ModStruct.ConstitutionMod = 0;
	ModStruct.AccuracyMod = ModStruct.AttackMod = ModStruct.ArmorMod = 0;
	StatsStruct.Armor = 0;

	if(!StatsStruct.bCanAct)
		StatsStruct.bCanAct = true;
	
	StatsStruct.bHasActed = false;
}

int32 ATurnBasedCharacter::Attack(ATurnBasedCharacter* targetToHit)
{
	if (StatsStruct.CurrentActionPoints < (ModStruct.APSpentThisAction + StatsStruct.AttackAPBaseCost))
	{
		// Oh snap, don't have enough to attack
		return targetToHit->TakeDamage(0); // 0 damage, attack wasn't executed
	}
	else
	{
		//return targetToHit->TakeDamage(StatsStruct.Strength);
		int32 hitRoll = FMath::RandRange(0, 100);
		if (hitRoll <= (StatsStruct.Accuracy + ModStruct.AccuracyMod))
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack was played! (Attack Landed)"))
			int32 damage = (StatsStruct.Attack + ModStruct.AttackMod);
			CommitAPSpentThisAction(0);
			return targetToHit->TakeDamage(damage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack was played! (Attack Missed)"))
			CommitAPSpentThisAction(0);
			return targetToHit->TakeDamage(0); // 0 damage, attack missed
		}
	}
}

bool ATurnBasedCharacter::Defend()
{
	if (StatsStruct.CurrentActionPoints < (ModStruct.APSpentThisAction + StatsStruct.DefendAPBaseCost))
	{
		// Oh snap, don't have enough to Defend. Do nothing!
		UE_LOG(LogTemp, Warning, TEXT("Defense was played (BUT NOT ENOUGH AP)!"))
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Defense was played!"))
		StatsStruct.Armor += (StatsStruct.Defense + ModStruct.ArmorMod);
		CommitAPSpentThisAction(1);

		if (StatsStruct.CurrentActionPoints < StatsStruct.AttackAPBaseCost || StatsStruct.CurrentActionPoints < StatsStruct.DefendAPBaseCost)
			return true;

		return false;
	}
}

void ATurnBasedCharacter::SpendAP(int32 choice)
{
	UE_LOG(LogTemp, Warning, TEXT("Spend AP was played!!"))

	//StatsStruct.CurrentActionPoints -= 1;
	switch (choice)
	{
		case -1: // No points spent on additional modifiers
		{
			UE_LOG(LogTemp, Warning, TEXT("However, none spent on extra modifiers, simply attack!!"))
			break;
		}
		case 0: // spent on improving attack hit %
		{
			UE_LOG(LogTemp, Warning, TEXT("AP Spent on enhancing attack accuracy!!"))
			ModStruct.AccuracyMod += ModStruct.AccuracyModIncrement;
			ModStruct.APSpentThisAction += 1;
			break;
		}
		case 1: // Spent on improving attack damage
		{
			UE_LOG(LogTemp, Warning, TEXT("AP Spent on enhancing attack damage!!"))
			ModStruct.AttackMod += ModStruct.AttackModIncrement;
			ModStruct.APSpentThisAction += 1;
			break;
		}
		case 2: // Spent on improving Armor value
		{
			UE_LOG(LogTemp, Warning, TEXT("AP Spent on enhancing Armor value!!"))
			ModStruct.ArmorMod += ModStruct.ArmorModIncrement;
			ModStruct.APSpentThisAction += 1;
			break;
		}
		default: // something went wrong?
		{
			UE_LOG(LogTemp, Warning, TEXT("AP Spent	SOMETHING WENT WRONG!!"))
		}
	}

	if (StatsStruct.CurrentActionPoints <= 0)
	{
		EndTurn();
	}
}

void ATurnBasedCharacter::UnSpendAP(int32 choice)
{
	UE_LOG(LogTemp, Warning, TEXT("UnSpend was played!!"))
	if (ModStruct.APSpentThisAction <= 0)
	{
		choice = -1;
	}
	
	switch (choice)
	{
		case -1: // No points Unspent on additional modifiers
		{
			UE_LOG(LogTemp, Warning, TEXT("However, no points to UnSpend!!"))
			break;
		}
		case 0: // Unspent on improving attack hit %
		{
			UE_LOG(LogTemp, Warning, TEXT("AP unspent on enhancing attack accuracy!!"))
			ModStruct.AccuracyMod -= ModStruct.AccuracyModIncrement;
			ModStruct.APSpentThisAction -= 1;
			break;
		}
		case 1: // Unspent on improving attack damage
		{
			UE_LOG(LogTemp, Warning, TEXT("AP unspent on enhancing attack damage!!"))
			ModStruct.AttackMod -= ModStruct.AttackModIncrement;
			ModStruct.APSpentThisAction -= 1;
			break;
		}
		case 2: // Unspent on improving Armor value
		{
			UE_LOG(LogTemp, Warning, TEXT("AP unspent on enhancing Armor value!!"))
			ModStruct.ArmorMod -= ModStruct.ArmorModIncrement;
			ModStruct.APSpentThisAction -= 1;
			break;
		}
		default: // something went wrong?
		{
			UE_LOG(LogTemp, Warning, TEXT("AP Unspent BUT SOMETHING WENT WRONG!!"))
		}
	}
}

void ATurnBasedCharacter::CommitAPSpentThisAction(int32 choice)
{
	if (choice == 0 || choice == 2)
	{
		StatsStruct.CurrentActionPoints -= (ModStruct.APSpentThisAction + StatsStruct.AttackAPBaseCost);
	}
	
	if (choice == 1 || choice == 2)
	{
		StatsStruct.CurrentActionPoints -= (ModStruct.APSpentThisAction + StatsStruct.DefendAPBaseCost);
	}

	ModStruct.APSpentThisAction = ModStruct.AccuracyMod = ModStruct.AttackMod = ModStruct.ArmorMod = 0;
}

void ATurnBasedCharacter::EndTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("End Turn was played!!"))
	//this->StatsStruct.bCanAct = false;
	StatsStruct.bHasActed = true;
}