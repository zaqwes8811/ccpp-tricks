/* Udacity HW5
  Histogramming for Speed

  The goal of this assignment is compute a histogram
  as fast as possible.  We have simplified the problem as much as
  possible to allow you to focus solely on the histogramming algorithm.

  The input values that you need to histogram are already the exact
  bins that need to be updated.  This is unlike in HW3 where you needed
  to compute the range of the data and then do:
  bin = (val - valMin) / valRange to determine the bin.

  Here the bin is just:
  bin = val

  so the serial histogram calculation looks like:
  for (i = 0; i < numElems; ++i)
   histo[val[i]]++;

  That's it!  Your job is to make it run as fast as possible!

  1. Пользуемся распределением
  // Центральные значения обновляются много чаще
  The values are normally distributed - you may take
  advantage of this fact in your implementation.

  2. Базовая стратегия. 
  http://forums.udacity.com/questions/100040006/any-hw5-timing-results-on-a-solution-that-doesnt-simply-use-atomicadd-in-shared-and-global-mem#cs344
  Не ясно что с сортировкой - это же тоже время. и что сортировать то?
  И если много монипуляций, то может и не выйдет быстрее

*/


#include "utils.h"

static const int g_chunk = 4;
//__device__ __constant__   // падает произв
static const int d_chunk = g_chunk;

//static 
__global__ void src_histo_kernel(
    const unsigned int * const d_vals,
          unsigned int * const d_histo, 
    const unsigned int numBins,
    const unsigned int numElems)
{ 
  int g_id = threadIdx.x + blockDim.x * blockIdx.x;
  if (g_id >= numElems)
    return; 

  // bin
  unsigned int bin = d_vals[g_id];

  // Inc global memory. Partial histos not used.
  atomicAdd(&(d_histo[bin]), 1);
}

__global__
void yourHisto(const unsigned int* const vals, //INPUT
               unsigned int* const histo,      //OUPUT
               int numVals)
{
  //TODO fill in this kernel to calculate the histogram
  //as quickly as possible

  //Although we provide only one kernel skeleton,
  //feel free to use more if it will help you
  //write faster code
}

// Размер блока должен быть не меньше числа бинов
// 
static __global__ 
void histo_kernel_bins_shared_any_any(
    const unsigned int * const d_vals,
          unsigned int * const d_histo, 
    const unsigned int numBins,
    const unsigned int numElems)    
{ 
  extern   // если захардкодить размер, то быстрее не будет
  __shared__ unsigned int local_histo[];
  //__shared__ 
  unsigned slice[d_chunk];

  int g_id = blockDim.x * blockIdx.x + threadIdx.x;
  if (g_id >= numElems)
    return; 

  int ref = g_id * d_chunk;
  //if (ref+d_chunk >= numElems);
  //  return;


  for (int i = threadIdx.x; i < numBins; i += blockDim.x) 
    local_histo[i] = 0;

  for (int i = 0; i < d_chunk; ++i) {
    // bin
    const unsigned bin = d_vals[ref+i];  // read is coal.
    slice[i] = bin;
  }

  __syncthreads();

  // каждый поток обрабатывает отрезок
  for (int i = 0; i < d_chunk; ++i) {
    // bin
    //const unsigned bin = d_vals[ref+i];  // read is coal.

    // Inc global memory. Partial histos not used.
    // если поток столько же скольно и бинов, то гонок не будет
    //++local_histo[bin];  // значения могут быть одинаковыми
    atomicAdd(&(local_histo[slice[i]]), 1);
  }

  __syncthreads();  // ждем пока посчитают все потоки

  // Только первые потоки блока обновляеют гистограмму
  for (int i = threadIdx.x; i < numBins; i += blockDim.x) {
    const unsigned int value = local_histo[i];
      if (value)  // уменьшило время но не на много
        atomicAdd(&(d_histo[i]), value);  // write is coal.
  }
}

static __global__ 
void histo_kernel_bins_shared_any_tblock(
    const unsigned int * const d_vals,
          unsigned int * const d_histo, 
    const unsigned int numBins,
    const unsigned int numElems)    
{ 
  extern   // если захардкодить размер, то быстрее не будет
  __shared__ unsigned int local_histo[];

  int g_id = blockDim.x * blockIdx.x + threadIdx.x;
  //int tid = threadIdx.x;
  if (g_id >= numElems)
    return; 


  for (int i = threadIdx.x; i < numBins; i += blockDim.x) 
    local_histo[i] = 0;

  __syncthreads();

  // каждый поток обрабатывает отрезок
  //if (threadIdx.x % 8 == 0)
    //for (int i = 0, end = 1; i < end; ++i) {
      // bin
      unsigned int bin = d_vals[g_id+0];  // read is coal.

      // Inc global memory. Partial histos not used.
      // если поток столько же скольно и бинов, то гонок не будет
      //++local_histo[bin];  // значения могут быть одинаковыми
      atomicAdd(&(local_histo[bin]), 1);
    //}

  __syncthreads();  // ждем пока посчитают все потоки

  // Только первые потоки блока обновляеют гистограмму
  for (int i = threadIdx.x; i < numBins; i += blockDim.x) {
    const unsigned int value = local_histo[i];
      if (value)  // уменьшило время но не на много
        atomicAdd(&(d_histo[i]), value);  // write is coal.
  }
}

void computeHistogram(const unsigned int* const d_vals, //INPUT
                            unsigned int* const d_histo,      //OUTPUT
                      const unsigned int numBins,
                      const unsigned int numElems)
{
  //TODO Launch the yourHisto kernel
  // перемешанность данных балансирует нагрузку - если отсортировать вход - производительность резко упадет
  assert(numBins == 1024);
  //const int maxThreadsPerBlock = 1024;

	int threads = 1024;  // пробую меньше, чем число бинов
  int blocks = ceil((1.0f*numElems) / threads);
  //blocks /= 8;
  //int sub_hist_blocks = ceil((1.0f*numElems) / numBins);

  // и блок то меньше не сделать - будет не хватать индексов
  //assert(threads >= numBins);

  //thrust::sort(d_vals, d_vals + numElems);
  // Если отсортировать, то бины которые по середине будут писать практически в одно место - это ограничивает конкуренцию

  //if you want to use/launch more than one kernel,
  //feel free
  //src_histo_kernel<<< blocks, threads >>>(d_vals, d_histo, numBins, numElems);
  // 
  // Память может быть большей чем размеры блоков, просто правильно нужно будет обновить глоб. гист.
  //histo_kernel_bins_shared_any_tblock
  histo_kernel_bins_shared_any_any
  <<< 
    //blocks, threads/g_chunk, (numBins)* sizeof(unsigned int) /*+ 225*/ >>>
    blocks, threads/g_chunk, (numBins+4)* sizeof(unsigned int) + 225 >>>
    (d_vals, d_histo, numBins, numElems);
  //histo_kernel_bins_shared<<< sub_hist_blocks, numBins, numBins * sizeof(unsigned int) >>>(d_vals, d_histo, numBins, numElems);

  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}
