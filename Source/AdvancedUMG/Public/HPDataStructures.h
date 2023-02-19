#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Category = "UVP")
enum class EUVPActorType :uint8
{
	StaticMesh,  //actor which is static mesh
	Sprite,   //actor with planar image
	Text3D,   // text 3D
	Slug3D, // slug 3D text
	Slug2D   // slug 2D text
};

UENUM(BlueprintType, Category = "UVP")
//enumerates UE shader params types
enum class EUVPShaderParamType :uint8
{
	Sampler,
	Vector,//Vector  is alway  color in material
	Scalar 
 
};

//actor prop can be float,string,integer
//for now we avoid polymorphysm by packing both string and numeric 
struct UVPActorPropValue
{
	FString sval;//can be url or asset file name

	union //any numeric value
	{
		float fval;
		int   ival;
	};
};

struct UVMaterialPropValue
{
	EUVPShaderParamType shaderType;
	FString sval;//can be url for texture asset

	union //any numeric value
	{
		float    fparam; //float uniform
		uint32   cparam; //color uniform
	};
};

struct UVPDynamicActorData
{

	AActor* actor;
	//unique set of personalized props per JSActorType. Transforms are not part of it
	TMap<FString, UVPActorPropValue> actorProps;
	//param name, param type
	TMap<FName, UVMaterialPropValue> materialParams;
	EUVPActorType actorType;
	bool externalStaticMesh = false;// in case of static mesh actor has dynamic 3d model this one must be true
};