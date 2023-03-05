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
enum class EUVPActorPropType :uint8
{
	String,       //actor which is static mesh
	FloatValue,   //actor with planar image
	IntValue,     // text 3D
};

//enumerates UE shader params types
UENUM(BlueprintType, Category = "UVP")
enum class EUVPShaderParamType :uint8
{
	Sampler,
	Vector,//Vector  is alway  color in material
	Scalar ,
	HexColor // represented by string '0xFFFFFFFF
};

UENUM(BlueprintType, Category = "UVP")
enum class EUVPDynamicPropDataType :uint8
{
	FilePath, //for shader param string means Image file path
	Vector4, 
	Vector3, 
	ScalarInt,
	ScalarFloat,
	Color //Hex RGBA color  
	

};

//This one is needed for the UI cell so that when the Json
//writer retrives the data from the cell it can understand what type of data it is
UENUM(BlueprintType, Category = "UVP")
enum class EUVPDynamicPropType :uint8
{
	MaterialProp,
	ActorProp,
	TransformProp
};



//actor prop can be float,string,integer
//for now we avoid polymorphysm by packing both string and numeric 
struct UVPActorPropValue
{
	EUVPActorPropType propType;
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

struct UVPDynamicPropValue
{
	EUVPDynamicPropType     propType;
	EUVPDynamicPropDataType propDataType;

	//FString name;//this is prop name sucha as material param or unique prop name
	FString sval;//can be url for texture asset

	union //any numeric value
	{
		float    vval[4];
		float    fval;  //float uniform
		uint32   uival; //color uniform
	};
};

struct UVPDynamicActorData
{

	AActor* actor;
	//unique set of personalized props per JSActorType. Transforms are not part of it
	/*
	each entry in array is a row of data,where map->Key is the prop name
	*/

	typedef TMap<FString, UVPDynamicPropValue> DynamicPropsMap;

	typedef TArray<DynamicPropsMap> DynamicProps;

	DynamicProps props;

	
	//TMap<FString, UVPActorPropValue> actorProps;
	//param name, param type
	//TMap<FName, UVMaterialPropValue> materialParams;
	EUVPActorType actorType;
	bool externalStaticMesh = false;// in case of static mesh actor has dynamic 3d model this one must be true
};

 