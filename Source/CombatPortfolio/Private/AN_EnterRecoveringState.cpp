// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/AN_EnterRecoveringState.h"

#include "CombatPortfolio/Public/CharacterActionInterface.h"

void UAN_EnterRecoveringState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	const bool IsValidUObject = IsValid(MeshComp);

	if(!IsValidUObject) return;

	AActor* OwnerRef = MeshComp->GetOwner();

	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		ICharacterActionInterface::Execute_SetDodgingState(OwnerRef, true);
	}
}
