// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIActionInterface.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	NormalAttack = 0 UMETA(DisplayName = "NORMALATTACK"),
	LaunchingAttack = 1 UMETA(DisplayName = "LAUNCHATTACK"),
};



DECLARE_DYNAMIC_DELEGATE_OneParam(FFinishNormalAttacking, UBehaviorTreeComponent*, BehaviorTreeReference);

UCLASS()
class COMBATPORTFOLIO_API AEnemyCharacter : public ABaseCharacter, public IAIActionInterface
{
	GENERATED_BODY()

private:

	FFinishNormalAttacking OnFinishNATask;

	

	int32 MaxAttackEachExecution;

	int32 CurrentAttackCount = 0;

	// Timer handle
	FTimerHandle NormalAttackTimerHandle;


	int32 RndDecideMaxAttack();

	void InitializeBTAndBBComponent();

protected:

	UPROPERTY()
	UBehaviorTreeComponent* BTComponent;
	
	UPROPERTY()
	UBlackboardComponent* BBComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NorAttackTickInterval = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimMontages)
	UAnimMontage* LaunchAttackMontage;
	
	void NormalAttackContinueCheck();
	
public:

	virtual void BeginPlay() override;

	virtual void AIExecuteLaunchAttack_Implementation(UBTTask_EnemyExecution_Base* NormalAttackTask, FVector CurrentPlayerPos) override;
	
	virtual void AIExecuteNormalAttack_Implementation(UBTTask_ExecuteNormalAttack* NormalAttackTask) override;

	virtual void AIExecuteFinishNorAttackTask_Implementation() override;
};
