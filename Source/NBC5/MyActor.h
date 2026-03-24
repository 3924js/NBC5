//MyActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NBC5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Origin;

	UPROPERTY(EditAnywhere, Category = "MyActor")
	double MoveDistance;

	int Steps;
	double MoveCooldown;
	int EventCount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Move();	//이동 함수

	void Rotate();	//회전 함수

	void SimpleEvent();	//이벤트 함수

};
