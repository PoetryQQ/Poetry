// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	this->CalledFromCpp("who is fire");
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateValues();
}

void AMyActor::CalculateValues()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

#if WITH_EDITOR
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	CalculateValues();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AMyActor::PrintNameOfProperty()
{
	// for (TFieldIterator<FProperty> PropIt(GetClass()); PropIt; ++PropIt)
	// {
	// 	FProperty *mypro = *PropIt;
	// 	// 对属性做一些事情
	// 	UKismetSystemLibrary::PrintString(this, mypro->GetName()); 
	// }
	//成员函数，并获取到函数中的所有参数
	// for (TFieldIterator<UFunction> i(GetClass());i;++i)
	// {
	// 	for (TFieldIterator<FProperty> j(*i);j;++j)
	// 	{
	// 		if (j->PropertyFlags & CPF_ReturnParm)
	// 		{
	// 			UKismetSystemLibrary::PrintString(this, *i->GetName());
	// 		}
	// 	}
	// }
	//接口
	for (int i=GetClass()->Interfaces.Num();i;--i)
	{
		FImplementedInterface* f = &(GetClass()->Interfaces[i-1]);
	}

}