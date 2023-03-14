// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StraightPosToPlayer.h"

#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_StraightPosToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if(BlackBoard == nullptr) return EBTNodeResult::Failed;

	UObject* PlayerRefObject = BlackBoard->GetValueAsObject(BBKey_PlayerRef.SelectedKeyName);
	if(PlayerRefObject == nullptr) return EBTNodeResult::Failed;

	APlayerCharacter* PlayerCharacterClass = Cast<APlayerCharacter>(PlayerRefObject);
	if(PlayerCharacterClass == nullptr) return EBTNodeResult::Failed;

	const FVector CurrentPlayerPos = PlayerCharacterClass->GetActorLocation();

	BlackBoard->SetValueAsVector(BBKey_CurrentPlayerPosition.SelectedKeyName, CurrentPlayerPos);
	
	return EBTNodeResult::Succeeded;
}
