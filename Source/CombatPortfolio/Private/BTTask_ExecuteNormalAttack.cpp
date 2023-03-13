// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ExecuteNormalAttack.h"

#include "AIActionInterface.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_ExecuteNormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		
		// // Decide which attack type
		// EEnemyAttackType ExecutingAttackType = GetAttackTypeThisRound();
		//
		// switch (ExecutingAttackType)
		// {
		// 	case EEnemyAttackType::NormalAttack:
		// 		IAIActionInterface::Execute_AIExecuteNormalAttack(AiCharacter, this);
		// 		break;
		// 	case EEnemyAttackType::LaunchingAttack:
		//
		// 		break;
		// 	default:
		// 		break;
		// }
		
				
		return EBTNodeResult::InProgress;
	}

	
	return EBTNodeResult::Failed;
}

EEnemyAttackType UBTTask_ExecuteNormalAttack::GetAttackTypeThisRound()
{
	const int32 RndInt = UKismetMathLibrary::RandomIntegerInRange(1,2);

	if(RndInt == 2) return EEnemyAttackType::NormalAttack;
	
	return EEnemyAttackType::LaunchingAttack;
}

void UBTTask_ExecuteNormalAttack::NormalAttackTaskEnd(UBehaviorTreeComponent* OwnerComp)
{
	FinishLatentTask(*OwnerComp,EBTNodeResult::Succeeded);
}
