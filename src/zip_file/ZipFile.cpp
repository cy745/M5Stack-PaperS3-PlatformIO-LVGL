//
// Created by miku on 25-6-3.
//

#include "ZipFile.h"

#include <esp_log.h>
#include "miniz.h"

const auto TAG = "ZIPFILE";

uint8_t *ZipFile::read_file_to_memory(const char *path_inside, size_t *size) const {
    // open up the epub file using miniz
    mz_zip_archive zip_archive = {};

    bool status = mz_zip_reader_init_file(&zip_archive, source_path, 0);
    if (!status) {
        ESP_LOGE(TAG, "mz_zip_reader_init_file() failed!\n");
        ESP_LOGE(TAG, "Error %s\n", mz_zip_get_error_string(zip_archive.m_last_error));
        return nullptr;
    }

    // find the file
    mz_uint32 file_index = 0;
    if (!mz_zip_reader_locate_file_v2(&zip_archive, path_inside, nullptr, 0, &file_index)) {
        ESP_LOGE(TAG, "Could not find file %s", path_inside);
        mz_zip_reader_end(&zip_archive);
        return nullptr;
    }

    // get the file size - we do this all manually so we can add a null terminator to any strings
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, file_index, &file_stat)) {
        ESP_LOGE(TAG, "mz_zip_reader_file_stat() failed!\n");
        ESP_LOGE(TAG, "Error %s\n", mz_zip_get_error_string(zip_archive.m_last_error));
        mz_zip_reader_end(&zip_archive);
        return nullptr;
    }

    size_t file_size = file_stat.m_uncomp_size;
    uint8_t *file_data = (uint8_t *) calloc(file_size + 1, sizeof(uint8_t));
    if (!file_data) {
        ESP_LOGE(TAG, "Failed to allocate memory for %s\n", file_stat.m_filename);
        mz_zip_reader_end(&zip_archive);
        return nullptr;
    }

    // read the file
    status = mz_zip_reader_extract_to_mem(&zip_archive, file_index, file_data, file_size, 0);
    if (!status) {
        ESP_LOGE(TAG, "mz_zip_reader_extract_to_mem() failed!\n");
        ESP_LOGE(TAG, "Error %s\n", mz_zip_get_error_string(zip_archive.m_last_error));
        free(file_data);
        mz_zip_reader_end(&zip_archive);
        return nullptr;
    }

    // Close the archive, freeing any resources it was using
    mz_zip_reader_end(&zip_archive);
    // return the size if required
    if (size) {
        *size = file_size;
    }
    return file_data;
}

bool ZipFile::read_file_to_file(const char *filename, const char *dest) const {
    mz_zip_archive zip_archive = {};

    bool status = mz_zip_reader_init_file(&zip_archive, source_path, 0);
    if (!status) {
        ESP_LOGE(TAG, "mz_zip_reader_init_file() failed!\n");
        ESP_LOGE(TAG, "Error %s\n", mz_zip_get_error_string(zip_archive.m_last_error));
        return false;
    }

#ifdef DEBUG
    const auto file_name_buffer = new char[256];
    for (int i = 0; i < mz_zip_reader_get_num_files(&zip_archive); ++i) {
        mz_zip_reader_get_filename(&zip_archive, i, file_name_buffer, 200);
        ESP_LOGD(TAG, "readFile in %s, [%d]%s\n", source_path, i, file_name_buffer);
    }
#endif


    // Run through the archive and find the requiested file
    for (int i = 0; i < (int) mz_zip_reader_get_num_files(&zip_archive); i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
            ESP_LOGE(TAG, "mz_zip_reader_file_stat() failed!\n");
            ESP_LOGE(TAG, "Error %s\n", mz_zip_get_error_string(zip_archive.m_last_error));
            mz_zip_reader_end(&zip_archive);
            return false;
        }
        // is this the file we're looking for?
        if (strcmp(filename, file_stat.m_filename) == 0) {
            ESP_LOGI(TAG, "Extracting %s\n", file_stat.m_filename);
            mz_zip_reader_extract_file_to_file(&zip_archive, file_stat.m_filename, dest, 0);
            mz_zip_reader_end(&zip_archive);
            return true;
        }
    }
    mz_zip_reader_end(&zip_archive);
    return false;
}
