// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/KismetMathLibrary.h>

// ����Ĭ��ֵ
ACollidingPawn::ACollidingPawn()
{
    // ���ø�Pawn����֡����Tick()��������˹��ܣ��ɹر���������ܡ�
    PrimaryActorTick.bCanEverTick = true;

    // ���������Ϊ������Ӧ������
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

    // ����������������������Ա�鿴����λ��
    UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    SphereVisual->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
        SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        SphereVisual->SetWorldScale3D(FVector(0.8f));
    }

    // �����ɼ����ֹͣ������ϵͳ
    OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
    OurParticleSystem->SetupAttachment(SphereVisual);
    OurParticleSystem->bAutoActivate = true;
    OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
    if (ParticleAsset.Succeeded())
    {
        OurParticleSystem->SetTemplate(ParticleAsset.Object);
    }

    // ʹ�õ��ɱ۸��������ƽ����Ȼ���˶��С�
    USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.0f;

    // ��������������ӵ����ɱ�
    UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    // ����Ĭ�����
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // �����ƶ������ʵ������Ҫ������¸������
    OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;
    // ����������������������Ա�鿴����λ��
    SphereSmall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualSphere"));
    SphereSmall->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereSmallAssest(TEXT("/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180"));
    if (SphereSmallAssest.Succeeded())
    {
        SphereSmall->SetStaticMesh(SphereSmallAssest.Object);
        SphereSmall->SetRelativeLocation(FVector(90.0f, 0.0f, 90.0f));
        SphereSmall->SetWorldScale3D(FVector(1.f));
    }
    

}

// ��Ϸ��ʼ������ʱ����
void ACollidingPawn::BeginPlay()
{
    Super::BeginPlay();

}

// ��֡����
void ACollidingPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector upVector = SphereSmall->GetUpVector();
    //��Tick������ʹ��Χ����������ת1��
    FRotator rotator = UKismetMathLibrary::RotatorFromAxisAndAngle(upVector, 1);
    SphereSmall->AddWorldRotation(rotator);

}

// �����Խ������������
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
    Super::SetupPlayerInputComponent(InInputComponent);

    InInputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);


    InInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
    InInputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
    InInputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
    return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
    }
}

void ACollidingPawn::MoveRight(float AxisValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
    }
}

void ACollidingPawn::Turn(float AxisValue)
{
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += AxisValue;
    SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
    if (OurParticleSystem && OurParticleSystem->Template)
    {
        OurParticleSystem->ToggleActive();
    }
}