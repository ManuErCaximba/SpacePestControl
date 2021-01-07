// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Sets a collision box for character
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	RootComponent = CollisionBox;

	FTransform CollisionBoxTrans = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 0.5f, 75.0f),
		FVector(6.0f, 0.5f, 1.0f)
	);

	CollisionBox->SetWorldTransform(CollisionBoxTrans);
	CollisionBox->BodyInstance.SetCollisionProfileName("BlockAll");
	
	// Creamos el mesh del personaje
	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MapMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	MapMesh->SetupAttachment(RootComponent);

	FTransform MapMeshTrans = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector((1 / 12) * 1.0f, -18.0f, 0.0f),
		FVector((0.13f / 6), 0.38f, 1.0f)
	);

	MapMesh->SetRelativeTransform(MapMeshTrans);

	// Create a camera and a visible object
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(RootComponent);

	// Offset, rotate the camera and set it orthographic.
	CharacterCamera->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	CharacterCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CharacterCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CharacterCamera->SetOrthoWidth(225.0f);

	if (MapMeshAsset.Succeeded())
	{
		MapMesh->SetStaticMesh(MapMeshAsset.Object);
	}
}

void AMainCharacter::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMainCharacter::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		// Cargamos el material de idle y de run
		UMaterial* IdleMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Assets/Materials/M_IdleProta"));
		UMaterial* RunMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Assets/Materials/M_RunProta"));
		
		if (!CurrentVelocity.IsZero())
		{			

			// Sacamos, si choca el personaje con algo, la normal del hit para que el personaje no se "atasque" con las paredes
			FHitResult HitResult = FHitResult();
			FVector ActualLocation = GetActorLocation();
			FVector NewLocation = ActualLocation + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation, true, &HitResult);
			FVector_NetQuantizeNormal Normal = HitResult.ImpactNormal;

			// Si se choca con una pared a la izq. o der., permite la movilidad en el eje Y
			if (Normal.X == 1.0f || Normal.X == -1.0f)
			{
				FVector YVector = FVector(0.0f, CurrentVelocity.Y, 0.0f);
				FVector NewYLocation = ActualLocation + (YVector * DeltaTime);
				SetActorLocation(NewYLocation, true);
			}
			// Si se choca con una pared arriba o abajo, permite la movilidad en el eje X
			if (Normal.Y == 1.0f || Normal.Y == -1.0f)
			{
				FVector XVector = FVector(CurrentVelocity.X, 0.0f, 0.0f);
				FVector NewXLocation = ActualLocation + (XVector * DeltaTime);
				SetActorLocation(NewXLocation, true);
			}

			// Si el personaje ha conseguido moverse, usa la animacion de correr
			if (ActualLocation != GetActorLocation())
			{
				MapMesh->SetMaterial(0, RunMaterial);
			}
			// Sino, la de estar quieto
			else
			{
				MapMesh->SetMaterial(0, IdleMaterial);
			}
		}
		else
		{
			MapMesh->SetMaterial(0, IdleMaterial);
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &AMainCharacter::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMainCharacter::Move_YAxis);
}
