// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_EnemyExecution_Base.h"
#include "BTTask_Enemy_LaunchAttack.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTTask_Enemy_LaunchAttack : public UBTTask_EnemyExecution_Base
{
	GENERATED_BODY()
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= ValueToReadFromBB)
	FBlackboardKeySelector BBKey_PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= PropertySetting)
	float PlayerAndLandPosOffset = 125;
	
};
