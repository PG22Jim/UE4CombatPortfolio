// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_FinishActionAnim.h"

#include "AIActionInterface.h"
#include "CharacterActionInterface.h"

void UAN_FinishActionAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// valid check
	if(!MeshComp || !MeshComp->GetOwner()) return;

	// get owner actor reference
	AActor* OwnerRef = MeshComp->GetOwner();

	// check if owner class has character action interface
	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		// if it has character action interface, it means its base character, execute its SwitchToIdleState function
		ICharacterActionInterface::Execute_SwitchToIdleState(OwnerRef, false);

		// check if owner class has ai action interface
		if(OwnerRef->GetClass()->ImplementsInterface(UAIActionInterface::StaticClass()))
		{
			// if it has ai action interface, it means it is enemy character, execute Finish normal attack task function
			IAIActionInterface::Execute_AIExecuteFinishNorAttackTask(OwnerRef);
		}
	}


}
