// Fill out your copyright notice in the Description page of Project Settings.

#include "PractiseRangeCharacter.h"

// Sets default values
APractiseRangeCharacter::APractiseRangeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//create and setup camera component.
	{
		camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		//Attach to the capsuleComponent of the character.
		camera->SetupAttachment(GetCapsuleComponent());
		//position the camera at eye height.
		camera->SetRelativeLocation(FVector(0.0f, 0.f, 0.0f + BaseEyeHeight));
		//use the pawncontroler to rotate the camera.
		camera->bUsePawnControlRotation = true;
	}

	//Set projectile class
	{
		//find projectile class.
		static ConstructorHelpers::FClassFinder<AProjectile> projectileClassObj(TEXT("/Script/PractiseRange.Projectile")); // right clicked on script in editor and copied the refrence.  
		//set projectileClass to the class found above.
		projectileClass = projectileClassObj.Class;
	}
	
	//set up audio component
	{
		//finds gun shot sound cue.
		static ConstructorHelpers::FObjectFinder<USoundCue>gunShotCueObj(TEXT("/Game/Audio/Gun_Shot_Cue.Gun_Shot_Cue"));
		//set the gunShotCue varible to the cue found above.
		gunShotCue = gunShotCueObj.Object;
		//create an audio component
		audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
		//attach to root component
		audioComponent->SetupAttachment(RootComponent);
	}
	

	//set up gun mesh.
	{
		//finds gun mesh.
		static ConstructorHelpers::FObjectFinder<UStaticMesh> gunMesh (TEXT("/Game/Models/gun.gun"));
		//create a static mesh component.
		gunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMeshComponent"));
		//assign the gun mesh to the static mesh component.
		gunMeshComponent->SetStaticMesh(gunMesh.Object);
		//attach to root component.
		gunMeshComponent->SetupAttachment(RootComponent);
		//set the location of the mesh.
		gunMeshComponent->SetRelativeLocation(FVector(30.0f, 0.0f, 55.0f));
		//set the rotation of the mesh.
		gunMeshComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		//set the scale of the mesh.
		gunMeshComponent->SetWorldScale3D(FVector(10.0f, 10.0f, 10.0f));
	}

	// set default values.
	timeSinceLastShot = 0.0f;
	timeBtwShots = 0.3f;
}

// Called when the game starts or when spawned
void APractiseRangeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//set default sounds
	audioComponent->SetSound(gunShotCue);
}

// Called every frame
void APractiseRangeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// increments the timeSinceLastShot by DeltaTime till it equals the time betweent shots.
	if (timeSinceLastShot >= 0.0f && timeSinceLastShot <= timeBtwShots)
	{
		timeSinceLastShot += DeltaTime;
	}
}

// Called to bind functionality to input.
void APractiseRangeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//AxisBinding
	{
		//binding the inputs for moving to the PlayerInputComponent with their respective functions.
		PlayerInputComponent->BindAxis("MoveForward", this, &APractiseRangeCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &APractiseRangeCharacter::MoveRight);

		//binding for looking around using the functions inherited from the ACharacter class.
		PlayerInputComponent->BindAxis("Turn", this, &APractiseRangeCharacter::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &APractiseRangeCharacter::AddControllerPitchInput);
	}

	//ActionBinding
	{
		//binding the inputs for shooting to the PlayerInputComponent.
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APractiseRangeCharacter::Shoot);
	}
}


void APractiseRangeCharacter::MoveForward(float amount)
{
	//get the rotation of the controller controling the character to know the direction it is facing.
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//call the AddMovementInput function inherited from the APawn class, giving it the forward direction and the movement amount.
	AddMovementInput(direction, amount);
}

void APractiseRangeCharacter::MoveRight(float amount)
{
	//get the rotation of the controller controling the character to know the direction is right.
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//call the AddMovementInput function inherited from the APawn class, giving it the forward direction and the movement amount.
	AddMovementInput(direction, amount);
}

void APractiseRangeCharacter::Shoot()
{
	if (projectileClass) // if class assigned in the constructor exists.
	{
		FVector cameraLocation;
		FRotator cameraRotation;
		GetActorEyesViewPoint(cameraLocation, cameraRotation);

		//transform muzzle offest from camera space to world space.
		FVector muzzleLocation = cameraLocation + FTransform(cameraRotation).TransformVector(muzzleOffset);
		FRotator muzzleRotation = cameraRotation;

		UWorld* world = GetWorld();// gets a varible for the world to spawn the projectile in.
		if (world)
		{
			FActorSpawnParameters spawnParmeters;
			spawnParmeters.Owner = this;

			//play gunshot audio
			audioComponent->Play(0.0f);

			if (timeSinceLastShot >= timeBtwShots)
			{
				//spawn Projectile
				AProjectile* projectile = world->SpawnActor<AProjectile>(projectileClass, muzzleLocation, muzzleRotation, spawnParmeters);
				timeSinceLastShot = 0.0f;
			
				if (projectile)
				{
					//set the projectile's initial trajectory.
					FVector fireDirection = muzzleRotation.Vector();
					projectile->FireProjectile(fireDirection);
				}
			}
		}
	}
}

