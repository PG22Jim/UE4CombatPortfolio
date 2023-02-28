// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_FinishActionAnim.h"

#include "CharacterActionInterface.h"

void UAN_FinishActionAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	const bool IsValidUObject = IsValid(MeshComp);

	if(!IsValidUObject) return;

	AActor* OwnerRef = MeshComp->GetOwner();

	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		ICharacterActionInterface::Execute_SwitchToIdleState(OwnerRef, false);
	}


}
