// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBATPORTFOLIO_API ICharacterActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.


public:
	// NativeEvent to get override and get called with _Implemtation
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SwitchToIdleState(bool BufferingCheck);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ParryToGuard();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GuardToGuardEnd();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDodgingState(bool IsDodging);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetRecoveringState(bool IsRecovering);
	
};
