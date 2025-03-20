// Copyright H.D OWL. All rights reserved.

#include "EquipmentInformationBPLibrary.h"
#include "Windows/WindowsHWrapper.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericApplication.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "EquipmentInformation.h"

UEquipmentInformationBPLibrary::UEquipmentInformationBPLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

//CPU

void UEquipmentInformationBPLibrary::GetCPUInfo(FString &Info, int &Core)
{
    //Info
    Info = FWindowsPlatformMisc::GetCPUBrand();

    //Core
    Core = FPlatformMisc::NumberOfCores();
}

void UEquipmentInformationBPLibrary::GetSpecificInfoCPU(FString Info, ESpecificInfoCPU SpecificInformationToReceived, FString &SpecificInfo)
{
    //SpecificInfo
    FString CPUBrand = Info;
    FString BeforeAtSymbol;
    FString AfterAtSymbol;
    FString Number;
    FString Serie;
    bool IsAmd;

    CPUBrand.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
    IsAmd = BeforeAtSymbol.ToLower().Equals("amd");

    switch (SpecificInformationToReceived) 
    {
    case ESpecificInfoCPU::Company:
        SpecificInfo = BeforeAtSymbol;
        break;
    case ESpecificInfoCPU::Name:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        SpecificInfo = BeforeAtSymbol;
        break;
    case ESpecificInfoCPU::Number:
        if (IsAmd)
        {
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            SpecificInfo = BeforeAtSymbol;
        }
        else
        {
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            BeforeAtSymbol.Split(TEXT("-"), &Number, &Serie);
            SpecificInfo = Number;
        }
        break;
    case ESpecificInfoCPU::Series:
        if (IsAmd)
        {
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);

            FString SeriesComplet = BeforeAtSymbol;
            TCHAR firstChar = SeriesComplet[0];
            int firstNumber = (firstChar - TEXT('0'));
            int longeur = SeriesComplet.Len();
            TCHAR lastChar = SeriesComplet[(longeur - 1)];

            if (FChar::ToLower(lastChar) == 'x')
            {
                longeur = SeriesComplet.Len() - 1;
            }
            else if (FChar::ToLower(lastChar) == 'd')
            {
                longeur = SeriesComplet.Len() - 3;
            }
            else
            {
                SpecificInfo = "Error(1): Could not determine the series.";
                UE_LOG(LogTemp, Error, TEXT("Could not determine the series.(1)"));
            }

            if (longeur == 2)
            {
                SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 10));
            }
            else if (longeur == 3)
            {
                SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 100));
            }
            else if (longeur == 4)
            {
                SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 1000));
            }
            else
            {
                SpecificInfo = "Error(2): Could not determine the series.";
                UE_LOG(LogTemp, Error, TEXT("Could not determine the series.(2)"));
            }
        }
        else
        {
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
            BeforeAtSymbol.Split(TEXT("-"), &Number, &Serie);
            SpecificInfo = Serie;
        }
        break;
    }
}

//GPU

void UEquipmentInformationBPLibrary::GetGPUInfo(FString &Info)
{
    //Info
    Info = FPlatformMisc::GetPrimaryGPUBrand();
}

void UEquipmentInformationBPLibrary::GetSpecificInfoGPU(FString Info, ESpecificInfoGPU SpecificInformationToReceived, FString &SpecificInfo)
{
    //SpecificInfo
    FString GPUBrand = Info;
    FString BeforeAtSymbol;
    FString AfterAtSymbol;
    FString Model;
    FString MinimumModel;
    int32 CommaIndex;

    GPUBrand.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);

    switch (SpecificInformationToReceived)
    {
    case ESpecificInfoGPU::Company: 
        SpecificInfo = BeforeAtSymbol;
        break;
    case ESpecificInfoGPU::Name:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        SpecificInfo = BeforeAtSymbol;
        break;
    case ESpecificInfoGPU::Mark:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        SpecificInfo = BeforeAtSymbol;
        break;
    case ESpecificInfoGPU::Model:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        SpecificInfo = AfterAtSymbol;
        break;
    case ESpecificInfoGPU::MinimumModel:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);

        Model = AfterAtSymbol;
        CommaIndex = -1;

        if (Model.FindChar(' ', CommaIndex))
        {
            SpecificInfo = Model.Left(CommaIndex);
        }
        else
        {
            SpecificInfo = Model.Left(4);
        }
        break;
    case ESpecificInfoGPU::Series:
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);
        AfterAtSymbol.Split(TEXT(" "), &BeforeAtSymbol, &AfterAtSymbol);


        Model = AfterAtSymbol;
        CommaIndex = -1;

        if (Model.FindChar(' ', CommaIndex))
        {
            MinimumModel = Model.Left(CommaIndex);
        }
        else
        {
            MinimumModel = Model.Left(4);
        }


        TCHAR firstChar = MinimumModel[0];
        int firstNumber = (firstChar - TEXT('0'));
        int longeur = MinimumModel.Len();
        TCHAR lastChar = MinimumModel[(longeur - 1)];

        if (longeur == 2)
        {
            SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 10));
        }
        else if (longeur == 3)
        {
            SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 100));
        }
        else if (longeur == 4)
        {
            SpecificInfo = (*FString::Printf(TEXT("%d"), firstNumber * 1000));
        }
        break;
    }
}

//RAM

 void UEquipmentInformationBPLibrary::GetRAMInfo(float &TotalPhysicalMemory, float &UsedPhysicalMemory, float &FreePhysicalMemory)
{
    const FPlatformMemoryStats Stats = FPlatformMemory::GetStats();

    //TotalPhysicalMemory
    TotalPhysicalMemory = Stats.TotalPhysical / (1024.0f * 1024.0f * 1024.0f);

    //UsedPhysicalMemory
    //UsedPhysicalMemory = Stats.UsedPhysical / (1024.0f * 1024.0f * 1024.0f);
    UsedPhysicalMemory = (Stats.TotalPhysical - Stats.AvailablePhysical) / (1024.0f * 1024.0f * 1024.0f);

    //FreePhysicalMemory
    FreePhysicalMemory = Stats.AvailablePhysical / (1024.0f * 1024.0f * 1024.0f);
}

 //Displays

void UEquipmentInformationBPLibrary::GetDisplaysInfo(TArray<FDisplayInfo>& Displays, float& MaxFPSPrimaryMonitor)
{
    //Displays
    FDisplayMetrics DisplaysInfo;
    FDisplayMetrics::RebuildDisplayMetrics(DisplaysInfo);

    for (const FMonitorInfo& ArrayElement : DisplaysInfo.MonitorInfo)
    {
        Displays.Add(FDisplayInfo(ArrayElement.Name, ArrayElement.ID, ArrayElement.NativeWidth, ArrayElement.NativeHeight, ArrayElement.MaxResolution, ArrayElement.bIsPrimary, ArrayElement.DPI));
    }

    //MaxFPSPrimaryMonitor
    DEVMODE devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);
    int refreshRate = 0;

    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
    {
        refreshRate = devMode.dmDisplayFrequency;
    }
}