#include <windows.h>
#include <setupapi.h>
#include <stdio.h>

#pragma comment(lib, "setupapi.lib")

void EnumerateDevices() {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i;
    deviceInfoSet = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        return;
    }
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        TCHAR id[1024];
        TCHAR deviceName[1024];
        TCHAR compatible[1024];
        TCHAR service[1024];
        TCHAR class[1024];
        TCHAR manufacturer[1024];
        printf("Device\t\t: #%ld\n", i);
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE) id,
                                             sizeof(id), NULL)) {
            printf("Id\t\t: %s\n", id);
        }
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE) deviceName,
                                             sizeof(deviceName), NULL)) {
            printf("Name\t\t: %s\n", deviceName);
        }
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_COMPATIBLEIDS, NULL,
                                             (PBYTE) compatible, sizeof(compatible), NULL)) {
            printf("CompatibleId\t: %s\n", compatible);
        }
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_SERVICE, NULL, (PBYTE) service,
                                             sizeof(service), NULL)) {
            printf("Service\t\t: %s\n", service);
        }
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_CLASS, NULL, (PBYTE) class,
                                             sizeof(class), NULL)) {
            printf("Class\t\t: %s\n", class);
        }
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_MFG, NULL, (PBYTE) manufacturer,
                                             sizeof(manufacturer), NULL)) {
            printf("Manufacturer\t: %s\n", manufacturer);
        }
        printf("\n");
    }
    if (GetLastError() != ERROR_NO_MORE_ITEMS) {
        printf("SetupDiEnumDeviceInfo failed with error %ld\n", GetLastError());
    }
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main() {
    EnumerateDevices();
    return 0;
}
