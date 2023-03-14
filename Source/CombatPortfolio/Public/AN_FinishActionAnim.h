// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_FinishActionAnim.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPORTFOLIO_API UAN_FinishActionAnim : public UAnimNotify
{
	GENERATED_BODY()

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
