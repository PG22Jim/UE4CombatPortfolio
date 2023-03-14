// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StraightPosToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTTask_StraightPosToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ValueToStore)
	FBlackboardKeySelector BBKey_CurrentPlayerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ValueToRead)
	FBlackboardKeySelector BBKey_PlayerRef;
};
