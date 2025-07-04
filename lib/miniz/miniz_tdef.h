#pragma once
#include "miniz_common.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ------------------- Low-level Compression API Definitions */

/* Set X_TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently). */
#define X_TDEFL_LESS_MEMORY 0

/* x_tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search): */
/* X_TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression). */
enum
{
    X_TDEFL_HUFFMAN_ONLY = 0,
    X_TDEFL_DEFAULT_MAX_PROBES = 128,
    X_TDEFL_MAX_PROBES_MASK = 0xFFF
};

/* X_TDEFL_WRITE_ZLIB_HEADER: If set, the compressor outputs a zlib header before the deflate data, and the Adler-32 of the source data at the end. Otherwise, you'll get raw deflate data. */
/* X_TDEFL_COMPUTE_ADLER32: Always compute the adler-32 of the input data (even when not writing zlib headers). */
/* X_TDEFL_GREEDY_PARSING_FLAG: Set to use faster greedy parsing, instead of more efficient lazy parsing. */
/* X_TDEFL_NONDETERMINISTIC_PARSING_FLAG: Enable to decrease the compressor's initialization time to the minimum, but the output may vary from run to run given the same input (depending on the contents of memory). */
/* X_TDEFL_RLE_MATCHES: Only look for RLE matches (matches with a distance of 1) */
/* X_TDEFL_FILTER_MATCHES: Discards matches <= 5 chars if enabled. */
/* X_TDEFL_FORCE_ALL_STATIC_BLOCKS: Disable usage of optimized Huffman tables. */
/* X_TDEFL_FORCE_ALL_RAW_BLOCKS: Only use raw (uncompressed) deflate blocks. */
/* The low 12 bits are reserved to control the max # of hash probes per dictionary lookup (see X_TDEFL_MAX_PROBES_MASK). */
enum
{
    X_TDEFL_WRITE_ZLIB_HEADER = 0x01000,
    X_TDEFL_COMPUTE_ADLER32 = 0x02000,
    X_TDEFL_GREEDY_PARSING_FLAG = 0x04000,
    X_TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
    X_TDEFL_RLE_MATCHES = 0x10000,
    X_TDEFL_FILTER_MATCHES = 0x20000,
    X_TDEFL_FORCE_ALL_STATIC_BLOCKS = 0x40000,
    X_TDEFL_FORCE_ALL_RAW_BLOCKS = 0x80000
};

/* High level compression functions: */
/* x_tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc(). */
/* On entry: */
/*  pSrc_buf, src_buf_len: Pointer and size of source block to compress. */
/*  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression. */
/* On return: */
/*  Function returns a pointer to the compressed data, or NULL on failure. */
/*  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data. */
/*  The caller must free() the returned block when it's no longer needed. */
MINIZ_EXPORT void *x_tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags);

/* x_tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory. */
/* Returns 0 on failure. */
MINIZ_EXPORT size_t x_tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

/* Compresses an image to a compressed PNG file in memory. */
/* On entry: */
/*  pImage, w, h, and num_chans describe the image to compress. num_chans may be 1, 2, 3, or 4. */
/*  The image pitch in bytes per scanline will be w*num_chans. The leftmost pixel on the top scanline is stored first in memory. */
/*  level may range from [0,10], use MZ_NO_COMPRESSION, MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc. or a decent default is MZ_DEFAULT_LEVEL */
/*  If flip is true, the image will be flipped on the Y axis (useful for OpenGL apps). */
/* On return: */
/*  Function returns a pointer to the compressed data, or NULL on failure. */
/*  *pLen_out will be set to the size of the PNG image file. */
/*  The caller must mz_free() the returned heap block (which will typically be larger than *pLen_out) when it's no longer needed. */
MINIZ_EXPORT void *x_tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h, int num_chans, size_t *pLen_out, mz_uint level, mz_bool flip);
MINIZ_EXPORT void *x_tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h, int num_chans, size_t *pLen_out);

/* Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called X_TDEFL_OUT_BUF_SIZE at a time. */
typedef mz_bool (*x_tdefl_put_buf_func_ptr)(const void *pBuf, int len, void *pUser);

/* x_tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally. */
MINIZ_EXPORT mz_bool x_tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len, x_tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

enum
{
    X_TDEFL_MAX_HUFF_TABLES = 3,
    X_TDEFL_MAX_HUFF_SYMBOLS_0 = 288,
    X_TDEFL_MAX_HUFF_SYMBOLS_1 = 32,
    X_TDEFL_MAX_HUFF_SYMBOLS_2 = 19,
    X_TDEFL_LZ_DICT_SIZE = 32768,
    X_TDEFL_LZ_DICT_SIZE_MASK = X_TDEFL_LZ_DICT_SIZE - 1,
    X_TDEFL_MIN_MATCH_LEN = 3,
    X_TDEFL_MAX_MATCH_LEN = 258
};

