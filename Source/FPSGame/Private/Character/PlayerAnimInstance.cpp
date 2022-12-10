// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAnimInstance.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"
void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	}

	if (PlayerCharacter == nullptr) return;

	FVector Velocity = PlayerCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
	bIsInAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = PlayerCharacter->IsWeaponEquipped();
	bIsCrouched = PlayerCharacter->bIsCrouched;
	bAiming = PlayerCharacter->IsAiming();
	EquippedWeapon = PlayerCharacter->GetEquippedWeapon();
	TurningInPlace = PlayerCharacter->GetTurningInPlace();

	//Offset Yaw for Strafing
	FRotator AimRotation = PlayerCharacter->GetBaseAimRotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimRotation Yaw : %f "), AimRotation.Yaw);
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(PlayerCharacter->GetVelocity());
	//UE_LOG(LogTemp, Warning, TEXT("MovementRotation Yaw: %f "), MovementRotation.Yaw);
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 15.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationlastFrame = CharacterRotation;
	CharacterRotation = PlayerCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationlastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = PlayerCharacter->GetAO_Yaw();
	AO_Pitch = PlayerCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && PlayerCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotator;
		PlayerCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"),LeftHandTransform.GetLocation(),FRotator::ZeroRotator,OutPosition,OutRotator);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotator));
	}
}
