// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectTile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
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

	FollowingHitParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrail"));
	FollowingHitParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawneddf
void AProjectTile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectTileMesh->OnComponentHit.AddDynamic(this, &AProjectTile::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}


}

// Called every frame
void AProjectTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectTile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			
		}
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if(HitcameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitcameraShakeClass);
		}
		Destroy();
	}
}

