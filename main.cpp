#include <iostream>
#include <fstream>
#include <iomanip>

#include "PageArray.h"
#include "Frames.h"
#include "FIFOFrames.h"
#include "LRUFrames.h"
#include "OptimalFrames.h"

using namespace std;

void outputResults();

int fifoPageFaults;
float fifoFaultRates[5];

int lruPageFaults;
float lruFaultRates[5];

int optimalPageFaults;
float optimalFaultRates[5];

int main(int argc, char** argv) {
    // Read in the command line arguments
    if (argc < 4) {
        // Output usage messages
        std::cout << "Incorrect # of Command Line Arguments\n\n";
        std::cout << "Usage: memsim <frame_size> <input_file> <output_file>\n\n";
        std::cout << std::setw(15) << " " << "frame_size: The number of frames in the paging system\n";
        std::cout << std::setw(15) << " " << "input_file: The file containing the order of the page calls\n";
        std::cout << std::setw(15) << " " << "output_file: Target file to output results\n\n";

        return -1;
    }

    int frameSize = stoi(argv[1]);

    // Create the main arrays
    PageArray mainArray(10001);
    PageNode *genArray = new PageNode[512];

    // Read the file in
    std::ifstream file(argv[2], std::ios_base::in);
    int id;
    int inCount = 0;
    while (file >> id) {
        PageNode node(id);
        node.setIndex(inCount++);

        // Check if there is already a node for this page
        if (genArray[id].getPageID() != 0) {
            genArray[id].setChild(&node);
        }

        // Set the new node in place
        genArray[id] = node;
        mainArray.addPage(node);
    }

    std::cout << "Page Requests Expected: " << inCount << std::endl;

    // Delete unneeded array
    delete [] genArray;

    // Create the frames
    Frames *frames;

    // Run FIFO first
    frames = new FIFOFrames(frameSize);
    fifoPageFaults = 0;
    int fifoPageRequests = 0;
    for (int i = 0; i < mainArray.getSize(); ++i) {
        if (frames->add(mainArray.getNextPage())) {
            ++fifoPageFaults;
        }
        ++fifoPageRequests;

        if (i == 999) {
            fifoFaultRates[0] = (float)fifoPageFaults / 1000.;
        } else if (i == 1999) {
            fifoFaultRates[1] = (float)fifoPageFaults / 2000.;
        } else if (i == 3999) {
            fifoFaultRates[2] = (float)fifoPageFaults / 4000.;
        } else if (i == 5999) {
            fifoFaultRates[3] = (float)fifoPageFaults / 6000.;
        } else if (i == 7999) {
            fifoFaultRates[3] = (float)fifoPageFaults / 8000.;
        } else if (i == 9999) {
            fifoFaultRates[4] = (float)fifoPageFaults / 10000.;
        }
    }

    // Clean up
    delete frames;
    mainArray.reset();

    // Run LRU
    frames = new LRUFrames(frameSize);
    lruPageFaults = 0;
    int lruPageRequests = 0;
    int runtime;
    for (int i = 0; i < mainArray.getSize(); ++i) {
        // Set runtime
        PageNode node = mainArray.getNextPage();
        node.setLastCalled(runtime++);

        // Add the frame
        if (frames->add(node)) {
            ++lruPageFaults;
        }

        ++lruPageRequests;

        if (i == 999) {
            lruFaultRates[0] = (float)lruPageFaults / 1000.;
        } else if (i == 1999) {
            lruFaultRates[1] = (float)lruPageFaults / 2000.;
        } else if (i == 3999) {
            lruFaultRates[2] = (float)lruPageFaults / 4000.;
        } else if (i == 5999) {
            lruFaultRates[3] = (float)lruPageFaults / 6000.;
        } else if (i == 7999) {
            lruFaultRates[3] = (float)lruPageFaults / 8000.;
        } else if (i == 9999) {
            lruFaultRates[4] = (float)lruPageFaults / 10000.;
        }
    }

    // Clean up
    delete frames;
    mainArray.reset();

    // Run Optimal
    frames = new OptimalFrames(frameSize);
    optimalPageFaults = 0;
    int optimalPageRequests = 0;
    for (int i = 0; i < mainArray.getSize(); ++i) {
        if (frames->add(mainArray.getNextPage())) {
            ++optimalPageFaults;
        }
        ++optimalPageRequests;

        if (i == 999) {
            optimalFaultRates[0] = (float)optimalPageFaults / 1000.;
        } else if (i == 1999) {
            optimalFaultRates[1] = (float)optimalPageFaults / 2000.;
        } else if (i == 3999) {
            optimalFaultRates[2] = (float)optimalPageFaults / 4000.;
        } else if (i == 5999) {
            optimalFaultRates[3] = (float)optimalPageFaults / 6000.;
        } else if (i == 7999) {
            optimalFaultRates[3] = (float)optimalPageFaults / 8000.;
        } else if (i == 9999) {
            optimalFaultRates[4] = (float)optimalPageFaults / 10000.;
        }
    }

    // Clean up
    delete frames;

    outputResults();

    return 0;
}

void outputResults() {
    std::cout << std::setw(63) << "Page Fault Rates\n" 
              << std::setw(12) << "Algorithm" << std::setw(20) << "Total Page Faults"
              << std::setw(16) << 2000 << std::setw(10) << 4000 << std::setw(10) << 6000
              << std::setw(10) << 8000 << std::setw(11) << 10000 << '\n'
              << "---------------------------------------------------------------------------------------------\n"
              << std::setw(12) << "FIFO" << std::setw(13) << fifoPageFaults
              << std::setw(23) << fifoFaultRates[0]
              << std::setw(10) << fifoFaultRates[1]
              << std::setw(10) << fifoFaultRates[2]
              << std::setw(10) << fifoFaultRates[3]
              << std::setw(10) << fifoFaultRates[4] << '\n'
              << std::setw(12) << "LRU" << std::setw(13) << lruPageFaults
              << std::setw(23) << lruFaultRates[0]
              << std::setw(10) << lruFaultRates[1]
              << std::setw(10) << lruFaultRates[2]
              << std::setw(10) << lruFaultRates[3]
              << std::setw(10) << lruFaultRates[4] << '\n'
              << std::setw(12) << "Optimal" << std::setw(13) << optimalPageFaults
              << std::setw(23) << optimalFaultRates[0]
              << std::setw(10) << optimalFaultRates[1]
              << std::setw(10) << optimalFaultRates[2]
              << std::setw(10) << optimalFaultRates[3]
              << std::setw(10) << optimalFaultRates[4] << '\n';
}
