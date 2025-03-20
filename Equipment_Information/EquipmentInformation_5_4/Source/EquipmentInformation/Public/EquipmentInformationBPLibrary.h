// Copyright H.D OWL. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EquipmentInformationBPLibrary.generated.h"



UENUM()
enum class ESpecificInfoCPU : uint8
{
    Company,
    Name,
    Number,
    Series,
};

UENUM()
enum class ESpecificInfoGPU : uint8
{
    Company,
    Name,
    Mark,
    Model,
    MinimumModel,
    Series,
};

USTRUCT(BlueprintType)
struct FDisplayInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "info")
    FString Name;

    UPROPERTY(BlueprintReadOnly, Category = "info")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "info")
    int32 NativeWidth = 0;

    UPROPERTY(BlueprintReadOnly, Category = "info")
    int32 NativeHeight = 0;

    UPROPERTY(BlueprintReadOnly, Category = "info")
    FIntPoint MaxResolution = FIntPoint(ForceInitToZero);

    UPROPERTY(BlueprintReadOnly, Category = "info")
    bool bIsPrimary = false;

    UPROPERTY(BlueprintReadOnly, Category = "info")
    int32 DPI = 0;


    //Default constructor
    FDisplayInfo()
    {
        Name = FString("");
        ID = FString("");
        NativeWidth = 0;
        NativeHeight = 0;
        MaxResolution = FIntPoint(ForceInitToZero);
        bIsPrimary = false;
        DPI = 0;
    }

    // Custom constructor
    FDisplayInfo(const FString &InName, const FString &InID, int32 InNativeWidth, int32 InNativeHeight, 
        const FIntPoint &InMaxResolution, bool InbIsPrimary, int32 InDPI)
        : Name(InName),
        ID(InID),
        NativeWidth(InNativeWidth),
        NativeHeight(InNativeHeight),
        MaxResolution(InMaxResolution),
        bIsPrimary(InbIsPrimary),
        DPI(InDPI)
    {
    }
};

UCLASS()
class UEquipmentInformationBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()

    //CPU

    UFUNCTION(BlueprintPure, Category = "Equipment Information | CPU", DisplayName = "Get CPU Info", meta = (ToolTip = "Get CPU Info", Keywords = "CPU cpu Information Info"))
    static void GetCPUInfo(FString &Info, int &Core);

    UFUNCTION(BlueprintPure, Category = "Equipment Information | CPU", DisplayName = "Get Specific Info (CPU)", meta = (ToolTip = "Get Specific Info (CPU)", Keywords = "CPU cpu Information Info"))
    static void GetSpecificInfoCPU(FString Info, ESpecificInfoCPU SpecificInformationToReceived, FString &SpecificInfo);

    //GPU                                                                        

    UFUNCTION(BlueprintPure, Category = "Equipment Information | GPU", DisplayName = "Get GPU Info", meta = (ToolTip = "Get GPU Info", Keywords = "GPU gpu Information Info"))
    static void GetGPUInfo(FString &Info);

    UFUNCTION(BlueprintPure, Category = "Equipment Information | GPU", DisplayName = "Get Specific Info (GPU)", meta = (ToolTip = "Get Specific Info (GPU)", Keywords = "GPU gpu Information Info"))
    static void GetSpecificInfoGPU(FString Info, ESpecificInfoGPU SpecificInformationToReceived, FString &SpecificInfo);

    // RAM

    UFUNCTION(BlueprintPure, Category = "Equipment Information | RAM", DisplayName = "Get RAM Info", meta = (ToolTip = "Get RAM Info", Keywords = "RAM ram Information Info"))
    static void GetRAMInfo(float &TotalPhysicalMemory, float &UsedPhysicalMemory, float &FreePhysicalMemory);

    // Display

    UFUNCTION(BlueprintPure, Category = "Equipment Information | Display", DisplayName = "Get Displays Info", meta = (ToolTip = "Get Displays Info", Keywords = "Displays displays Display display Information Info"))
    static void GetDisplaysInfo(TArray<FDisplayInfo> &Displays, float &MaxFPSPrimaryMonitor);
};
