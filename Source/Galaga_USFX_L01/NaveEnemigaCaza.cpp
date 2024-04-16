// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaCaza.h"
#include "ProyectilGrande.h"

ANaveEnemigaCaza::ANaveEnemigaCaza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));
	//// Create the mesh component
	//mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
	
}

void ANaveEnemigaCaza::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(TiempoDisparo, this, &ANaveEnemigaCaza::Disparar, 2.0f, true);
}

void ANaveEnemigaCaza::Mover(float DeltaTime)
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

void ANaveEnemigaCaza::Disparar()
{
    FVector PosicionNave = GetActorLocation();
	FVector Offset= FVector(0.0f, 90.0f, 0.0f);
    FRotator Rotacion= FRotator(180,0,0);

    UWorld* const World = GetWorld();
    if (World != nullptr)
    {
		// spawn the projectile
		World->SpawnActor<AProyectilGrande>(PosicionNave + Offset, Rotacion);
	}

	
}


void ANaveEnemigaCaza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
    

}
