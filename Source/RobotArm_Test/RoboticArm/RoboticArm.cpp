// Fill out your copyright notice in the Description page of Project Settings.

#pragma region --- Own scripts ---

#include "RoboticArm.h"

#pragma endregion

#pragma region --- UE4 Lib ---

#include "Components/PoseableMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#pragma endregion

// Sets default values
ARoboticArm::ARoboticArm()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create root component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	// 
	CameraRotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRotationPoint"));
	CameraRotPoint->SetupAttachment(pRoot);

	// create default camera component and attach to root
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRotPoint);

	CameraDir = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Dir"));
	CameraDir->SetupAttachment(Camera);
	CameraDir->SetRelativeRotation(FRotator(0.f, -(Camera->GetRelativeLocation().Z), 0.f));

	// Create poseable mesh
	RoboticArm = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("RoboticArm"));
	RoboticArm->SetupAttachment(pRoot);

	// Create skeletal mesh component
	RoboticArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RoboticArmMesh"));
	RoboticArmMesh->SetupAttachment(pRoot);

#pragma region --- Rotate Points ---

	// base point
	Base_Point = CreateDefaultSubobject<USceneComponent>(TEXT("Base_Point"));
	Base_Point->SetupAttachment(pRoot);

	// base swing arm point
	BaseSwingArm_Point = CreateDefaultSubobject<USceneComponent>(TEXT("BaseSwingArm_Point"));
	BaseSwingArm_Point->SetupAttachment(Base_Point);
	BaseSwingArm_Point->SetRelativeLocation(FVector(0.f, 0.f, 75.f));
	BaseSwingArm_Point->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// arm one point
	ArmOne_Point = CreateDefaultSubobject<USceneComponent>(TEXT("ArmOne_Point"));
	ArmOne_Point->SetupAttachment(BaseSwingArm_Point);
	ArmOne_Point->SetRelativeLocation(FVector(88.603073f, 114.54834f, 0.f));

	// arm one axis point
	ArmOneAxis_Point = CreateDefaultSubobject<USceneComponent>(TEXT("ArmOneAxis_Point"));
	ArmOneAxis_Point->SetupAttachment(ArmOne_Point);
	ArmOneAxis_Point->SetRelativeRotation(FRotator(0.f, 49.397102f, 90.f));

	// arm two point
	ArmTwo_Point = CreateDefaultSubobject<USceneComponent>(TEXT("ArmTwo_Point"));
	ArmTwo_Point->SetupAttachment(ArmOneAxis_Point);
	ArmTwo_Point->SetRelativeLocation(FVector(0.f, 0.f, 122.126793f));
	ArmTwo_Point->SetRelativeRotation(FRotator(-90.f, 0.f, -90.f));

	// arm two axis point
	ArmTwoAxis_Point = CreateDefaultSubobject<USceneComponent>(TEXT("ArmTwoAxis_Point"));
	ArmTwoAxis_Point->SetupAttachment(ArmTwo_Point);
	ArmTwoAxis_Point->SetRelativeRotation(FRotator(0.f, 150.f, 90.f));

	// hand point
	Hand_Point = CreateDefaultSubobject<USceneComponent>(TEXT("Hand_Point"));
	Hand_Point->SetupAttachment(ArmTwoAxis_Point);
	Hand_Point->SetRelativeLocation(FVector(0.f, 0.f, 34.290184f));

	// finger one point
	FingerOne_Point = CreateDefaultSubobject<USceneComponent>(TEXT("FingerOne_Point"));
	FingerOne_Point->SetupAttachment(Hand_Point);
	FingerOne_Point->SetRelativeLocation(FVector(-11.249985f, 0.f, 24.956512f));

	// finger two point
	FingerTwo_Point = CreateDefaultSubobject<USceneComponent>(TEXT("FingerTwo_Point"));
	FingerTwo_Point->SetupAttachment(Hand_Point);
	FingerTwo_Point->SetRelativeLocation(FVector(11.250031f, 0.f, 24.956512f));
	FingerTwo_Point->SetRelativeRotation(FRotator(0.f, 180.f, -180.f));

#pragma endregion

