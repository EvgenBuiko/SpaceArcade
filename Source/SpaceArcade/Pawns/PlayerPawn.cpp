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

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	bool max_min_x = GetActorLocation().X >= MinimumXScope && GetActorLocation().X <= MaximumXScope;
	bool max_min_y = GetActorLocation().Y >= MinimumYScope && GetActorLocation().Y <= MaximumYScope;
	if (!max_min_x)
		SetActorLocation(FVector((GetActorLocation().X < MinimumXScope) ? MinimumXScope + 1 : MaximumXScope - 1, GetActorLocation().Y, 0));
	if (!max_min_y)
		SetActorLocation(FVector(GetActorLocation().X, (GetActorLocation().Y < MinimumYScope) ? MinimumYScope + 1 : MaximumYScope - 1, 0));

	if( PlayerController )
	{
		bool touch;
		FVector2D curTouchCoords;
		PlayerController->GetInputTouchState(ETouchIndex::Touch1, curTouchCoords.X, curTouchCoords.Y, touch);
		if( touch && max_min_x && max_min_y )
		{
			UE_LOG( LogTemp, Log, TEXT( "Touching in X:%f Y:%f" ), curTouchCoords.X, curTouchCoords.Y );
			AddActorWorldOffset( FVector( TouchLocation.Y - curTouchCoords.Y, curTouchCoords.X - TouchLocation.X, 0 ) * 0.5 );
			TouchLocation = curTouchCoords;
		}
	}
	else
	{
		UE_LOG( LogController, Error, TEXT( "!!!NULL PlayerController!!!" ) );
		return;
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouch);
}

void APlayerPawn::OnTouch( ETouchIndex::Type TchInd, FVector Coord )
{
	UE_LOG(LogTemp, Log, TEXT("Touch"));
	TouchLocation = FVector2D(Coord);
}

