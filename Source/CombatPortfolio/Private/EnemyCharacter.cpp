// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "BTTask_ExecuteNormalAttack.h"
#include "EnemyAIController.h"
#include "Kismet/KismetMathLibrary.h"



void AEnemyCharacter::AIExecuteNormalAttack_Implementation(UBTTask_ExecuteNormalAttack* NormalAttackTask)
{
	IAIActionInterface::AIExecuteNormalAttack_Implementation(NormalAttackTask);

	//if(!OnFinishNATask.IsBound())

	// Bind ending task function with enemy character class
	OnFinishNATask.BindDynamic(NormalAttackTask, &UBTTask_ExecuteNormalAttack::NormalAttackTaskEnd);
	
	// decide how many attack Ai should make
	MaxAttackEachExecution = RndDecideMaxAttack();
	
	// Perform Normal Attack
	
	// Reset Current normal attack counter
	CurrentAttackCount = 0;
	
	// Try normal attack
	TryNormalAttack();

	CurrentAttackCount++;
	
	// Timer function to loop normal attack if Max Attack Each Execution is bigger than 1
	if(MaxAttackEachExecution > 1)
	{
		const UWorld* World = GetWorld();
		if(World == nullptr) return;

		World->GetTimerManager().SetTimer(NormalAttackTimerHandle, this, &AEnemyCharacter::NormalAttackContinueCheck, NorAttackTickInterval, true, -1);		
	}
}

void AEnemyCharacter::AIExecuteFinishNorAttackTask_Implementation()
{
	IAIActionInterface::AIExecuteFinishNorAttackTask_Implementation();

	OnFinishNATask.Execute(BTComponent);
}

int32 AEnemyCharacter::RndDecideMaxAttack()
{
	return UKismetMathLibrary::RandomIntegerInRange(1,3);
}

void AEnemyCharacter::InitializeBTAndBBComponent()
{
	AController* EnemySelfController = GetController();
	if(Controller == nullptr) return;
		
	AEnemyAIController* EnemyAIController =  Cast<AEnemyAIController>(EnemySelfController);
	if(EnemyAIController == nullptr) return;
	
	if(BTComponent == nullptr) BTComponent = EnemyAIController->GetBTComponent();

	if(BBComponent == nullptr && BTComponent != nullptr) BBComponent = BTComponent->GetBlackboardComponent();
}

void AEnemyCharacter::NormalAttackContinueCheck()
{
	// check if character is able to normal attack
	if(CurrentActionState == EActionState::Idle)
	{
		// do normal attack and current attack count increment
		TryNormalAttack();

		CurrentAttackCount++;
		
		// check if character's current attack counter is equal max attack of this round
		if(CurrentAttackCount >= MaxAttackEachExecution)
		{
			const UWorld* World = GetWorld();
			if(World == nullptr) return;

			World->GetTimerManager().ClearTimer(NormalAttackTimerHandle);
		}
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeBTAndBBComponent();
}

void AEnemyCharacter::AIExecuteLaunchAttack_Implementation(UBTTask_ExecuteNormalAttack* NormalAttackTask)
{
	IAIActionInterface::AIExecuteLaunchAttack_Implementation(NormalAttackTask);

	// Bind ending task function with enemy character class
	OnFinishNATask.BindDynamic(NormalAttackTask, &UBTTask_ExecuteNormalAttack::NormalAttackTaskEnd);
	
	if(CurrentActionState == EActionState::Idle)
	{
		CurrentActionState = EActionState::SpecialAttack;

		CurrentPlayingMontage = LaunchAttackMontage;

		PlayAnimMontage(CurrentPlayingMontage, 1, NAME_None);
	}

}