#pragma region --- Collision ---

	// base collision
	BaseOne_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseOne_Col"));
	BaseOne_Collision->SetupAttachment(Base_Point);

	// base two collision
	BaseTwo_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseTwo_Col"));
	BaseTwo_Collision->SetupAttachment(BaseSwingArm_Point);
	BaseTwo_Collision->SetRelativeLocation(FVector(0.f, -75.f, 0.f));
	BaseTwo_Collision->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	// base swing arm collision
	BaseSwingArm_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseSwingArm_Col"));
	BaseSwingArm_Collision->SetupAttachment(BaseSwingArm_Point);
	BaseSwingArm_Collision->SetRelativeLocation(FVector(0.f, -75.f, 0.f));
	BaseSwingArm_Collision->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	// arm one axis collision
	ArmOneAxis_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmOneAxis_Col"));
	ArmOneAxis_Collision->SetupAttachment(ArmOne_Point);
	ArmOneAxis_Collision->SetRelativeLocation(FVector(-88.60f, -189.55f, 0.f));
	ArmOneAxis_Collision->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	// arm one collision
	ArmOne_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmOne_Col"));
	ArmOne_Collision->SetupAttachment(ArmOneAxis_Point);
	ArmOne_Collision->SetRelativeLocation(FVector(-202.16f, 0.f, -53.97f));
	ArmOne_Collision->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

	// arm two axis collision
	ArmTwoAxis_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmTwoAxis_Col"));
	ArmTwoAxis_Collision->SetupAttachment(ArmTwo_Point);
	ArmTwoAxis_Collision->SetRelativeLocation(FVector(176.09f, -202.16f, 0.f));
	ArmTwoAxis_Collision->SetRelativeRotation(FRotator(0.f, 40.f, 90.f));

	// arm two collision
	ArmTwo_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmTwo_Col"));
	ArmTwo_Collision->SetupAttachment(ArmTwoAxis_Point);
	ArmTwo_Collision->SetRelativeLocation(FVector(-253.58f, 0.f, 87.02f));
	ArmTwo_Collision->SetRelativeRotation(FRotator(-70.f, -180.f, -180.f));

	// hand collision
	Hand_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand_Col"));
	Hand_Collision->SetupAttachment(Hand_Point);
	Hand_Collision->SetRelativeLocation(FVector(-253.58f, 0.f, 52.73f));
	Hand_Collision->SetRelativeRotation(FRotator(-70.f, -180.f, -180.f));

	// finger one collision
	FingerOne_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FingerOne_Col"));
	FingerOne_Collision->SetupAttachment(FingerOne_Point);
	FingerOne_Collision->SetRelativeLocation(FVector(-242.33f, 0.f, 27.78f));
	FingerOne_Collision->SetRelativeRotation(FRotator(-70.f, -180.f, -180.f));

	// finger two collision
	FingerTwo_Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FingerTwo_Col"));
	FingerTwo_Collision->SetupAttachment(FingerTwo_Point);
	FingerTwo_Collision->SetRelativeLocation(FVector(264.83f, 0.f, -27.78f));
	FingerTwo_Collision->SetRelativeRotation(FRotator(70.f, 0.f, 0.f));

#pragma endregion

}

// Called when the game starts or when spawned
void ARoboticArm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoboticArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Debugs the current selected axis on screen
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString(TEXT("Current Axis selected: ")).Append(FString::FromInt(currentAxisSelected)));

	RotateCamera(DeltaTime);
	MoveRobot(DeltaTime);
	MoveFingers(DeltaTime);
}

// Called to bind functionality to input
void ARoboticArm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// rotate robot on Q and E
	InputComponent->BindAxis("Rotate", this, &ARoboticArm::RotateArm);

	// swap rotate axis by scrolling the mouse wheel up and down
	InputComponent->BindAxis("SwapAxis", this, &ARoboticArm::SwapAxisToRotate);

	// set the inputcomponent up to scan for these axis
	InputComponent->BindAxis(TEXT("ForwardBack"));
	InputComponent->BindAxis(TEXT("LeftRight"));
	InputComponent->BindAxis(TEXT("MoveFinger"));
	InputComponent->BindAxis(TEXT("CameraUpDown"));
	InputComponent->BindAxis(TEXT("CameraLeftRight"));
}


void ARoboticArm::RotateCamera(float DeltaTime)
{
	float lr = InputComponent->GetAxisValue(TEXT("CameraLeftRight"));

	CameraRotPoint->AddLocalRotation(FRotator(0.f, lr * Camera_RotationSpeed * DeltaTime, 0.f));
}

// changes the current axis thats going to be rotated
void ARoboticArm::SwapAxisToRotate(float AxisChange)
{
	// add up current axis
	currentAxisSelected += AxisChange;

	// clamp axis number between 0 and 6
	// if reached first axis, jump to last
	if (currentAxisSelected < 0)
	{
		currentAxisSelected = 6;
	}
	// if reached last axis, jump to first
	else if (currentAxisSelected > 6)
	{
		currentAxisSelected = 0;
	}
}

// rotates the current selected axis if the rotate buttons are pressed
void ARoboticArm::RotateArm(float Direction)
{
	switch (currentAxisSelected)
	{
	case 0:
		ApplyYawAxisRotation(Direction, Base_Point, Base_MoveSpeed);
		break;
	case 1:
		ApplyYawAxisRotation(Direction, BaseSwingArm_Point, BaseSwingArm_MoveSpeed);
		break;
	case 2:
		ApplyYawAxisRotation(Direction, ArmOne_Point, ArmOneSwing_MoveSpeed);
		break;
	case 3:
		ApplyYawAxisRotation(Direction, ArmOneAxis_Point, ArmOneAxis_MoveSpeed);
		break;
	case 4:
		ApplyYawAxisRotation(Direction, ArmTwo_Point, ArmTwoSwing_MoveSpeed);
		break;
	case 5:
		ApplyYawAxisRotation(Direction, ArmTwoAxis_Point, ArmTwoAxis_MoveSpeed);
		break;
	case 6:
		ApplyYawAxisRotation(Direction, Hand_Point, HandAxis_MoveSpeed);
		break;
	default:
		break;
	}
}

