// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnBasedCharacter.h"
#include "EnemyBaseChar.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTDESCENT_API AEnemyBaseChar : public ATurnBasedCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 minAPReq;

	UPROPERTY(BlueprintReadWrite)
	int32 maxAccSpend;

	UPROPERTY(BlueprintReadWrite)
	int32 numAttacks;

protected:

	void StatsStructInitializer();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TurnIntent(ATurnBasedCharacter* targetToHit);

	int32 Attack(ATurnBasedCharacter* targetToHit, bool calculated = false);
	
};
