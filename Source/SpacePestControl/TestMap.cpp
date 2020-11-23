// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMap.h"

// Sets default values
ATestMap::ATestMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Creamos el mesh del mapa y lo hago el componente principal de la clase
	UStaticMeshComponent* MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MapMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	MapMesh->SetupAttachment(RootComponent);

	// Cargamos el material que usara el mesh
	UMaterial* MapMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Assets/Materials/M_TestMap"));

	//Creamos cuatro paredes invisibles para que el personaje no salga del mapa
	IWRight = CreateDefaultSubobject<UBoxComponent>(TEXT("IWRight"));
	IWRight->SetupAttachment(MapMesh);
	IWRight->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	IWLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("IWLeft"));
	IWLeft->SetupAttachment(MapMesh);
	IWLeft->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	IWBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("IWBottom"));
	IWBottom->SetupAttachment(MapMesh);
	IWBottom->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));

	// Creamos valores por defecto para el mesh y las paredes invisibles para que mantenga la proporcion por pixeles
	FTransform MeshTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 0.5f, 0.0f),
		FVector(1.92f, 1.87f, 1.0f)
	);
	FVector IWScale = FVector(1 / 1.92f, 1 / 1.87f, 1.0f);
	FTransform IWRToDefaultTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(47.4f, 0.29f, 15.0f),
		FVector(1 / 1.92f, 50 + (1 / 1.87f), 10.0f)
	);
	FTransform IWLToDefaultTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(-47.4f, 0.29f, 15.0f),
		FVector(1 / 1.92f, 50 + (1 / 1.87f), 10.0f)
	);
	FTransform IWBToDefaultTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 47.34f, 15.0f),
		FVector(50 + (1 / 1.92f), 1 / 1.87f, 10.0f)
	);


	// Colocamos el mesh, el material y los valores por defecto al componente principal de la clase
	if (MapMeshAsset.Succeeded())
	{
		MapMesh->SetStaticMesh(MapMeshAsset.Object);
		MapMesh->SetWorldTransform(MeshTransform);
		MapMesh->SetMaterial(0, MapMaterial);
		IWRight->SetRelativeTransform(IWRToDefaultTransform);
		IWLeft->SetRelativeTransform(IWLToDefaultTransform);
		IWBottom->SetRelativeTransform(IWBToDefaultTransform);
	}
}

// Called when the game starts or when spawned
void ATestMap::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

