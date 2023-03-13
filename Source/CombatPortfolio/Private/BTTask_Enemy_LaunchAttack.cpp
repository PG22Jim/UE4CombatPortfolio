// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Enemy_LaunchAttack.h"

#include "AIActionInterface.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_Enemy_LaunchAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AActor* OwnerActor = OwnerComp.GetOwner();
	
	if(OwnerActor == nullptr) return EBTNodeResult::Failed;

	const AAIController* AiController = OwnerComp.GetAIOwner();
	if(AiController == nullptr) return EBTNodeResult::Failed;

	ACharacter* AiCharacter = AiController->GetCharacter();
	if(AiCharacter == nullptr) return  EBTNodeResult::Failed;
	
	if(AiCharacter->GetClass()->ImplementsInterface(UAIActionInterface::StaticClass()))
	{
		UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
		if(BlackBoard == nullptr) return EBTNodeResult::Failed;
		
		UObject* PlayerRefObject = BlackBoard->GetValueAsObject(BBKey_PlayerRef.SelectedKeyName);
		if(PlayerRefObject == nullptr) return EBTNodeResult::Failed;

		APlayerCharacter* PlayerCharacterClass = Cast<APlayerCharacter>(PlayerRefObject);
		if(PlayerCharacterClass == nullptr) return EBTNodeResult::Failed;

		const FVector CurrentPlayerPos = PlayerCharacterClass->GetActorLocation();
		
		IAIActionInterface::Execute_AIExecuteLaunchAttack(AiCharacter, this, CurrentPlayerPos);
		
		return EBTNodeResult::InProgress;
	}

	
	return EBTNodeResult::Failed;

}
