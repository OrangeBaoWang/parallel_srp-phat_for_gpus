// Release date: June 2015
// Author: Taewoo Lee, (twlee@speech.korea.ac.kr)
//
// Copyright (C) 2015 Taewoo Lee
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Reference:
// [1] Taewoo Lee, Sukmoon Chang, and Dongsuk Yook, "Parallel SRP-PHAT for
//     GPUs," Computer Speech and Language, vol. 35, pp. 1-13, Jan. 2016.
//
#ifndef _MAIN_H___
#define _MAIN_H___
#include <sys/time.h>
#include <cufft.h>
#include <vector_types.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SS	          340000            // speed of sound (mm/s)
#define FS	          16000             // sampling frequency (Hz)
#define T             4096              // number of sampels in a frame
#define MAX_SD	      16                // maximum sample difference in a given microphone array
#define CC_PAIR_SIZE  (MAX_SD*2+1)      // valid cross correlation range
#define N             (M*(M-1)/2)
#define B2(x) (    (x) | (   (x)>>1)  ) // For 32-bit
#define B4(x) (  B2(x) | ( B2(x)>>2)  )
#define B8(x) (  B4(x) | ( B4(x)>>4)  )
#define B16(x)(  B8(x) | ( B8(x)>>8)  )
#define B32(x)( B16(x) | (B16(x)>>16) )
#define NEXT_POW_OF_2(x) (B32(x-1)+1  )
#define POWER_SIZE 	      NEXT_POW_OF_2(Q)
#define NW 32                   // warp size
#define SHMEM_SIZE_MAX 48128    // shared memory size per block (bytes)
#define SIZE_OF_FLOAT 4         // bytes
#define SIZE_OF_FLOAT2 8        // bytes
#define REGISTER_SIZE_MAX (32768*4)
#define SUBBAND 128

int32_t load_TDOA_table(void);
int32_t load_TOA_table(void);
int32_t load_sphCoords(void);
void srp_phat_TDGPU(void);
void srp_phat_FDGPU(void);

typedef float2 Complex;
static __device__ __host__ inline Complex ComplexMul(Complex,Complex);
static __device__ __host__ inline Complex ComplexConj(Complex);
static __device__ __host__ inline float ComplexAbs(Complex a);
__global__ void applyWindow(cufftComplex* d_dataBlock,const float* d_window);
__global__ void phat_weight(cufftComplex* d_dataBlock);

//------------- FD GPU KERNELS -----------------------------------
__global__ void find_max_by_reduction(const float* d_power,int* d_max_indices,float* d_max_powers);
__global__ void find_max_by_reduction32(int* d_max_indices,float* d_max_powers,int* d_maxIdx);
__global__ void fdsp_srp_minotto(const cufftComplex* d_dataBlock,const float* d_w,const float* d_TOA_table,float* d_power);
__global__ void fdsp_srp_gpu4(const cufftComplex* d_dataBlock,const float* d_w,const float* d_TOA_table,float* d_power_tmp);
__global__ void fdsp_srp_gpu4_sum(const float* d_power_tmp,float* d_power);
//------------- FD GPU KERNELS -----------------------------------

//------------- TD GPU KERNELS -----------------------------------
__global__ void ccMul_Minotto(const cufftComplex* d_dataBlock,cufftComplex* d_ifft,const int* d_pair);
__global__ void ccMul_shmem_reg(const cufftComplex* d_dataBlock,cufftComplex* d_ifft);
__global__ void copyDevCC(cufftComplex* d_ifft, float* d_cc);
__global__ void SRP_Minotto(const int* d_TDOA_table, float* d_power);
__global__ void SRP_TD_GPU4_3(const float* d_cc,const char4* d_tdoa_table_char4,float* d_power);
//------------- TD GPU KERNELS -----------------------------------
#endif
