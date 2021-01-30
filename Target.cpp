// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//gets default target model.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshObj(TEXT("/Game/Models/Target.Target"));

	//create a static mesh component and assign the target model.
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetStaticMesh(meshObj.Object);
	RootComponent = meshComponent;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


