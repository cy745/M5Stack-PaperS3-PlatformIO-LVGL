//
// Created by miku on 25-6-3.
//

#ifndef ZIPFILE_H
#define ZIPFILE_H
#include <string>

class ZipFile {
    const char *source_path;

public:
    explicit ZipFile(const char *source_path) {
        this->source_path = source_path;
    }

    ~ZipFile() {
    }

    // read a file from the zip file allocating the required memory for the data
    uint8_t *read_file_to_memory(const char *path_inside, size_t *size = nullptr) const;

    bool read_file_to_file(const char *filename, const char *dest) const;
};


#endif //ZIPFILE_H
