// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AShootProjectile::AShootProjectile()
	: ShootProjectileSpeed(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collision	= CreateDefaultSubobject<USphereComponent		> (TEXT("Collision"			));
	Mesh		= CreateDefaultSubobject<UStaticMeshComponent	> (TEXT("ProjectileMesh"	));

	RootComponent = Collision;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(ShootProjectileSpeed * DeltaTime, 0, 0));
}

