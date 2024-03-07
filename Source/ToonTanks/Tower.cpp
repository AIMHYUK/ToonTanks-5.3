// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //탱크까지 거리 찾기
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= FireRange)
        {
           RotateTurret(Tank->GetActorLocation());
        }
    }   

    //사정거리에 있으면 그 방향으로 회전


}

void ATower::BeginPlay()
{
    Super::BeginPlay();

   Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}