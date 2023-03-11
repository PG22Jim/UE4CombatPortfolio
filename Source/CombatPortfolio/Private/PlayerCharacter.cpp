// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPortfolio/Public/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &APlayerCharacter::TryDodge);
	PlayerInputComponent->BindAction("NormalAttack", IE_Pressed, this, &APlayerCharacter::TryNormalAttack);
	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &APlayerCharacter::TryGuard);
	PlayerInputComponent->BindAction("Guard", IE_Released, this, &APlayerCharacter::TryCancelGuarding);
	PlayerInputComponent->BindAction("DebugButton", IE_Pressed, this, &APlayerCharacter::DebugTesting);
	

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::DebugTesting()
{
	// Hit result
	FHitResult Hit;
	// Empty array of ignoring actor, maybe add Enemies classes to be ignored
	const TArray<AActor*> IgnoreActors;
	// Line trace by channel from Kismet System Library
	//

	// Calculate launch start position, end position and launch height position
	LaunchStartPos = GetActorLocation();

	const FVector FacingDir = GetActorForwardVector();
	
	const FVector EndPos =  LaunchStartPos + (FacingDir * 300);

	// line trace to see is there any blocking thing from starting to ending
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(this, LaunchStartPos, EndPos, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors, EDrawDebugTrace::Persistent,Hit,true);

	LaunchStartHegiht = LaunchStartPos.Z;

	LaunchHighestHeight = LaunchStartHegiht + 300;

	if(bHit)
		LaunchEndPos = Hit.ImpactPoint;
	else
		LaunchEndPos = EndPos;

	LATimeLine.PlayFromStart();
	
}
