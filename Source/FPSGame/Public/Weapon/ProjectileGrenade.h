// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Projectile.h"
#include "ProjectileGrenade.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AProjectileGrenade : public AProjectile
{
	GENERATED_BODY()
public:
	AProjectileGrenade();
protected:
	virtual void BeginPlay() override;

	void StartDestroyTime();

	void DestroyTimerFinshed();
	virtual void Destroyed() override;

	UFUNCTION()
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
private:
	UPROPERTY(EditAnywhere)
	USoundCue* BounceSound;
	
	FTimerHandle DestroyTimer;

	UPROPERTY(EditAnywhere)
	float DestroyTime = 2.f;
	
};
