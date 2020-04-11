// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/ShootProjectile.h"

#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting Params")
		float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting Params")
		TSubclassOf<AShootProjectile> ProjectileClass;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void Shoot();
	
	FTimerHandle ShootingTimer;

public:	

		
};
