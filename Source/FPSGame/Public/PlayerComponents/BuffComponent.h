// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();
	friend class APlayerCharacter;

	void Heal(float HealAmount, float HealingTime);
	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime);
	void SetInitalSpeeds(float BaseSpeed, float CrouchSpeed);
protected:
	virtual void BeginPlay() override;

	void HealRampUp(float DeltaTime);

private:
	UPROPERTY()
	class APlayerCharacter* Character;

	bool bHealing = false;
	float HealingRate = 0;
	float AmountToHeal = 0.f;

	FTimerHandle SpeedBuffTimer;
	void ResetSpeeds();

	float InitialBaseSpeed;
	float InitailCrouchSpeed;

	UFUNCTION(NetMulticast,Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
