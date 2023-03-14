// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Enemy_DecideAttackAction.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_Enemy_DecideAttackAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if(BlackBoard == nullptr) return EBTNodeResult::Failed;

	const int32 RndIndex = UKismetMathLibrary::RandomIntegerInRange(0,1);
	
	BlackBoard->SetValueAsEnum(BBKey_ActionTypeToOverwrite.SelectedKeyName, RndIndex);
	
	return EBTNodeResult::Succeeded;
}


