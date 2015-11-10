#include <iostream>
#include <fstream>
#include <iomanip>

#include "PageArray.h"
#include "Frames.h"
#include "FIFOFrames.h"
#include "LRUFrames.h"

using namespace std;

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
    int inCount;
    while (file >> id) {
        PageNode node(id);

        // Check if there is already a node for this page
        if (genArray[id].getPageID() != 0) {
            genArray[id].setChild(&node);
        }

        // Set the new node in place
        genArray[id] = node;
        mainArray.addPage(node);

        // Increment the count
        ++inCount;
    }

    std::cout << "Page Requests Expected: " << inCount << std::endl;

    // Delete unneeded array
    delete [] genArray;

    // Create the frames
    Frames *frames;

    // Run FIFO first
    frames = new FIFOFrames(frameSize);
    int fifoPageFaults = 0;
    int fifoPageRequests = 0;
    for (int i = 0; i < mainArray.getSize(); ++i) {
        if (frames->add(mainArray.getNextPage())) {
            ++fifoPageFaults;
        }
        ++fifoPageRequests;
    }

    // Clean up
    delete frames;
    mainArray.reset();

    // Run LRU
    frames = new LRUFrames(frameSize);
    int lruPageFaults = 0;
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

        std::cout << *frames << std::endl;

        ++lruPageRequests;
    }
    delete frames;

    std::cout << "FIFO Page Faults: " << fifoPageFaults << std::endl;
    std::cout << "FIFO Page Requests: " << fifoPageRequests << std::endl;
    std::cout << "LRU Page Faults: " << lruPageFaults << std::endl;
    std::cout << "LRU Page Requests: " << lruPageRequests << std::endl;

    return 0;
}