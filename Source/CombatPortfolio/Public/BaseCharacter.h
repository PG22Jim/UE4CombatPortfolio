// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Katana = 0 UMETA(DisplayName = "KATANA"),
	GreatSword = 1 UMETA(DisplayName = "GREATSWORD"),
};

UENUM(BlueprintType)
enum class EActionState: uint8
{
	Idle = 0 UMETA(DisplayName = "IDLE"),
	Evade = 3 UMETA(DisplayName = "EVADE"),
	NormalAttack = 4 UMETA(DisplayName = "NORMALATTACK"),
	Recovering = 5 UMETA(DisplayName = "RECOVERING")
};



UCLASS()
class COMBATPORTFOLIO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CharacterProperty)
	EWeaponType CharacterWeaponType = EWeaponType::Katana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CharacterProperty)
	EActionState CurrentActionState = EActionState::Idle;
	
	/** 
	* Called via input to turn at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	virtual void TurnAtRate(float Rate);

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	
	UFUNCTION(BlueprintCallable)
	void TryDodge();

	UFUNCTION(BlueprintCallable)
	void FinishDodging();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
