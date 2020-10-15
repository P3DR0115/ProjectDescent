// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseChar.h"


void AEnemyBaseChar::StatsStructInitializer()
{
	this->StatsStruct.TurnStruct.Team = 1;
}

void AEnemyBaseChar::TurnIntent(ATurnBasedCharacter* targetToHit)
{
	numAttacks = FMath::RandRange(1, (StatsStruct.CurrentActionPoints / StatsStruct.AttackAPBaseCost));

	minAPReq = StatsStruct.CurrentActionPoints - (StatsStruct.AttackAPBaseCost * numAttacks);

	for (int i = 0; i < numAttacks; i++)
	{
		maxAccSpend = ((100 - StatsStruct.Accuracy) / ModStruct.AccuracyModIncrement);

		if (maxAccSpend <= (StatsStruct.CurrentActionPoints - minAPReq))
			ModStruct.AccuracyMod += FMath::RandRange(0, maxAccSpend);
		else
			ModStruct.AccuracyMod += FMath::RandRange(0, (StatsStruct.CurrentActionPoints - minAPReq));

		ModStruct.AttackMod = FMath::RandRange(0, (minAPReq - ModStruct.AccuracyMod));

		UE_LOG(LogTemp, Warning, TEXT("Enemy attack # %d"), (i + 1))
		UE_LOG(LogTemp, Warning, TEXT("Enemy spent points on accuracy: %d"), ModStruct.AccuracyMod)
		UE_LOG(LogTemp, Warning, TEXT("Enemy spent points on attack: %d"), ModStruct.AttackMod)

		Attack(targetToHit, true);
	}
	
}

int32 AEnemyBaseChar::Attack(ATurnBasedCharacter* targetToHit, bool calculated)
{
	if (!calculated)
		TurnIntent(targetToHit);

	//if (StatsStruct.CurrentActionPoints < (ModStruct.APSpentThisAction + StatsStruct.AttackAPBaseCost))
	//{
	//	// Oh snap, don't have enough to attack
	//	return targetToHit->TakeDamage(0); // 0 damage, attack wasn't executed
	//}
	//else
	{
		int32 hitRoll = FMath::RandRange(0, 100);
		if (hitRoll <= (StatsStruct.Accuracy + ModStruct.AccuracyMod))
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack was played! (Attack Landed)"))
			int32 damage = (StatsStruct.Attack + ModStruct.AttackMod);
			CommitAPSpentThisAction(2);
			return targetToHit->TakeDamage(damage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack was played! (Attack Missed)"))
			CommitAPSpentThisAction(2);
			return targetToHit->TakeDamage(0); // 0 damage, attack missed
		}
	}
}
