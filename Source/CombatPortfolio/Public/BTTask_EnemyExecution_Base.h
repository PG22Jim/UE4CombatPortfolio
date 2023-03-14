// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemyExecution_Base.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTTask_EnemyExecution_Base : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
	void ActionTaskEnd(UBehaviorTreeComponent* OwnerComp) {FinishLatentTask(*OwnerComp,EBTNodeResult::Succeeded);}
};

