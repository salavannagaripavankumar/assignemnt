#include <iostream>

#include <cmath>

#include <string>

#include <vector>

#include <ns3/core-module.h>

#include <ns3/network-module.h>

#include <ns3/lte-module.h>


using namespace ns3;


// Function to display the transport block size

void TransportBlock(int tbSize) {

   std::cout << "1. Transport Block: Size = " << tbSize << " bits" << std::endl;

}


// Function to determine and display the CRC attachment

void TransportBlockCrcAttachment(int tbSize) {

   int crcBits = (tbSize > 3824) ? 24 : 16;

   std::cout << "2. Transport Block CRC Attachment: " << crcBits << " bits" << std::endl;

}


// Function to select and display LDPC base graph

int LdpcBaseGraphSelection(int tbSize, double codingRate) {

   int baseGraph;

   if (codingRate < 0.25 || tbSize < 292 || (tbSize < 3824 && codingRate < 0.67)) {

       baseGraph = 2;

   } else {

       baseGraph = 1;

   }

   std::cout << "3. LDPC Base Graph Selection: Base Graph " << baseGraph << std::endl;

   return baseGraph;

}


// Function to determine and display code block segmentation

void CodeBlockSegmentation(int tbSize, int crcBits, int baseGraph) {

   int maxSize = (baseGraph == 1) ? (8448 - 24) : (3840 - 24);

   if (tbSize + crcBits > maxSize) {

       int numSegments = std::ceil((tbSize + crcBits) / static_cast<double>(maxSize));

       std::cout << "4. Code Block Segmentation: Segmentation Required. Number of Segments = " << numSegments << std::endl;

   } else {

       std::cout << "4. Code Block Segmentation: No Segmentation Required" << std::endl;

   }

}


// Function to scramble data using a 31-length Gold sequence

std::vector<int> ScrambleData(const std::vector<int>& data) {

   std::vector<int> goldSequence = {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};

   std::vector<int> scrambledData(data.size());


   for (size_t i = 0; i < data.size(); ++i) {

       scrambledData[i] = data[i] ^ goldSequence[i % goldSequence.size()];

   }


   return scrambledData;

}


// Function to simulate modulation (64 QAM or 256 QAM)

std::vector<std::string> Modulate(const std::vector<int>& symbols, const std::string& modulationScheme) {

   std::vector<std::string> modulatedSymbols;

   for (int symbol : symbols) {

       if (modulationScheme == "64 QAM") {

           modulatedSymbols.push_back("64QAM-" + std::to_string(symbol));

       } else if (modulationScheme == "256 QAM") {

           modulatedSymbols.push_back("256QAM-" + std::to_string(symbol));

       } else {

           modulatedSymbols.push_back("UnknownMod-" + std::to_string(symbol));

       }

   }

   return modulatedSymbols;

}


// Function to map modulation symbols to layers

std::vector<std::vector<std::string>> LayerMappingData(const std::vector<std::string>& modulatedSymbols, int layers) {

   std::vector<std::vector<std::string>> layerMappedSymbols(layers);

   for (size_t i = 0; i < modulatedSymbols.size(); ++i) {

       layerMappedSymbols[i % layers].push_back(modulatedSymbols[i]);

   }

   return layerMappedSymbols;

}


// Function to simulate VRB to PRB mapping

std::vector<int> VrbToPrbMappingData(const std::vector<int>& vrb) {

   std::vector<int> prb(vrb.size());

   for (size_t i = 0; i < vrb.size(); ++i) {

       prb[i] = vrb[i]; // Identity mapping for simplicity

   }

   return prb;

}


// Function to perform LDPC coding

void LdpcCoding(const std::vector<int>& data, int baseGraph) {

   std::cout << "5. LDPC Coding: Code blocks encoded using LDPC Base Graph " << baseGraph << std::endl;


   // Placeholder implementation for LDPC coding

   std::vector<int> encodedData = data; // In practice, you would apply the LDPC encoding here


   std::cout << "  Encoded Data: ";

   for (int bit : encodedData) {

       std::cout << bit << " ";

   }

   std::cout << std::endl;

}


// Function to perform rate matching

