/*************************************************************************
MIT License

Copyright (c) 2025 Tommy Tracy II, University of Virginia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************/

#include "util.h"

/**
 * Checks errno to see if there was an error opening the file.
 */
void inputFileCheck() {
    if(errno == ENOENT) {
        std::cout<< "IO Error: no such input file." << std::endl;
        exit(-1);
    }
}

/**
 * Opens and parses a file name and returns its contents as a vector of unsigned chars.
 */
std::vector<unsigned char> file2CharVector(std::string fn) {

    // open the file:
    std::ifstream file(fn, std::ios::binary);
    if(file.fail()){
        inputFileCheck();
    }

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // reserve capacity
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<unsigned char>(file),
               std::istream_iterator<unsigned char>());
    file.close();
    return vec;

}

/**
 * This reads valid CRISPR-style 24-byte patterns and sets last 3 to TGG
 */
std::vector<std::vector<uint8_t>> read_patterns(std::string fn) {
    std::ifstream file(fn, std::ios::binary);
    if(file.fail()){
        inputFileCheck();
    }

    std::string pattern;
    std::vector<std::vector<uint8_t>> vec;

    while(std::getline(file, pattern)) {
        auto tmp = std::vector<uint8_t>();
        for(int i = 0; i < 20; i++) {
            tmp.push_back(pattern[i]);
        }
        tmp.push_back('T');
        tmp.push_back('G');
        tmp.push_back('G');
        vec.push_back(tmp);
    }

    return vec;
}

/**
 * This converts a ragg_id and ridPlusOne bit vector to a vector of ids
 */
std::vector<int> getIndexes(UBYTE ragg_id, USHORT ridPlusOne) {
    int offset = ragg_id * RAGG_SIZE;

    std::vector<int> vec;

    for(int id = 0; id < RAGG_SIZE; id++)
    {
        BOOL bitset = ridPlusOne & (1 << id);

        // If id-th bit is set, calculate index and push to vector
        if(bitset)
        {
            int automata_index = offset + id;

            if(automata_index > (NUM_AUTOMATA - 1))
            {
                std::cout << "Found automaton outside of range!" << std::endl;
                exit(-1);
            }
            vec.push_back(automata_index);
        }
    }
    return vec;
}

/**
 * This converts an integer to a bit vector representing the edit distance for the LEV automata
 */
char edit_distance_byte(int arg){

    char return_byte;
    if(arg > 6){
        std::cout<< "IO Error: edit distance is not a value from 0 - 6." << std::endl;
        exit(-1);
    }

    switch (arg)
    {
    case 0:
        return_byte = 0b00000001;
        break;
    case 1:
        return_byte = 0b00000011;
        break;
    case 2:
        return_byte = 0b00000111;
        break;
    case 3:
        return_byte = 0b00001111;
        break;
    case 4:
        return_byte = 0b00011111;
        break;
    case 5:
        return_byte = 0b00111111;
        break;
    case 6:
        return_byte = 0b01111111;
        break;
    
    default:
        return_byte = 0b00000001;
        break;
    }
    return return_byte;
}