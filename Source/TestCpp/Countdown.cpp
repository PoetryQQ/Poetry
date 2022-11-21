// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextRenderComponent.h"
#include "Countdown.h"

//����Ĭ��ֵ
ACountdown::ACountdown()
{
    //����Actor��Ϊ��֡����Tick()��������˹��ܣ��ɹر���������ܡ�
    PrimaryActorTick.bCanEverTick = false;

    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;

    CountdownTime = 3;
}

// ��Ϸ��ʼ������ʱ����
void ACountdown::BeginPlay()
{
    Super::BeginPlay();

    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
}

// ��֡����
void ACountdown::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ACountdown::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        //������ɣ�ֹͣ���ж�ʱ����
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        //��ʱ������ʱ��ִ��Ҫִ�е����������
        CountdownHasFinished();
    }
}

void ACountdown::CountdownHasFinished_Implementation()
{
    //��Ϊ�������
    CountdownText->SetText(TEXT("GO!"));
}