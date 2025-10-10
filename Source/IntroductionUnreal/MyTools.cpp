#include "MyTools.h"

void UMyTools::DebugLog(const FString& Message)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *Message)
}

void UMyTools::DebugLogWarning(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message)
}

void UMyTools::DebugLogError(const FString& Message)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Message)
}

FVector UMyTools::MyUnclampedLerp(const FVector A, FVector B, float T)
{
	FVector Result = FVector();

	Result.X = A.X * (1 - T) + B.X * T;
	Result.Y = A.Y * (1 - T) + B.Y * T;
	Result.Z = A.Z * (1 - T) + B.Z * T;

	return Result;
}

float UMyTools::MyClamp(float Value, float Min, float Max)
{
	if (Value < Min)
		return Min;

	if (Value > Max)
		return Max;

	return Value;
}

FVector UMyTools::MyLerp(FVector A, FVector B, float T)
{
	T = UMyTools::MyClamp(T, 0, 1);
	return UMyTools::MyUnclampedLerp(A, B, T);
}

FVector UMyTools::BezierInterp(const TArray<FVector>& Points, float Alpha)
{
	//Si il n'y a pas de point on ne peut pas effectuer l'interpolation
	if (Points.Num() == 0)
		return FVector();

	TArray<FVector> InitialLerpPoints = Points;
	TArray<FVector> LerpPoints = TArray<FVector>();

	//Num() => taille d'un array
	while (InitialLerpPoints.Num() > 1)
	{
		//On passe dans chaque point en s'arrêtant à l'avant dernier
		//car on utilise 2 points par tour de boucle (i et i + 1)
		for (int i = 0; i < InitialLerpPoints.Num() - 1; i++)
		{
			//On effectue le lerp entre les deux points et on stock le résultat
			FVector NewPoint = FMath::Lerp(InitialLerpPoints[i], InitialLerpPoints[i + 1], Alpha);
			LerpPoints.Add(NewPoint);
		}

		//On met nos résultat dans les point initiaux pour le prochain tour de boucle
		InitialLerpPoints = LerpPoints;
		LerpPoints = TArray<FVector>();
	}

	//On retourne le résultat
	return InitialLerpPoints[0];
}
