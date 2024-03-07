// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

ATank::ATank()
{
    MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    MySpringArm->SetupAttachment(RootComponent);

    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    MyCamera->SetupAttachment(MySpringArm);

}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}


void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
}