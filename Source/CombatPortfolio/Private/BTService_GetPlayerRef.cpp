// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetPlayerRef.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_GetPlayerRef::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if(BlackBoard == nullptr) return;

	UObject* PlayerRefFromBBKey = BlackBoard->GetValueAsObject(BBKey_PlayerRef.SelectedKeyName);

	if(!(PlayerRefFromBBKey == nullptr)) return;

	const UWorld* World = GetWorld();
	if(World == nullptr) return;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World,0);

	APlayerCharacter* CastedRef = Cast<APlayerCharacter>(PlayerCharacter);

	BlackBoard->SetValueAsObject(BBKey_PlayerRef.SelectedKeyName,CastedRef);
}
