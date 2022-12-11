// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

UCLASS()
class FPSGAME_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpusle, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;
};
