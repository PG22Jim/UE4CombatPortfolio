// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ParryToGuard.h"

#include "CharacterActionInterface.h"

void UAN_ParryToGuard::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(!MeshComp || !MeshComp->GetOwner()) return;

	AActor* OwnerRef = MeshComp->GetOwner();

	if(OwnerRef->GetClass()->ImplementsInterface(UCharacterActionInterface::StaticClass()))
	{
		ICharacterActionInterface::Execute_ParryToGuard(OwnerRef);
	}
}
