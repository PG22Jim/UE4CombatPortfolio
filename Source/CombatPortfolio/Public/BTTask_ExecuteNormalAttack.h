// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ExecuteNormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTTask_ExecuteNormalAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EEnemyAttackType GetAttackTypeThisRound();
	
public:
	
	UFUNCTION()
	void NormalAttackTaskEnd(UBehaviorTreeComponent* OwnerComp);
	
};