// rotates the chosen point on its yaw / z axis
void ARoboticArm::ApplyYawAxisRotation(float Direction, USceneComponent* AxisToRotate, float MoveSpeed)
{
	AxisToRotate->AddLocalRotation(FRotator(0.f, Direction * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f), true);
}

// moves the robot forward, back, left and right based on the camera angle and axis input
void ARoboticArm::MoveRobot(float DeltaTime)
{
	// get direction vector
	FVector BaseLoc = Base_Point->GetComponentLocation();
	FVector CameraLoc = CameraDir->GetComponentLocation();

	FVector DirectionVector = FVector(BaseLoc.X - CameraLoc.X, BaseLoc.Y - CameraLoc.Y, 0.f);
	DirectionVector.Normalize();

	// get input from axis
	float fb = InputComponent->GetAxisValue(FName(TEXT("ForwardBack")));
	float lr = InputComponent->GetAxisValue(FName(TEXT("LeftRight")));

	// add forwardback movement to new Pos
	FVector newPos = DirectionVector * fb;
	// add left right movement
	newPos += FVector(DirectionVector.Y, -(DirectionVector.X), 0.f) * lr;
	// normalize movement to make diagonal movement not faster
	newPos.Normalize();

	// add movement speed
	newPos *= Robot_MovementSpeed * DeltaTime;

	// apply move
	AddActorWorldOffset(newPos, true);
}

// 
void ARoboticArm::MoveFingers(float DeltaTime)
{
	float fingerAxis = InputComponent->GetAxisValue(TEXT("MoveFinger"));

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString(TEXT("Finger One Point Pitch: ")).Append(FString::SanitizeFloat(FingerOne_Point->GetRelativeRotation().Pitch)));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString(TEXT("Finger Two Point Pitch: ")).Append(FString::SanitizeFloat(FingerTwo_Point->GetRelativeRotation().Pitch)));


	// check if fingers should rotate outside
	if (fingerAxis < 0)
	{
		// check if new position would be bigger than clamp angle
		if (FingerOne_Point->GetRelativeRotation().Pitch + (-fingerAxis) * Finger_MoveSpeed * DeltaTime > fingerClampAngleOne)
		{
			// dont apply new rotation
			return;
		}
	}
	// if fingers should rotate inside
	else if (fingerAxis > 0)
	{
		if (FingerOne_Point->GetRelativeRotation().Pitch + (-fingerAxis) * Finger_MoveSpeed * DeltaTime < fingerClampAngleTwo)
		{
			// dont apply new rotation
			return;
		}
	}

	// apply new rotation
	FingerOne_Point->AddLocalRotation(FRotator(-fingerAxis * Finger_MoveSpeed * DeltaTime, 0.f, 0.f), true);

	// apply new rotation
	FingerTwo_Point->AddLocalRotation(FRotator(fingerAxis * Finger_MoveSpeed * DeltaTime, 0.f, 0.f), true);
}

// calculates the yaw rotation and saves it in a preset rotator to be called in the anim BP
void ARoboticArm::CalculateYawRotation_AnimBP(float Direction, FName BoneName, float MoveSpeed, FRotator Output)
{
	FRotationConversionCache RelativeRotationCache;

	// get current rotation from bone
	FRotator currentBoneRotation = RelativeRotationCache.QuatToRotator(RoboticArmMesh->GetBoneQuaternion(BoneName, EBoneSpaces::ComponentSpace));

	// create new rotator to rotate by
	FRotator rotBy = FRotator::FRotator(0.f, Direction * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f);

	// convert rotator to quaternion
	const FQuat CurRelRotQuat = RelativeRotationCache.RotatorToQuat(currentBoneRotation);

	// get new pos in quaternion
	const FQuat NewRelRotQuat = CurRelRotQuat * rotBy.Quaternion();

	Output = NewRelRotQuat.Rotator();
}

// rotates the chosne bone of the poseable mesh
void ARoboticArm::RotateYaw(float Direction, FName BoneName, float MoveSpeed)
{
	FRotationConversionCache RelativeRotationCache;

	// get current rotation from bone
	FRotator currentBaseRotation = RoboticArm->GetBoneRotationByName(BoneName, EBoneSpaces::ComponentSpace);

	// create new rotator to rotate by
	FRotator rotBy = FRotator::FRotator(0.f, Direction * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f);

	// convert rotator to quaternion
	const FQuat CurRelRotQuat = RelativeRotationCache.RotatorToQuat(currentBaseRotation);

	// get new pos in quaternion
	const FQuat NewRelRotQuat = CurRelRotQuat * rotBy.Quaternion();

	// set new bone rotation
	RoboticArm->SetBoneRotationByName(BoneName, RelativeRotationCache.QuatToRotator(NewRelRotQuat), EBoneSpaces::ComponentSpace);
}