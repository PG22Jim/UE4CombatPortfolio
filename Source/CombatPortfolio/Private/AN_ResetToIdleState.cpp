// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/AN_ResetToIdleState.h"
#include "CombatPortfolio/Public/BaseCharacter.h"

void UAN_ResetToIdleState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	const bool IsValidUObject = IsValid(MeshComp);

	if(!IsValidUObject) return;

	AActor* OwnerRef = MeshComp->GetOwner();

	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		ICharacterActionInterface::Execute_SwitchToIdleState(OwnerRef, true);
	}

}
