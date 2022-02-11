// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"

#include <Eigen/Dense>

#include "SimpleIKCharacter.generated.h"

UCLASS(config=Game)
class ASimpleIKCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASimpleIKCharacter();
	void Tick(float DeltaTime) override;

	// functions used for IK
	bool CheckHierarchy(FName TipBoneName, FName RootBoneName);
	TArray<FName> GetBoneChain(FName TipBoneName, FName RootBoneName);
	void SolveCCD(FName TipBoneName, FName RootBoneName, FVector TargetLocation, float Precision, int32 MaxIterations);
	void SolveFABRIK(FName TipBoneName, FName RootBoneName, FVector TargetLocation, float Precision, int32 MaxIterations);
	void SolveJacobianTranspose(FName TipBoneName, FName RootBoneName, FVector TargetLocation, float Precision);
	void SolveJacobianPinv(FName TipBoneName, FName RootBoneName, FVector TargetLocation, float Precision);
	void SolveJacobianDLS(FName TipBoneName, FName RootBoneName, FVector TargetLocation, float Precision);
	Eigen::MatrixXf GetJacobianMatrix(FName TipBoneName, FName RootBoneName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Category = "IK")
	UPoseableMeshComponent* poseableMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "IK")
	TArray<FName> BoneNames;

	UPROPERTY(EditAnywhere, Category = "IK")
	AActor* Target;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

