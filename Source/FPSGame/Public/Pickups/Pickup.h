// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class FPSGAME_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnyWhere)
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnyWhere)
	class USoundCue* PickupSound;

	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* PickupMesh;

};