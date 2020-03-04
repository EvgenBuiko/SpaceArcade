// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"

#include "PlayerPawn.generated.h"

UCLASS()
class SPACEARCADE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Fields
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* body;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
		UBoxComponent* collision;
	UPROPERTY(EditAnywhere, BlueprintreadOnly, Category = "Camera")
		UCameraComponent* camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnTouch( ETouchIndex::Type, FVector );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
