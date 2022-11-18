#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class TESTCPP_API ACollidingPawn : public APawn
{
    GENERATED_BODY()

public:
    // ���ô�Pawn���Ե�Ĭ��ֵ
    ACollidingPawn();

protected:
    // ��Ϸ��ʼ������ʱ����
    virtual void BeginPlay() override;

public:
    // ��֡����
    virtual void Tick(float DeltaSeconds) override;

    // �����Խ������������
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