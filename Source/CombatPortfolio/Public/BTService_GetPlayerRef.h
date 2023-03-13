// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_GetPlayerRef.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UBTService_GetPlayerRef : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=BBKeyToStore)
	FBlackboardKeySelector BBKey_PlayerRef;
};