void RateMatching(const std::vector<int>& encodedData) {

   std::cout << "6. Rate Matching: Performed by puncturing a fraction of systematic bits" << std::endl;


   // Placeholder implementation for Rate Matching

   std::vector<int> rateMatchedData = encodedData; // In practice, you would apply rate matching here


   std::cout << "  Rate Matched Data: ";

   for (int bit : rateMatchedData) {

       std::cout << bit << " ";

   }

   std::cout << std::endl;

}


// Function to concatenate code blocks

void CodeBlockConcatenation(const std::vector<int>& rateMatchedData) {

   std::cout << "7. Code Block Concatenation: Concatenation of code blocks" << std::endl;


   // Placeholder implementation for Code Block Concatenation

   std::vector<int> concatenatedData = rateMatchedData; // In practice, you would concatenate code blocks here


   std::cout << "  Concatenated Data: ";

   for (int bit : concatenatedData) {

       std::cout << bit << " ";

   }

   std::cout << std::endl;

}


// Function to display layer mapping step

void LayerMappingDisplay(const std::vector<std::string>& modulatedSymbols, int layers) {

   std::vector<std::vector<std::string>> layerMappedSymbols = LayerMappingData(modulatedSymbols, layers);

   std::cout << "10. Layer Mapping: Modulation symbols mapped to " << layers << " layers" << std::endl;

   for (size_t i = 0; i < layerMappedSymbols.size(); ++i) {

       std::cout << "Layer " << i + 1 << ": ";

       for (const std::string& symbol : layerMappedSymbols[i]) {

           std::cout << symbol << " ";

       }

       std::cout << std::endl;

   }

}


// Function to display VRB mapping step

void VrbMapping(const std::vector<int>& vrb) {

   std::cout << "11. VRB Mapping: Virtual Resource Blocks mapped" << std::endl;

   for (int block : vrb) {

       std::cout << block << " ";

   }

   std::cout << std::endl;

}


// Function to display VRB to PRB mapping step

void VrbToPrbMappingDisplay(const std::vector<int>& vrb) {

   std::vector<int> prb = VrbToPrbMappingData(vrb);

   std::cout << "12. VRB to PRB Mapping: Virtual Resource Blocks mapped to Physical Resource Blocks" << std::endl;

   for (int block : prb) {

       std::cout << block << " ";

   }

   std::cout << std::endl;

}


// Main function to orchestrate the PDSCH process

void PdschProcess(int tbSize, double codingRate, const std::string& modulationScheme, int layers) {

   TransportBlock(tbSize);

   TransportBlockCrcAttachment(tbSize);


   int baseGraph = LdpcBaseGraphSelection(tbSize, codingRate);

   CodeBlockSegmentation(tbSize, (tbSize > 3824 ? 24 : 16), baseGraph);


   // Example data for LDPC coding, rate matching, and concatenation

   std::vector<int> exampleData = {1, 0, 1, 0, 1, 1, 0, 1};


   LdpcCoding(exampleData, baseGraph);

   RateMatching(exampleData);

   CodeBlockConcatenation(exampleData);


   // Note the function names have been updated for consistency

   std::vector<int> scrambledData = ScrambleData(exampleData);

   std::cout << "8. Scrambling: Data scrambled with 31 length Gold sequence" << std::endl;

   for (int bit : scrambledData) {

       std::cout << bit << " ";

   }

   std::cout << std::endl;


   std::vector<std::string> modulatedSymbols = Modulate(exampleData, modulationScheme);

   std::cout << "9. Modulation: Modulation Scheme Selected - " << modulationScheme << std::endl;

   for (const std::string& symbol : modulatedSymbols) {

       std::cout << symbol << " ";

   }

   std::cout << std::endl;


   LayerMappingDisplay(modulatedSymbols, layers);

   VrbMapping({0, 1, 2, 3, 4});

   VrbToPrbMappingDisplay({0, 1, 2, 3, 4});

}


// Example parameters

int main(int argc, char *argv[]) {

   CommandLine cmd;

   cmd.Parse(argc, argv);


   int tbSize = 4000;         // bits

   double codingRate = 0.3;

   std::string modulationScheme = "64 QAM";

   int layers = 2;


   // Run the PDSCH process

   PdschProcess(tbSize, codingRate, modulationScheme, layers);


   return 0;

}