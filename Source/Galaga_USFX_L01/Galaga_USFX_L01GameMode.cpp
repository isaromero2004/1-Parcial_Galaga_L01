// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01GameMode.h"
#include "Galaga_USFX_L01Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaTransporteG1.h"
#include "NaveEnemigaCaza.h"

AGalaga_USFX_L01GameMode::AGalaga_USFX_L01GameMode()
{
	// set default pawn class to our character class
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = AGalaga_USFX_L01Pawn::StaticClass();

	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L01GameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set the game state to playing
	FVector ubicacionInicioNavesEnemigasCaza = FVector(-500.0f, -1000.0f, 200.0f);
	FVector ubicacionInicioNavesEnemigasTransporte = FVector(200.0f, 1000.0f, 200.0f);
	FVector ubicacionInicioNavesEnemigasTransporteG1 = FVector(500.0f, 500.0f, 200.0f);
	//FVector ubicacionNave01 = FVector(-1000.0f, 500.0f, 250.0f);
	//FVector ubicacionNave02 = FVector(-500.0f, -500.0f, 250.0f);

	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (int i = 0; i < 5; i++) {
			FVector PosicionNaveActualCaza = FVector(ubicacionInicioNavesEnemigasCaza.X, ubicacionInicioNavesEnemigasCaza.Y + i * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaCaza* NaveEnemigaCazaTemporal = World->SpawnActor<ANaveEnemigaCaza>(PosicionNaveActualCaza, rotacionNave);

			//TANavesEnemigasCaza.Push(NaveEnemigaCazaTemporal);
			TANavesEnemigas.Push(NaveEnemigaCazaTemporal);
		}

		

		for (int j = 0; j < 5; j++) {
			FVector PosicionNaveActualTransporte = FVector(ubicacionInicioNavesEnemigasTransporte.X, ubicacionInicioNavesEnemigasTransporte.Y + j * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = GetWorld()->SpawnActor<ANaveEnemigaTransporte>(ANaveEnemigaTransporte::StaticClass(), ubicacionInicioNavesEnemigasTransporte, rotacionNave);
			for (int k = 0; k < 5; k++) {
				FVector PosicionNaveActualTransporteG1 = FVector(ubicacionInicioNavesEnemigasTransporteG1.X, ubicacionInicioNavesEnemigasTransporteG1.Y + k * 300, ubicacionInicioNavesEnemigasTransporteG1.Z);
				ANaveEnemigaTransporteG1* NaveEnemigaTransporteG1Temporal = World->SpawnActor<ANaveEnemigaTransporteG1>(PosicionNaveActualTransporteG1, rotacionNave);

				//TANavesEnemigasTransporte.Push(NaveEnemigaTransporteTemporal);
				TANavesEnemigasTransporte.Push(NaveEnemigaTransporteG1Temporal);
			}
			//TANavesEnemigasTransporte.Push(NaveEnemigaTransporteTemporal);
			TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
		}
		//for (int k = 0; k < 5; k++) {
		//		FVector PosicionNaveActualTransporteG1 = FVector(ubicacionInicioNavesEnemigasTransporteG1.X, ubicacionInicioNavesEnemigasTransporteG1.Y + k * 300, ubicacionInicioNavesEnemigasTransporteG1.Z);
		//		ANaveEnemigaTransporteG1* NaveEnemigaTransporteG1Temporal = World->SpawnActor<ANaveEnemigaTransporteG1>(PosicionNaveActualTransporteG1, rotacionNave);

		//		//TANavesEnemigasTransporte.Push(NaveEnemigaTransporteTemporal);
		//		TANavesEnemigasTransporte.Push(NaveEnemigaTransporteG1Temporal);
		//	}


		//NaveEnemigaTransporte01 = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionNave01, rotacionNave);
		//NaveEnemigaCaza01 = World->SpawnActor<ANaveEnemigaCaza>(ubicacionNave02, rotacionNave);

		TiempoTranscurrido = 0;
	}

	/*NaveEnemigaCaza01->SetPosicion(FVector(-500.0f, 500.0f, 200.0f));
	NaveEnemigaTransporte01->SetPosicion(FVector(500.0f, -500.0f, 200.0f));*/

}

void AGalaga_USFX_L01GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiempoTranscurrido++;

	if (TiempoTranscurrido >= 100)
	{
		int numeroEnemigo = FMath::RandRange(0, 9);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Hola estoy aqui")));


			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Entero: %d"), numeroEnemigo));
			
		}*/
		//TANavesEnemigas[numeroEnemigo]->PrimaryActorTick.bCanEverTick = false;
		TANavesEnemigas[numeroEnemigo]->SetVelocidad(0);
	}
}
