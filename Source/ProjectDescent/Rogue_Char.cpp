// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue_Char.h"

void ARogue_Char::StatsInitializer()
{
	ClassName = ClassArchetype::Rogue;
	this->StatsStruct.TurnStruct.Initiative = this->StatsStruct.Attack = 7;
}

//int32 ARogue_Char::Attack(ATurnBasedCharacter* targetToHit, int32 ExtraAPToSpend)
//{
//	Super::Attack(targetToHit, ExtraAPToSpend);
//	UE_LOG(LogTemp, Warning, TEXT("Attack was played!"))
//
//	SpendAP(ExtraAPToSpend);
//	//return targetToHit->TakeDamage(this->StatsStruct.Dexterity);
//	return targetToHit->TakeDamage(this->StatsStruct.Attack);
//}