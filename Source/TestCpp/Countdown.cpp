// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextRenderComponent.h"
#include "Countdown.h"

//设置默认值
ACountdown::ACountdown()
{
    //将此Actor设为逐帧调用Tick()。如无需此功能，可关闭以提高性能。
    PrimaryActorTick.bCanEverTick = false;

    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;

    CountdownTime = 3;
}

// 游戏开始或生成时调用
void ACountdown::BeginPlay()
{
    Super::BeginPlay();

    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
}

// 逐帧调用
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
        //倒数完成，停止运行定时器。
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        //定时器结束时，执行要执行的特殊操作。
        CountdownHasFinished();
    }
}

void ACountdown::CountdownHasFinished_Implementation()
{
    //改为特殊读出
    CountdownText->SetText(TEXT("GO!"));
}