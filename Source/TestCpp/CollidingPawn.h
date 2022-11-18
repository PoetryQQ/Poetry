#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class TESTCPP_API ACollidingPawn : public APawn
{
    GENERATED_BODY()

public:
    // 设置此Pawn属性的默认值
    ACollidingPawn();

protected:
    // 游戏开始或生成时调用
    virtual void BeginPlay() override;

public:
    // 逐帧调用
    virtual void Tick(float DeltaSeconds) override;

    // 调用以将功能与输入绑定
    virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

    UPROPERTY(EditAnywhere)
    class UParticleSystemComponent* OurParticleSystem;

    UPROPERTY()
    class UCollidingPawnMovementComponent* OurMovementComponent;
    UPROPERTY()
    class UStaticMeshComponent* SphereSmall;

    virtual UPawnMovementComponent* GetMovementComponent() const override;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void Turn(float AxisValue);
    void ParticleToggle();
};