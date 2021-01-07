// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"

// Sets default values
AHitBox::AHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creamos el mesh del mapa y lo hago el componente principal de la clase
	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MapMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	MapMesh->SetupAttachment(RootComponent);

	// Cargamos el material que usara el mesh
	UMaterial* MapMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Basic_Wall"));

	// Creamos valores por defecto para el mesh
	FTransform MeshTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 0.5f, 0.0f),
		FVector(0.1f, 0.1f, 0.1f)
	);

	// Colocamos el mesh, el material y los valores por defecto al componente principal de la clase
	if (MapMeshAsset.Succeeded())
	{
		MapMesh->SetStaticMesh(MapMeshAsset.Object);
		MapMesh->SetWorldTransform(MeshTransform);
		MapMesh->SetMaterial(0, MapMaterial);
	}

}

// Called when the game starts or when spawned
void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

