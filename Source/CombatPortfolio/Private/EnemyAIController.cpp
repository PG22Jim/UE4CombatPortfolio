// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	// start the behaviour tree
	if (BehaviorComponent != nullptr && BehaviorTree != nullptr)
	{
		if (BehaviorTree->BlackboardAsset != nullptr)
		{
			BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
		
		BehaviorComponent->StartTree(*BehaviorTree);
	}

	// assign delegate function when Ai perception component update 
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::IsPLayerNoticed);

	InPawn->OnTakeAnyDamage.AddDynamic(this, &AEnemyAIController::ReceiveDamage);
	
}

void AEnemyAIController::IsPLayerNoticed(AActor* DetectedPawns, FAIStimulus Stimulus)
{
	UWorld* World = GetWorld();
	if(World == nullptr) return;

	const TSubclassOf<UAISense> SenseClass =  UAIPerceptionSystem::GetSenseClassForStimulus(World, Stimulus);

	// if SenseClassForStimulus is hearing 
	if(SenseClass == UAISense_Hearing::StaticClass())
	{
		// // if enemy state is idle or enemy cannot see player
		// if(BlackboardComponent->GetValueAsEnum("EnemySituation"))
		// {
		// 	// set enemy state to only hear something and turn at that direction
		// 	BlackboardComponent->SetValueAsEnum("EnemySituation", 1);
		//
		// 	const FVector SoundLocation =  Stimulus.StimulusLocation;
		// 	BlackboardComponent->SetValueAsVector("HeardLocation", SoundLocation);
		// }
	}
}

void AEnemyAIController::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	
}

bool AEnemyAIController::CanEnemySeePlayer(AActor* DetectedPawns)
{
	TArray<AActor*> PerceivedActors;
	AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PerceivedActors);
	return PerceivedActors.Contains(DetectedPawns);
}

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
{
	InitializeBehaviorTree();
	InitializeSenseConfig();
}

void AEnemyAIController::InitializeBehaviorTree()
{
	//Initialize Behaviour Tree
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AEnemyAIController::InitializeSenseConfig()
{
	// Create Default class of PerceptionComponent, Sight and Hearing config
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Enemy Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	// Assign Variables of Sight and Hearing config
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = SightSuccessRange;
	SightConfig->PeripheralVisionAngleDegrees = SightAngleDegree;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearConfig->HearingRange = HearRange;
	HearConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Assign Perception Component's configure sense
	AIPerceptionComponent->ConfigureSense(*HearConfig);
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(HearConfig->GetSenseImplementation());
}



