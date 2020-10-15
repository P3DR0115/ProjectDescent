// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurnBasedCharacter.generated.h"

UENUM(BlueprintType)
enum ClassArchetype
{
	Rogue	UMETA(DisplayName = "Rogue"),
	Knight	UMETA(DisplayName = "Knight")
};

USTRUCT(BlueprintType)
struct FTurnStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Initiative = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TurnOrder = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Team = 0;
};


USTRUCT(BlueprintType)
struct FStatsStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "TurnVariables")
	FTurnStruct TurnStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthVariables")
	int32 MaxHealthPoints = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthVariables")
	int32 CurrentHealthPoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionPointVariables")
	int32 MaxActionPoints = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionPointVariables")
	int32 CurrentActionPoints = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackVariables")
	int32 Attack = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackVariables")
	int32 AttackAPBaseCost = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackVariables")
	int32 Accuracy = 80;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 Strength = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 Dexterity = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 Intelligence = 5;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 Defense = 2; // The minimum Armor you get for defending
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 DefendAPBaseCost = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatVariables")
	int32 Armor = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActVariables")
	bool bCanAct = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActVariables")
	bool bHasActed = false;
};


USTRUCT(BlueprintType)
struct FModStruct
{
	GENERATED_BODY()

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 StrengthMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 DexterityMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 IntelligenceMod = 0;*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModVariables")
	int32 AttackMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModVariables")
	int32 AccuracyMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModVariables")
	int32 ArmorMod = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 AttackModIncrement = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 AccuracyModIncrement = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModVariables")
	int32 ArmorModIncrement = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModVariables")
	int32 APSpentThisAction = 0;
};


UCLASS(Blueprintable)
class PROJECTDESCENT_API ATurnBasedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurnBasedCharacter();
	//UPROPERTY(BlueprintReadWrite, Category = "StatVariables")
	//FStatsStruct StatsStruct = _StatsStruct;
	UPROPERTY(BlueprintReadOnly, Category = "ClassArchetype")
	TEnumAsByte<ClassArchetype> ClassName;

	UPROPERTY(BlueprintReadWrite, Category = "StatVariables")
	FStatsStruct StatsStruct;

	UPROPERTY(BlueprintReadWrite, Category = "ModVariables")
	FModStruct ModStruct;
protected:

	/*UPROPERTY(BlueprintReadWrite, Category = "TurnVariables")
	FTurnStruct TurnStruct;*/


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetTurnOrder(int32 order);

public:
	//UFUNCTION(BlueprintCallable, Category = "VariablesGetters")
	//FStatsStruct GetStatsStruct();

	UFUNCTION(BlueprintCallable, Category = "VariablesGetters")
	FTurnStruct GetTurnStruct();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual int32 TakeDamage(int32 damage);

protected:

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void BeginTurn();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual int32 Attack(ATurnBasedCharacter* targetToHit);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual bool Defend();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void SpendAP(int32 choice = -1);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void UnSpendAP(int32 choice = -1);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void CommitAPSpentThisAction(int32 choice);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void EndTurn();

};