/* X_TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes). */
#if X_TDEFL_LESS_MEMORY
enum
{
    X_TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024,
    X_TDEFL_OUT_BUF_SIZE = (X_TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
    X_TDEFL_MAX_HUFF_SYMBOLS = 288,
    X_TDEFL_LZ_HASH_BITS = 12,
    X_TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
    X_TDEFL_LZ_HASH_SHIFT = (X_TDEFL_LZ_HASH_BITS + 2) / 3,
    X_TDEFL_LZ_HASH_SIZE = 1 << X_TDEFL_LZ_HASH_BITS
};
#else
enum
{
    X_TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024,
    X_TDEFL_OUT_BUF_SIZE = (X_TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
    X_TDEFL_MAX_HUFF_SYMBOLS = 288,
    X_TDEFL_LZ_HASH_BITS = 15,
    X_TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
    X_TDEFL_LZ_HASH_SHIFT = (X_TDEFL_LZ_HASH_BITS + 2) / 3,
    X_TDEFL_LZ_HASH_SIZE = 1 << X_TDEFL_LZ_HASH_BITS
};
#endif

/* The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions. */
typedef enum {
    X_TDEFL_STATUS_BAD_PARAM = -2,
    X_TDEFL_STATUS_PUT_BUF_FAILED = -1,
    X_TDEFL_STATUS_OKAY = 0,
    X_TDEFL_STATUS_DONE = 1
} x_tdefl_status;

/* Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums */
typedef enum {
    X_TDEFL_NO_FLUSH = 0,
    X_TDEFL_SYNC_FLUSH = 2,
    X_TDEFL_FULL_FLUSH = 3,
    X_TDEFL_FINISH = 4
} x_tdefl_flush;

/* tdefl's compression state structure. */
typedef struct
{
    x_tdefl_put_buf_func_ptr m_pPut_buf_func;
    void *m_pPut_buf_user;
    mz_uint m_flags, m_max_probes[2];
    int m_greedy_parsing;
    mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
    mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
    mz_uint m_num_flags_left, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_buffer;
    mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index, m_wants_to_finish;
    x_tdefl_status m_prev_return_status;
    const void *m_pIn_buf;
    void *m_pOut_buf;
    size_t *m_pIn_buf_size, *m_pOut_buf_size;
    x_tdefl_flush m_flush;
    const mz_uint8 *m_pSrc;
    size_t m_src_buf_left, m_out_buf_ofs;
    mz_uint8 m_dict[X_TDEFL_LZ_DICT_SIZE + X_TDEFL_MAX_MATCH_LEN - 1];
    mz_uint16 m_huff_count[X_TDEFL_MAX_HUFF_TABLES][X_TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint16 m_huff_codes[X_TDEFL_MAX_HUFF_TABLES][X_TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint8 m_huff_code_sizes[X_TDEFL_MAX_HUFF_TABLES][X_TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint8 m_lz_code_buf[X_TDEFL_LZ_CODE_BUF_SIZE];
    mz_uint16 m_next[X_TDEFL_LZ_DICT_SIZE];
    mz_uint16 m_hash[X_TDEFL_LZ_HASH_SIZE];
    mz_uint8 m_output_buf[X_TDEFL_OUT_BUF_SIZE];
} x_tdefl_compressor;

/* Initializes the compressor. */
/* There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory. */
/* pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the x_tdefl_compress_buffer() API for compression. */
/* If pBut_buf_func is NULL the user should always call the x_tdefl_compress() API. */
/* flags: See the above enums (X_TDEFL_HUFFMAN_ONLY, X_TDEFL_WRITE_ZLIB_HEADER, etc.) */
MINIZ_EXPORT x_tdefl_status x_tdefl_init(x_tdefl_compressor *d, x_tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

/* Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible. */
MINIZ_EXPORT x_tdefl_status x_tdefl_compress(x_tdefl_compressor *d, const void *pIn_buf, size_t *pIn_buf_size, void *pOut_buf, size_t *pOut_buf_size, x_tdefl_flush flush);

/* x_tdefl_compress_buffer() is only usable when the x_tdefl_init() is called with a non-NULL x_tdefl_put_buf_func_ptr. */
/* x_tdefl_compress_buffer() always consumes the entire input buffer. */
MINIZ_EXPORT x_tdefl_status x_tdefl_compress_buffer(x_tdefl_compressor *d, const void *pIn_buf, size_t in_buf_size, x_tdefl_flush flush);

MINIZ_EXPORT x_tdefl_status x_tdefl_get_prev_return_status(x_tdefl_compressor *d);
MINIZ_EXPORT mz_uint32 x_tdefl_get_adler32(x_tdefl_compressor *d);

/* Create x_tdefl_compress() flags given zlib-style compression parameters. */
/* level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files) */
/* window_bits may be -15 (raw deflate) or 15 (zlib) */
/* strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED */
MINIZ_EXPORT mz_uint x_tdefl_create_comp_flags_from_zip_params(int level, int window_bits, int strategy);

#ifndef MINIZ_NO_MALLOC
/* Allocate the x_tdefl_compressor structure in C so that */
/* non-C language bindings to x_tdefl_ API don't need to worry about */
/* structure size and allocation mechanism. */
MINIZ_EXPORT x_tdefl_compressor *x_tdefl_compressor_alloc(void);
MINIZ_EXPORT void x_tdefl_compressor_free(x_tdefl_compressor *pComp);
#endif

#ifdef __cplusplus
}
#endif
