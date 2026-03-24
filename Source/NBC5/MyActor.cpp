//MyActor.cpp

#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//맴버 변수 초기화
	Steps = 0;
	MoveCooldown = 0.0;
	EventCount = 0;
	Origin = GetActorLocation();
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	//시작 위치 고정
	SetActorLocation(FVector(0, 50, 0));

	GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Cyan, FString::Printf(TEXT("시작합니다!")), true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//이동 쿨타임 끝나면
	if (Steps < 10 && MoveCooldown <= 0) {
		Steps++;
		MoveCooldown += 2;	//2초마다 반복
		if (FMath::FRand() < 0.5) { //50%확률로 이동
			Move();
		}
		else {	//50%확률로 회전
			Rotate();
		}
		if (FMath::FRand() < 0.5) { //50%확률로 이벤트 발동
			SimpleEvent();
		}
	}
	else if (Steps == 10) {
		Steps++;
		GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Orange, FString(TEXT("이동이 끝났습니다!")), true);
		GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Red, FString::Printf(TEXT("총 이동 거리: %f"), FVector::Dist(Origin, GetActorLocation())), true);
		GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Red, FString::Printf(TEXT("이벤트 발생 횟수: %d"), EventCount), true);	//이벤트 발생횟수 출력
	}
	else {	//쿨타임중이면
		MoveCooldown -= DeltaTime;
	}
}

void AMyActor::Move() {	//전방으로 이동
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * MoveDistance);
	GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Red, FString::Printf(TEXT("큐브가 움직였습니다: (%f , %f)"), GetActorLocation().X, GetActorLocation().Y), true);
}

void AMyActor::Rotate(){ //yaw 90도 회전
	SetActorRotation(GetActorRotation() + FRotator(0,90,0));
	GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Green, FString::Printf(TEXT("큐브가 회전했습니다: %f"), GetActorRotation().Yaw), true);
}

void AMyActor::SimpleEvent(){	//이벤트 메세지 출력
	EventCount++;
	GEngine->AddOnScreenDebugMessage(-1, 60.0, FColor::Magenta, FString::Printf(TEXT("이벤트가 호출됬습니다!")), true);
}
