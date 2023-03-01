// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/AN_EnterRecoveringState.h"

#include "CombatPortfolio/Public/CharacterActionInterface.h"

void UAN_EnterRecoveringState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(!MeshComp || !MeshComp->GetOwner()) return;

	AActor* OwnerRef = MeshComp->GetOwner();

	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		ICharacterActionInterface::Execute_SetRecoveringState(OwnerRef, true);
	}
}
