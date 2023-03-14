// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/ANS_ResetToIdleState.h"
#include "CombatPortfolio/Public/BaseCharacter.h"

void UANS_ResetToIdleState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AActor* OwnerRef = MeshComp->GetOwner();

	ABaseCharacter* CharacterRef = Cast<ABaseCharacter>(OwnerRef);

	if(CharacterRef)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Notify Works!"));	
	}
}
