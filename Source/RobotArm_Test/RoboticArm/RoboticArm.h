// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RoboticArm.generated.h"

class UPoseableMeshComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class ROBOTARM_TEST_API ARoboticArm : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARoboticArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// camera rotation point
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
		USceneComponent* CameraRotPoint = nullptr;

	// camera component
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
		USceneComponent* CameraDir = nullptr;

	void RotateCamera(float DeltaTime);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float Camera_RotationSpeed = 100.f;

#pragma region --- Movement Speeds ---

	// speed of roboter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float Robot_MovementSpeed = 100.f;

	// base_rotateZ
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float Base_MoveSpeed = 100.0f;

	// base_swingArm
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float BaseSwingArm_MoveSpeed = 100.0f;

	// arm1_swing
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float ArmOneSwing_MoveSpeed = 100.0f;

	// arm1_rotateAxis
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float ArmOneAxis_MoveSpeed = 100.0f;

	// arm2_swing
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float ArmTwoSwing_MoveSpeed = 100.0f;

	// arm2_rotateAxis
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float ArmTwoAxis_MoveSpeed = 100.0f;

	// hand_rotateAxis
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float HandAxis_MoveSpeed = 100.0f;

	// finger1_translateX | finger2_translateX
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement Speeds")
		float Finger_MoveSpeed = 100.0f;

#pragma endregion

#pragma region --- Axis Components ---
	// swaps the current selected axis
	void SwapAxisToRotate(float AxisChange);

	// rotates the arm with the current selected axis
	void RotateArm(float Direction);

	// current axis selected
	int currentAxisSelected = 0;
#pragma endregion

#pragma region --- Collision and rotation points - static mesh build ---

	// applies the axis rotation to yaw / z axis
	void ApplyYawAxisRotation(float Direction, USceneComponent* AxisToRotate, float MoveSpeed);

	// moves the robot
	void MoveRobot(float DeltaTime);

	// move fingers
	void MoveFingers(float DeltaTime);

	// base
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* Base_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* BaseOne_Collision = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* BaseTwo_Collision = nullptr;

	// base swing arm
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* BaseSwingArm_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* BaseSwingArm_Collision = nullptr;

	// arm one
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* ArmOne_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* ArmOne_Collision = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* ArmOneAxis_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* ArmOneAxis_Collision = nullptr;

	// arm two
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* ArmTwo_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* ArmTwo_Collision = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* ArmTwoAxis_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* ArmTwoAxis_Collision = nullptr;

	// hand
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* Hand_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* Hand_Collision = nullptr;

	// finger clamp angles
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Robotic Arm")
		float fingerClampAngleOne = 35.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Robotic Arm")
		float fingerClampAngleTwo = -25.f;

	// finger one
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* FingerOne_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* FingerOne_Collision = nullptr;

	// finger two
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		USceneComponent* FingerTwo_Point = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm Collision")
		UStaticMeshComponent* FingerTwo_Collision = nullptr;

#pragma endregion

#pragma region --- Poseable Mesh Components ---
	// Mesh component of the robotic arm to make it moveable in C++ | can't apply any collision sadly
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm")
		UPoseableMeshComponent* RoboticArm = nullptr;

	// Rotates bone on yaw axis
	void RotateYaw(float Direction, FName BoneName, float MoveSpeed);
#pragma endregion

#pragma region --- Anim Blueprint Try ---

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Robotic Arm")
		USkeletalMeshComponent* RoboticArmMesh = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Robotic Arm")
		void CalculateYawRotation_AnimBP(float Direction, FName BoneName, float MoveSpeed, FRotator Output);

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator Base_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator BaseSwingArm_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator ArmOneSwing_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator ArmOneAxis_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator ArmTwoSwing_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator ArmTwoAxis_Rotator = FRotator();

	UPROPERTY(BlueprintReadOnly, Category = "Robotic Arm")
		FRotator HandAxis_Rotator = FRotator();

#pragma endregion

};
