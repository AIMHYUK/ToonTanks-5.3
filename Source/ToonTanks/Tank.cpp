// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


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
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllRef = Cast<APlayerController>(GetController());

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FHitResult HitResult;
    if(PlayerControllRef)
    {
        PlayerControllRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
            );
        
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::Move(float Value)
{
    FVector DeltaLocation(0.f);
    // x = Value * DeltaTime * Speed
    DeltaLocation.X = Speed * UGameplayStatics::GetWorldDeltaSeconds(this) * Value; //월드컨텍스트 = this
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    //Yaw = Value * TurnRate * DT
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}
