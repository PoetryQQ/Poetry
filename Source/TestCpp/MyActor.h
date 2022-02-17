// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TESTCPP_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float DamagePerSecond;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PostInitProperties();
	// UFUNCTION() 宏负责处理将C++函数公开给反射系统。BlueprintCallable 选项将其公开给蓝图虚拟机
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CalculateValues();
	// 蓝图可调用的 打印所有property name  的函数 
	UFUNCTION(BlueprintCallable, Category = "MyDebug")
	void PrintNameOfProperty();

	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void CalledFromCpp(const FString& str);

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent);
#endif

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
