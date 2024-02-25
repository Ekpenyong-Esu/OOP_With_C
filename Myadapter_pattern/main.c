#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*printLegacy)(const char*);
} LegacyPrinter;

typedef struct {
    void (*printModern)(const char*);
} ModernPrinter;

typedef struct {
    LegacyPrinter* legacyPrinter;
    void (*printModern)(const char*, LegacyPrinter*);
} PrinterAdapter;

void printUsingLegacyPrinter(const char* text) {
    printf("Legacy Printer: %s\n", text);
}

void printUsingModernPrinter(const char* text) {
    printf("Modern Printer: %s\n", text);
}

LegacyPrinter* createLegacyPrinter() {
    LegacyPrinter* printer = (LegacyPrinter*)malloc(sizeof(LegacyPrinter));
    printer->printLegacy = printUsingLegacyPrinter;
    return printer;
}

ModernPrinter* createModernPrinter() {
    ModernPrinter* printer = (ModernPrinter*)malloc(sizeof(ModernPrinter));
    printer->printModern = printUsingModernPrinter;
    return printer;
}

void printModernAdapter(const char* text, LegacyPrinter* legacyPrinter) {
    legacyPrinter->printLegacy(text);
}

PrinterAdapter* createPrinterAdapter(LegacyPrinter* legacyPrinter) {
    PrinterAdapter* adapter = (PrinterAdapter*)malloc(sizeof(PrinterAdapter));
    adapter->legacyPrinter = legacyPrinter;
    adapter->printModern = printModernAdapter;
    return adapter;
}

void freePrinters(LegacyPrinter* legacyPrinter, ModernPrinter* modernPrinter, PrinterAdapter* adapter) {
    free(legacyPrinter);
    free(modernPrinter);
    free(adapter);
}

int main() {
    LegacyPrinter* legacyPrinter = createLegacyPrinter();
    ModernPrinter* modernPrinter = createModernPrinter();

    modernPrinter->printModern("Hello from Modern Printer");

    PrinterAdapter* adapter = createPrinterAdapter(legacyPrinter);
    adapter->printModern("Hello from Legacy Printer through Adapter", adapter->legacyPrinter);

    freePrinters(legacyPrinter, modernPrinter, adapter);

    return 0;
}
