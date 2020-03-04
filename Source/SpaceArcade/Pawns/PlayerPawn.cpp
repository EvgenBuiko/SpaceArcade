// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision	= CreateDefaultSubobject< UBoxComponent			>(	TEXT(	"Collision"	) );
	body		= CreateDefaultSubobject< UStaticMeshComponent	>(	TEXT(	"Body"		) );
	camera		= CreateDefaultSubobject< UCameraComponent		>(	TEXT(	"Camera"	) );
	SetRootComponent( collision );
	body->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	InputComponent->BindTouch( IE_Pressed, this, &APlayerPawn::OnTouch );

}

void APlayerPawn::OnTouch( ETouchIndex::Type TchInd, FVector Coord )
{

}

