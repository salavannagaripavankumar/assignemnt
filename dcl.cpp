#include <iostream>
#include <bitset>

// Define the DCI format structure
struct DCI {
    uint8_t format; // DCI format (0, 1, 1A, 1B, 1C, 1D, 2, 2A, 2B, 2C)
    uint16_t rnti; // Radio Network Temporary Identifier
    uint8_t resourceAllocation; // Resource allocation type (0, 1, 2, 3)
    uint8_t modulationAndCoding; // Modulation and coding scheme
    uint8_t numberOfLayers; // Number of layers
    uint8_t precodingInformation; // Precoding information
    uint8_t pci; // Physical Cell Identity
    uint8_t scramblingId; // Scrambling ID
    uint8_t rv; // Redundancy version
    uint8_t harqProcess; // HARQ process number
    uint8_t tpc; // Transmit power control
    uint8_t daip; // Downlink assignment index
    uint8_t cqiRequest; // CQI request
    uint8_t srsRequest; // SRS request
    uint8_t ackNack; // ACK/NACK feedback
};

// Define the PDCCH DCI mapping function
void pdcchDciMapping(DCI dci, uint8_t* pdcchPayload) {
    // DCI format
    pdcchPayload[0] = (dci.format & 0x3) << 6;

    // RNTI
    pdcchPayload[0] |= (dci.rnti >> 8) & 0x3F;
    pdcchPayload[1] = dci.rnti & 0xFF;

    // Resource allocation
    pdcchPayload[2] = dci.resourceAllocation << 5;

    // Modulation and coding
    pdcchPayload[2] |= (dci.modulationAndCoding & 0x7) << 2;

    // Number of layers
    pdcchPayload[2] |= (dci.numberOfLayers & 0x3);

    // Precoding information
    pdcchPayload[3] = dci.precodingInformation << 4;

    // PCI
    pdcchPayload[3] |= (dci.pci & 0xF);

    // Scrambling ID
    pdcchPayload[4] = dci.scramblingId << 3;

    // RV
    pdcchPayload[4] |= (dci.rv & 0x7);

    // HARQ process
    pdcchPayload[5] = dci.harqProcess << 2;

    // TPC
    pdcchPayload[5] |= (dci.tpc & 0x3);

    // DAIP
    pdcchPayload[6] = dci.daip << 1;

    // CQI request
    pdcchPayload[6] |= (dci.cqiRequest & 0x1);

    // SRS request
    pdcchPayload[7] = dci.srsRequest << 1;

    // ACK/NACK feedback
    pdcchPayload[7] |= (dci.ackNack & 0x1);
}

int main() {
    DCI dci;
    dci.format = 1; // DCI format 1
    dci.rnti = 0x1234; // RNTI
    dci.resourceAllocation = 0; // Resource allocation type 0
    dci.modulationAndCoding = 0; // Modulation and coding scheme 0
    dci.numberOfLayers = 1; // Number of layers 1
    dci.precodingInformation = 0; // Precoding information 0
    dci.pci = 0; // Physical Cell Identity 0
    dci.scramblingId = 0; // Scrambling ID 0
    dci.rv = 0; // Redundancy version 0
    dci.harqProcess = 0; // HARQ process number 0
    dci.tpc = 0; // Transmit power control 0
    dci.daip = 0; // Downlink assignment index 0
    dci.cqiRequest = 0; // CQI request 0
    dci.srsRequest = 0; // SRS request 0
    dci.ackNack = 0; // ACK/NACK feedback 0

    uint8_t pdcchPayload[8];
    pdcchDciMapping(dci, pdcchPayload);

    std::cout<< "PDCCH Payload: ";
    for (int i = 0; i < 8; i++) {
        std::cout << std::hex << (int)pdcchPayload[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}