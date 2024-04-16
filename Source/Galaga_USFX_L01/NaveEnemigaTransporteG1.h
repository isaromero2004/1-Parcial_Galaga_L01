// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaTransporteG1.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveEnemigaTransporteG1 : public ANaveEnemigaTransporte
{
	GENERATED_BODY()

public:
		ANaveEnemigaTransporteG1();

protected:
	virtual void BeginPlay()override;
	virtual void Mover(float DeltaTime)override;
	virtual void Disparar()override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
