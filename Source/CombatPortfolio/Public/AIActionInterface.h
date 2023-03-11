// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIActionInterface.generated.h"

class UBTTask_ExecuteNormalAttack;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBATPORTFOLIO_API IAIActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AIExecuteNormalAttack(UBTTask_ExecuteNormalAttack* NormalAttackTask);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AIExecuteLaunchAttack(UBTTask_ExecuteNormalAttack* NormalAttackTask);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AIExecuteFinishNorAttackTask();

	
	
};
