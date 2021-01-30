// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Target.h"
#include "Projectile.generated.h"

UCLASS()
class PRACTISERANGE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// public function to be called by character class.
	void  FireProjectile(const FVector& direction);

private:
	USphereComponent* colliderComponent;
	UProjectileMovementComponent* movementComponent;
	UStaticMeshComponent* meshComponent;
	float selfDestructTime;

};
