#include <stdio.h>
#include "GasMixer.h"
#include "GasDisplay.h"

int main() {
    printf("\n=================================\n");
    printf("Oxygen Sensor Monitoring System\n");
    printf("=================================\n\n");
    
    printf("Running Gas Mixer Test:\n");
    printf("-----------------------\n");
    mixerGas();
    
    printf("\nRunning Gas Display Test:\n");
    printf("------------------------\n");
    displayGas();
    
    printf("\nAll tests completed successfully.\n");
    return 0;
}
