// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
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

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast< APlayerController >( NewController );
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type touchIndex, FVector touchLocation)
{
	TouchLocation = touchLocation;
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
	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

void APlayerPawn::GiveCoordsInScope()
{
	FVector coordsInScope = GetActorLocation();
	coordsInScope.X = FMath::Clamp(coordsInScope.X, MinimumScope.X, MaximumScope.X);
	coordsInScope.Y = FMath::Clamp(coordsInScope.Y, MinimumScope.Y, MaximumScope.Y);
	SetActorLocation( coordsInScope );
}

void APlayerPawn::OnTouchMove( ETouchIndex::Type touchIndex, FVector touchLocation )
{
	FVector oldLocation = TouchLocation;
	if (PlayerController)
	{
		UE_LOG(LogTemp, Log, TEXT("Touching in X:%f Y:%f"), touchLocation.Y, touchLocation.X );
		AddActorLocalOffset(FVector(oldLocation.Y - touchLocation.Y, touchLocation.X - oldLocation.X, 0) * MoveSensivity);
		GiveCoordsInScope();
	}
	else
	{
		UE_LOG(LogController, Error, TEXT("!!!NULL PlayerController!!!"));
		return;
	}
	TouchLocation = touchLocation;
}

