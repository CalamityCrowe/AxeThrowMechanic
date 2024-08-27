// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEntity.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputData;
UCLASS()
class PLAYABLEPORTFOLIO_API ABaseEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UInputData* GetInputs() { return Inputs; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	USpringArmComponent* GetSpringArm() { return SpringArm; }
	UCameraComponent* GetCamera() { return Camera; }
	virtual void SetupActions(UInputComponent* PlayerInputComponent);

private:
	UFUNCTION()
	virtual void Move(const FInputActionValue& Value);
	UFUNCTION()
	virtual void RotateCamera(const FInputActionValue& Value);

	void BindMappingContexts(UInputComponent* PlayerInputComponent);


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent>Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent>SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputData> Inputs;

};
