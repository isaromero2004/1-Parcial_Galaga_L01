// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilGrande.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
AProyectilGrande::AProyectilGrande()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileGrandeAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	// Create mesh component for the projectile sphere
	ProyectilGrandeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProyectileMesh0"));
	ProyectilGrandeMesh->SetStaticMesh(ProjectileGrandeAsset.Object);
	ProyectilGrandeMesh->SetupAttachment(RootComponent);
	ProyectilGrandeMesh->BodyInstance.SetCollisionProfileName("Proyectile");
	ProyectilGrandeMesh->OnComponentHit.AddDynamic(this, &AProyectilGrande::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProyectilGrandeMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProyectilGrandeMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}
void AProyectilGrande::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}