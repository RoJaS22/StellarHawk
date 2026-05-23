// Fill out your copyright notice in the Description page of Project Settings.


#include "AtacarState.h"
#include "PerseguirState.h"
#include "PatrullarState.h"
#include "NaveEnemiga.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

void UAtacarState::EntrarState(ANaveEnemiga* Nave)
{
    // Al entrar al estado de ataque, forzamos que pueda disparar casi de inmediato
    // asignándole un valor alto al temporizador.
    //TiempoDesdeUltimoDisparo= Nave->CadenciaDisparo;

  
}

void UAtacarState::ActualizarState(ANaveEnemiga* Nave, float DeltaTime)
{
    if (!Nave) return;

    // --- 1. VERIFICAR SI PERDIMOS LA VISIÓN ---
    if (!Nave->VeAlJugador())
    {
        Nave->CambiarState(NewObject<UPatrullarState>(Nave));
        return;
    }

    APawn* Jugador = UGameplayStatics::GetPlayerPawn(Nave->GetWorld(), 0);
    if (!Jugador) return;

    FVector UbicacionActual = Nave->GetActorLocation();
    FVector UbicacionJugador = Jugador->GetActorLocation();
    float DistanciaAlJugador = FVector::Dist(UbicacionActual, UbicacionJugador);

    // --- 2. TRANSICIÓN A CHASE (Con Histéresis) ---
    // Multiplicamos por 1.1f (10% extra) para crear una zona de amortiguación.
    // Esto evita que la IA cambie de estado erráticamente si la distancia fluctúa.
    if (DistanciaAlJugador > (Nave->RangoAtaque * 1.1f))
    {
        Nave->CambiarState(NewObject<UPerseguirState>(Nave));
        return;
    }

    // --- 3. ROTAR HACIA EL JUGADOR ---
    FVector Direccion = (UbicacionJugador - UbicacionActual).GetSafeNormal();
    FRotator RotacionObjetivo = UKismetMathLibrary::MakeRotFromX(Direccion);
    FRotator RotacionSuave = FMath::RInterpTo(Nave->GetActorRotation(), RotacionObjetivo, DeltaTime, Nave->VelocidadRotacion * 2.0f);
    Nave->SetActorRotation(RotacionSuave);

    // --- 4. LÓGICA DE DISPARO ---
    // Aumentamos el temporizador con el tiempo transcurrido en este frame
    
    TiempoDesdeUltimoDisparo += DeltaTime;
    if (TiempoDesdeUltimoDisparo >= Nave->CadenciaDisparo && Nave->Proyectil)
   // if(true)
    {
        /*
        // Reseteamos el temporizador
        TiempoDesdeUltimoDisparo = 0.0f;

        // Calculamos dónde aparecerá el proyectil.
        // Lo adelantamos unos 100 cm para que no colisione con la propia nave enemiga al nacer.
        FVector UbicacionSpawn = UbicacionActual + (Nave->GetActorForwardVector() * 50.0f);
        FRotator RotacionSpawn = Nave->GetActorRotation();

   

        //ParametrosSpawn.Owner = Nave;
       // ParametrosSpawn.Instigator = Nave;

        // Spawneamos el proyectil en el mundo
        Nave->GetWorld()->SpawnActor<AActor>(Nave->Proyectil, UbicacionSpawn, RotacionSpawn);
        // Opcional: Aquí podrías reproducir un sonido de disparo usando UGameplayStatics::PlaySoundAtLocation
        */
        TiempoDesdeUltimoDisparo -= Nave->CadenciaDisparo;

        // Calculamos la ubicación (Idealmente, en el futuro deberías usar un "Socket" del modelo 3D)
        FVector UbicacionSpawn = UbicacionActual + (Nave->GetActorForwardVector() * 50.0f); // Ajustado a 100 según tu comentario
        FRotator RotacionSpawn = Nave->GetActorRotation();

        // Configuramos los parámetros de instanciación
        FActorSpawnParameters ParametrosSpawn;
        ParametrosSpawn.Owner = Nave;      // El dueño es este enemigo
        ParametrosSpawn.Instigator = Nave->GetInstigator(); // El instigador (quién causará el daño)

        // Forzamos que el proyectil aparezca siempre, aunque esté tocando algo
        ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        // Spawneamos el proyectil pasándole los parámetros
        GetWorld()->SpawnActor<AActor>(Nave->Proyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
    }
    
}

void UAtacarState::SalirState(ANaveEnemiga* Nave)
{
}
