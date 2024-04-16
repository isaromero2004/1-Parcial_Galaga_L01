// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaTransporte.h"
#include "Galaga_USFX_L01Projectile.h"

ANaveEnemigaTransporte::ANaveEnemigaTransporte()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);

}

void ANaveEnemigaTransporte::BeginPlay() 
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(TiempoDisparo, this, &ANaveEnemigaTransporte::Disparar, 2.0f, true);
}

void ANaveEnemigaTransporte::Mover(float DeltaTime)
{

    FVector PosicionActual = GetActorLocation();
    float LimiteDerecho = 1000.0f;
    float LimiteIzquierdo = -1000.0f;

    // Definir la velocidad de movimiento horizontal
    float VelocidadHorizontal = 500.0f;

    // Calcular el desplazamiento horizontal para este fotograma
    float DesplazamientoHorizontal = VelocidadHorizontal * DeltaTime;

    // Verificar si la nave está moviéndose hacia derecha o izquierda

    if (DireccionMovimientoHorizontal == 1) // Movimiento hacia derecha
    {


        // Mover la nave hacia derecha
        FVector NuevaPosicion = PosicionActual + FVector(0.0f, DesplazamientoHorizontal - 1.0f, 0.0f);
        if (NuevaPosicion.Y <= LimiteDerecho)
        {
            SetActorLocation(NuevaPosicion);
        }
        else
        {
            // Si alcanza el límite superior, cambiar la dirección de movimiento a hacia izquierda
            DireccionMovimientoHorizontal = -1;
        }
    }
    else // Movimiento hacia izquierda
    {
        // Mover la nave hacia izquierda
        FVector NuevaPosicion = PosicionActual - FVector(0.0f, DesplazamientoHorizontal - 1.0f, 0.0f);
        if (NuevaPosicion.Y >= LimiteIzquierdo)
        {
            SetActorLocation(NuevaPosicion);
        }
        else
        {
            // Si alcanza el límite de la izquierda, cambiar la dirección de movimiento a hacia la derecha
            DireccionMovimientoHorizontal = 1;
            SetActorLocation(FVector(NuevaPosicion.X, NuevaPosicion.Y - 100.0f, NuevaPosicion.Z));
        }
    }
}


void ANaveEnemigaTransporte::Disparar()
{
    FVector PosicionNave = GetActorLocation();
    FVector OffSet = FVector(0.0f, 90.0f, 0.0f);
    FRotator Rotacion = FRotator(180, 0, 0);

    UWorld* const World = GetWorld();
    if (World != nullptr)
    {
        // spawn the projectile
        World->SpawnActor<AGalaga_USFX_L01Projectile>(PosicionNave + OffSet, Rotacion);
    }
}

void ANaveEnemigaTransporte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
	
}
