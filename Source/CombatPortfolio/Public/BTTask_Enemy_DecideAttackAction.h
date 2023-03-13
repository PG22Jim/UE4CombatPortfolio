// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Enemy_DecideAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTTask_Enemy_DecideAttackAction : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AttackActionType)
	FBlackboardKeySelector BBKey_ActionTypeToOverwrite;
	
};
