// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerTypes/TurningInPlace.h"
#include "Interfaces/InteractWithCrosshairsInterface.h"
#include "Components/TimelineComponent.h"
#include "PlayerTypes/CombatState.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter,public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	void PlayFireMontage(bool bAiming);
	void PlayElimMontage();
	void PlayReloadMontage();
	void PlayThrowGrenadeMontage();

	virtual void OnRep_ReplicatedMovement() override;

	void Elim();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastElim();

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;

	void UpdateHUDHealth();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents();
	void PlayHitReactMontage();

	virtual void Destroyed() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimBuittonReleased();
	void FireButtonpressed();
	void ReloadButtonPressed();
	void AimOffset(float DeltaTime);
	void CalculateAO_Pitch();
	virtual void Jump() override;

	void FireButtonReleased();
	void SimProxiesTurn();
	UFUNCTION()
	void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void PoolInit();

	void QButtonPressed();
	void EButtonPressed();

	void RotateInPlace(float DeltaTime);
	void GrenadeButtonPressed();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere)
	class UBuffComponent* Buff;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere,Category = Combat)
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere,Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere,Category = Combat)
	UAnimMontage* ElimMontage;

	UPROPERTY(EditAnywhere,Category = Combat)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ThrowGrenadeMontage;

	void HideCameraIfCharacterClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 50.f;

	bool bRotateRootBone;
	UPROPERTY(EditAnywhere)
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	float CalculateSpeed();

	//Player Health
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere,Category = "Player Stats")
	float Health = 100.f;
	
	UFUNCTION()
	void OnRep_Health(float LastHealth);

	class APlayerCharacterController* PlayerCharacterController;
	
	bool bElimmed = false;

	FTimerHandle ElimTimer;

	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;

	void ElimTimerFinished();
	
	//Dissolve Effect

	UTimelineComponent* DissolveTimeline;

	FOnTimelineFloat DissolveTrack;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	void StartDissolve();

	UPROPERTY(VisibleAnywhere,Category = Elim)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	UPROPERTY(EditAnywhere,Category = Elim)
	UMaterialInstance* DissolveMaterialInstance;

	UPROPERTY()
	class APlayerCharacterState* PlayerCharacterState;

	UPROPERTY(EditAnywhere,Category= Combat)
	float SocketOffsetY;
	UPROPERTY(EditAnywhere,Category= Combat)
	float SocketOffsetZ;

public:
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch()  const { return AO_Pitch; }
	AWeapon* GetEquippedWeapon();

	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FVector GetHitTarget() const;
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsElimmed() const { return bElimmed; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	ECombatState GetCombatState() const;
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }
	FORCEINLINE FTimerHandle& GetElimTimerHandle()  { return ElimTimer; }
	FORCEINLINE UAnimMontage* GetReloadMontage() const { return ReloadMontage; }
	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }
	FORCEINLINE UBuffComponent* GetBuff()const { return Buff; }
};
