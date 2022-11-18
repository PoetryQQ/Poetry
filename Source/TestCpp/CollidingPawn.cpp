// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/KismetMathLibrary.h>

// 设置默认值
ACollidingPawn::ACollidingPawn()
{
    // 设置该Pawn以逐帧调用Tick()。如无需此功能，可关闭以提高性能。
    PrimaryActorTick.bCanEverTick = true;

    // 根组件将成为对物理反应的球体
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

    // 创建并放置网格体组件，以便查看球体位置
    UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    SphereVisual->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
        SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        SphereVisual->SetWorldScale3D(FVector(0.8f));
    }

    // 创建可激活或停止的粒子系统
    OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
    OurParticleSystem->SetupAttachment(SphereVisual);
    OurParticleSystem->bAutoActivate = true;
    OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
    if (ParticleAsset.Succeeded())
    {
        OurParticleSystem->SetTemplate(ParticleAsset.Object);
    }

    // 使用弹簧臂给予摄像机平滑自然的运动感。
    USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.0f;

    // 创建摄像机并附加到弹簧臂
    UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    // 控制默认玩家
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // 创建移动组件的实例，并要求其更新根组件。
    OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;
    // 创建并放置网格体组件，以便查看球体位置
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

// 游戏开始或生成时调用
void ACollidingPawn::BeginPlay()
{
    Super::BeginPlay();

}

// 逐帧调用
void ACollidingPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector upVector = SphereSmall->GetUpVector();
    //在Tick函数中使其围绕上向量旋转1度
    FRotator rotator = UKismetMathLibrary::RotatorFromAxisAndAngle(upVector, 1);
    SphereSmall->AddWorldRotation(rotator);

}

// 调用以将功能与输入绑定
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