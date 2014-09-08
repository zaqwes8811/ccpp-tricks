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

   The values are normally distributed - you may take
   advantage of this fact in your implementation.

*/


#include "utils.h"

template <class Type> __device__ __host__ Type cuda_min2( Type a, Type b ) {
  // I - +inf
  return a < b ? a : b;
}

template <class Type> __device__ __host__ Type cuda_max2( Type a, Type b ) {
  // I - -inf
  return a > b ? a : b;
}

//static 
__global__ void src_histo_kernel(
    const unsigned int * const d_vals,
          unsigned int * const d_histo, 
    const unsigned int numBins,
    const unsigned int numElems
    //float min_logLum, float logLumRange
    )
{ 
  int g_id = threadIdx.x + blockDim.x * blockIdx.x;
  if (g_id >= numElems)
    return; 
    
  //float value = d_vals[g_id];

  // bin
  unsigned int bin = d_vals[g_id];
  //cuda_min2(
  //    static_cast<unsigned int>(numBins - 1), 
  //    static_cast<unsigned int>((value - min_logLum) / logLumRange * numBins));

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

void computeHistogram(const unsigned int* const d_vals, //INPUT
                            unsigned int* const d_histo,      //OUTPUT
                      const unsigned int numBins,
                      const unsigned int numElems)
{
  //TODO Launch the yourHisto kernel
  const int maxThreadsPerBlock = 1024;
	int threads = maxThreadsPerBlock;
  int blocks = ceil((1.0f*numElems) / maxThreadsPerBlock);

  //if you want to use/launch more than one kernel,
  //feel free
  src_histo_kernel<<< blocks, threads >>>(d_vals, d_histo, numBins, numElems);

  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}
