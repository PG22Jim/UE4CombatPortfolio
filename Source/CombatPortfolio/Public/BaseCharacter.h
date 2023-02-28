// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterActionInterface.h"
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
	Evade = 1 UMETA(DisplayName = "EVADE"),
	NormalAttack = 2 UMETA(DisplayName = "NORMALATTACK"),
	Recovering = 3 UMETA(DisplayName = "RECOVERING")
};



UCLASS()
class COMBATPORTFOLIO_API ABaseCharacter : public ACharacter , public ICharacterActionInterface
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimMontages)
	UAnimMontage* DodgeAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimMontages)
	TArray<UAnimMontage*> NormalAttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EActionState BufferingAction = EActionState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BufferDuration = 0.2f;

	// Timer Handle for calling parkour functions in time
	FTimerHandle BufferTimerHandle;
	
	
	int32 NormalAttackCounter = 0;
	
	
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
	void BeginDodge();

	
	UFUNCTION(BlueprintCallable)
	void TryNormalAttack();

	UFUNCTION(BlueprintCallable)
	void BeginNormalAttack();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAnimMontage* GetNormalAttackAnimMontage();

	void NormalAttackCounterIncrement();

	void ResetNormalAttackCounter();


	void StoreBufferingCommand(EActionState BufferingActionCommand);

	void ResetBufferCommand();

	void BufferChecking();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	virtual void SwitchToIdleState_Implementation(bool BufferingCheck) override;
	
	virtual void SetDodgingState_Implementation(bool IsDodgingEnd) override;

	virtual void SetRecoveringState_Implementation(bool IsRecovering) override;

	
	
};
