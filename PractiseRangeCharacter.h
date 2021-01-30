// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h" // for the camera component.
#include "Components/CapsuleComponent.h" // to attach camera to the capsule component.
#include "Projectile.h" // projectile class.
#include "UObject/ConstructorHelpers.h" 
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "PractiseRangeCharacter.generated.h"

UCLASS()
class PRACTISERANGE_API APractiseRangeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APractiseRangeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//int score;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;
	UPROPERTY(EditDefaultsOnly, category = Projectile)
	TSubclassOf<class AProjectile> projectileClass;
	UPROPERTY(EditAnywhere, Category = Weapon)
	FVector muzzleOffset;
	UAudioComponent* audioComponent;
	USoundCue* gunShotCue;
	UStaticMeshComponent* gunMeshComponent;
	float timeBtwShots;
	float timeSinceLastShot;
	bool canShoot;

	/** moves the character forward relative to the direction it is facing */
	void MoveForward(float amount);
	/** moves the character right relative to the direction it is facing */
	void MoveRight(float amount);
	/** Fires projectile*/
	void Shoot();
};
