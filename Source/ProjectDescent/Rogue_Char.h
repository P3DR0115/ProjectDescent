// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnBasedCharacter.h"
#include "Rogue_Char.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTDESCENT_API ARogue_Char : public ATurnBasedCharacter
{
	GENERATED_BODY()
	
protected:
	void StatsInitializer();

	//int32 Attack(ATurnBasedCharacter* targetToHit, int32 ExtraAPToSpend) override;

};
