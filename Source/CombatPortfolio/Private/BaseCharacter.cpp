// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// ========================================= Dodge =============================================
// =============================================================================================
void ABaseCharacter::TryDodge()
{
	
	// if player is recovering from action or is dodging, return
	if(CurrentActionState == EActionState::Recovering || CurrentActionState == EActionState::Evade) return;
	
	// if player is able to dodge, make dodge
	if(CurrentActionState == EActionState::Idle)
	{
		BeginDodge();
		return;
	}
	
	// TODO: if player is attacking, store next command as dodging
	if(CurrentActionState == EActionState::NormalAttack)
	{
		// only store normal attack as buffering command if current buffering command is not normal attack
		if(BufferingAction != EActionState::Evade)
			StoreBufferingCommand(EActionState::Evade);
	}
}

void ABaseCharacter::BeginDodge()
{
	
	if(DodgeAnimMontage == nullptr) return;

	CurrentActionState = EActionState::Evade;

	PlayAnimMontage(DodgeAnimMontage, 1, NAME_None);
}


// ============================================= Attack =============================================
// ==================================================================================================
void ABaseCharacter::TryNormalAttack()
{
	// if player is recovering from action or is dodging, return
	if(CurrentActionState == EActionState::Recovering) return;
	
	// if player is able to dodge, make dodge
	if(CurrentActionState == EActionState::Idle)
	{
		BeginNormalAttack();
		return;
	}

	// TODO: if player is attacking, store next command as normal attack
	if(CurrentActionState == EActionState::NormalAttack)
	{
		// only store normal attack as buffering command if current buffering command is not normal attack
		if(BufferingAction != EActionState::NormalAttack)
			StoreBufferingCommand(EActionState::NormalAttack);
	}
}

void ABaseCharacter::BeginNormalAttack()
{
	if(NormalAttackMontages[0] == nullptr) return;

	CurrentActionState = EActionState::NormalAttack;

	UAnimMontage* PlayingMontage = GetNormalAttackAnimMontage();

	PlayAnimMontage(PlayingMontage, 1, NAME_None);

	NormalAttackCounterIncrement();
}

UAnimMontage* ABaseCharacter::GetNormalAttackAnimMontage()
{
	return NormalAttackMontages[NormalAttackCounter];
}

void ABaseCharacter::NormalAttackCounterIncrement()
{
	NormalAttackCounter++;
	if(NormalAttackCounter >= 5)
	{
		ResetNormalAttackCounter();
	}
}

void ABaseCharacter::ResetNormalAttackCounter()
{
	NormalAttackCounter = 0;
}

// ========================================= Buffering =============================================
// =================================================================================================

void ABaseCharacter::StoreBufferingCommand(EActionState BufferingActionCommand)
{
	const UWorld* World = GetWorld();
	if(World == nullptr) return;

	// Store buffer command
	BufferingAction = BufferingActionCommand;

	
	
	World->GetTimerManager().SetTimer(BufferTimerHandle,this, &ABaseCharacter::ResetBufferCommand, BufferDuration, false, -1);
}

void ABaseCharacter::ResetBufferCommand()
{
	BufferingAction = EActionState::Idle;
}

void ABaseCharacter::BufferChecking()
{
	// Stop buffering timer
	const UWorld* World = GetWorld();
	if(World == nullptr) return;
	World->GetTimerManager().ClearTimer(BufferTimerHandle);

	// switch case to check buffering state
	switch (BufferingAction)
	{
		case EActionState::Evade:
			ResetBufferCommand();
			StopAnimMontage();
			BeginDodge();
			break;
		
		case EActionState::NormalAttack:
			ResetBufferCommand();
			StopAnimMontage();
			BeginNormalAttack();
			break;
		
		default:
			break;
	}
	
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// =============================================== Interface Implementation ======================================

void ABaseCharacter::SwitchToIdleState_Implementation(bool BufferingCheck)
{
	ICharacterActionInterface::SwitchToIdleState_Implementation(BufferingCheck);

	// reset current action state
	CurrentActionState = EActionState::Idle;

	// if notify is firing buffering check, check if player is storing buffering command
	if(BufferingCheck)
	{
		BufferChecking();
		return;
	}

	// reset normal attack counter
	ResetNormalAttackCounter();

	// reset buffering command no matter what
	BufferingAction = EActionState::Idle;
}


void ABaseCharacter::SetDodgingState_Implementation(bool IsDodging)
{
	ICharacterActionInterface::SetDodgingState_Implementation(IsDodging);

	// if bool is true, it means is dodging, flip state to evade state
	if(IsDodging)
	{
		CurrentActionState = EActionState::Evade;
	}
	else
	{
		CurrentActionState = EActionState::Idle;
	}
}

void ABaseCharacter::SetRecoveringState_Implementation(bool IsRecovering)
{
	ICharacterActionInterface::SetRecoveringState_Implementation(IsRecovering);

	if(IsRecovering)
	{
		CurrentActionState = EActionState::Recovering;
	}
	else
	{
		CurrentActionState = EActionState::Idle;
	}
}

