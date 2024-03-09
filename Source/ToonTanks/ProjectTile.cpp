// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectTile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectTile::AProjectTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //발사체는 틱이 필요없음

	ProjectTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectTile Mesh"));
	RootComponent = ProjectTileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PPProjectile"));
	ProjectileMovementComponent->MaxSpeed = 1300;
	ProjectileMovementComponent->InitialSpeed = 1300;



}

// Called when the game starts or when spawneddf
void AProjectTile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectTileMesh->OnComponentHit.AddDynamic(this, &AProjectTile::OnHit);
}

// Called every frame
void AProjectTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectTile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

	}
}
