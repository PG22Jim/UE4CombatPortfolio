// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// COMPONENTS

	UPROPERTY( EditInstanceOnly )
	UBehaviorTreeComponent* BehaviorComponent;
	
	UPROPERTY( EditInstanceOnly )
	UBlackboardComponent* BlackboardComponent;

	// SenseConfig

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=AIPerception)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	UAISenseConfig_Hearing* HearConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AIPerception)
	float SightRadius = 6000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AIPerception)
	float SightSuccessRange = 500.0f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AIPerception)
	float HearRange = 5000.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=AIPerception)
	float SightAngleDegree = 75.0f;

	
	// PROPERTIES
	
	UPROPERTY( EditDefaultsOnly, Category="AI" )
	UBehaviorTree* BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()	
	void IsPLayerNoticed(AActor* DetectedPawns, FAIStimulus Stimulus);

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanEnemySeePlayer(AActor* DetectedPawns);
public:
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);

	UBehaviorTreeComponent* GetBTComponent() const { return BehaviorComponent; }

	UBlackboardComponent* GetBBComponent() const { return BlackboardComponent; }
	
private:

	
	void InitializeBehaviorTree();

	void InitializeSenseConfig();
};
