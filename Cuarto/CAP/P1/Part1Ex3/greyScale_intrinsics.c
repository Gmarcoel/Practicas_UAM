#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <x86intrin.h>

static inline void getRGB(uint8_t *im, int width, int height, int nchannels, int x, int y, int *r, int *g, int *b)
{

    unsigned char *offset = im + (x + width * y) * nchannels;
    *r = offset[0];
    *g = offset[1];
    *b = offset[2];
}

int main(int nargs, char **argv)
{
    int width, height, nchannels;
    struct timeval fin, ini;

    if (nargs < 2)
    {
        printf("Usage: %s <image1> [<image2> ...]\n", argv[0]);
    }
    // For each image
    // Bucle 0
    for (int file_i = 1; file_i < nargs; file_i++)
    {
        printf("[info] Processing %s\n", argv[file_i]);
        /****** Reading file ******/
        uint8_t *rgb_image = stbi_load(argv[file_i], &width, &height, &nchannels, 4);
        if (!rgb_image)
        {
            perror("Image could not be opened");
        }

        /****** Allocating memory ******/
        // - RGB2Grey
        uint8_t *grey_image = malloc(width * height);
        if (!grey_image)
        {
            perror("Could not allocate memory");
        }

        // - Filenames
        for (int i = strlen(argv[file_i]) - 1; i >= 0; i--)
        {
            if (argv[file_i][i] == '.')
            {
                argv[file_i][i] = 0;
                break;
            }
        }

        char *grey_image_filename = 0;
        asprintf(&grey_image_filename, "%s_grey.jpg", argv[file_i]);
        if (!grey_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        /****** Computations ******/
        printf("[info] %s: width=%d, height=%d, nchannels=%d\n", argv[file_i], width, height, nchannels);

        if (nchannels != 3 && nchannels != 4)
        {
            printf("[error] Num of channels=%d not supported. Only three (RGB), four (RGBA) are supported.\n", nchannels);
            continue;
        }

        gettimeofday(&ini, NULL);
        // RGB to grey scale
        // int r, g, b;
        for (int j = 0; j < height; j+=1)
        {
            for (int i = 0; i < width; i+=4)
            {
                // Load 8 bytes twice (use two vectors “low” and “high”)
                // *image+0
                __m128i datal = _mm_loadl_epi64((__m128i *)(rgb_image + (i + width * j) * 4));
                // *image+8
                __m128i datah = _mm_loadl_epi64((__m128i *)(rgb_image + (i + width * j ) * 4 + 8));

                // Convert each vector to 32-bit integer: _mm256_cvtepu8_epi32 (Zero sign-extend)
                __m256i datali = _mm256_cvtepu8_epi32(datal);
                __m256i datahi = _mm256_cvtepu8_epi32(datah);

                // Convert to float (single precision): _mm256_cvtepi32_ps
                __m256 datalf = _mm256_cvtepi32_ps(datali);
                __m256 datahf = _mm256_cvtepi32_ps(datahi);

                // Multiply by a constant vector: _mm256_mul_ps : 0.2989, 0.5870, 0.1140
                // *offset = im + (x + width * y) * nchannels
                __m256 coefficients = _mm256_setr_ps(0.2989, 0.5870, 0.1140, 0, 0.2989, 0.5870, 0.1140, 0);
                //__m256 coefficients = (__m256)_mm256_set_pd(0.2989, 0.5870, 0.1140, 0); // __m256d
                __m256 datalm = _mm256_mul_ps(coefficients, datalf);
                __m256 datahm = _mm256_mul_ps(coefficients, datahf);

                // Sum all values per pixel using horizontal addition
                // __m256d result = _mm256_hadd_pd((__m256d)datalm, (__m256d)datahm); // Esto esta mal ?
                // Hacerlo ahora bien
                __m256 result = _mm256_hadd_ps(datalm, datahm);
                result = _mm256_hadd_ps(result, result);

                // Reorder the values: _mm256_permutevar8x32_ps
                // Second parameter is the index (permutation) ¿values?
                __m256 result_perm = _mm256_permutevar8x32_ps(result, _mm256_setr_epi32(0,4,1,5,0,0,0,0)); // Todo ceros ?? 0,4,1,5,2,6,3,7 // 0,2,0,0,1,3,0,0

                // Convert to 32-bit integer:
                // _mm_cvtps_epi32(_mm256_extractf128_ps ())
                __m128i result_int = _mm_cvtps_epi32(_mm256_extractf128_ps(result_perm, 0));
                uint32_t* result_arr = (uint32_t*)& result_int;

                // Store in memmory uint32_t *greyimage
                // grey_image[i + width * j] = _mm_cvtsi128_si32(result_int);
                // _mm_storeu_si128((__m128i *)(grey_image + (i + width * j)), result_int);
                grey_image[0 + i + width * j] = result_arr[0];
                grey_image[1 + i + width * j] = result_arr[1];
                grey_image[2 + i + width * j] = result_arr[2];
                grey_image[3 + i + width * j] = result_arr[3];
                // Legacy
                /*
                getRGB(rgb_image, width, height, 4, i, j, &r, &g, &b);
                grey_image[j * width + i] = (int)(0.2989 * r + 0.5870 * g + 0.1140 * b);
                */
            }
        }

        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        free(rgb_image);

        gettimeofday(&fin, NULL);

        printf("Tiempo: %f\n", ((fin.tv_sec * 1000000 + fin.tv_usec) - (ini.tv_sec * 1000000 + ini.tv_usec)) * 1.0 / 1000000.0);
        free(grey_image_filename);
    }
}
