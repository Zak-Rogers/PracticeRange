// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	//UE_LOG(LogTemp, Warning, TEXT("example log"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	colliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	colliderComponent->InitSphereRadius(0.5f);

	//set to the coloition profile created in the project settings..................
	colliderComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	
	RootComponent = colliderComponent;

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	//set the projectile movement component to move the colliderComponent as aposed to the rootComponent-? i set it as the rootcomponent no?
	movementComponent->SetUpdatedComponent(colliderComponent);
	movementComponent->InitialSpeed = 2500.0f;
	movementComponent->MaxSpeed = 2500.0f;
	//set the rotation of the projectile to face the direction it is going- needed?
	movementComponent->bRotationFollowsVelocity = true;
	movementComponent->bShouldBounce = false; // nessaery?
	movementComponent->ProjectileGravityScale = 0.2f;

	//find mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> projectileMeshAsset(TEXT("/Game/Models/Sphere.Sphere"));

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetStaticMesh(projectileMeshAsset.Object);
	meshComponent->SetupAttachment(RootComponent);

	selfDestructTime = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	selfDestructTime -= DeltaTime;

	if (selfDestructTime <= 0)
	{
		this->Destroy();
	}
}
/** Fires projectile in direction at initial speed */
void AProjectile::FireProjectile(const FVector& direction)
{
	movementComponent->Velocity = direction * movementComponent->InitialSpeed;
}

