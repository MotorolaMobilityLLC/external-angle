//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// loadimage.h: Defines image loading functions

#ifndef LIBGLESV2_RENDERER_LOADIMAGE_H_
#define LIBGLESV2_RENDERER_LOADIMAGE_H_

namespace rx
{

template <typename T>
inline static T *offsetDataPointer(void *data, int y, int z, int rowPitch, int depthPitch)
{
    return reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(data) + (y * rowPitch) + (z * depthPitch));
}

template <typename T>
inline static const T *offsetDataPointer(const void *data, int y, int z, int rowPitch, int depthPitch)
{
    return reinterpret_cast<const T*>(reinterpret_cast<const unsigned char*>(data) + (y * rowPitch) + (z * depthPitch));
}

void loadAlphaDataToBGRA(int width, int height, int depth,
                         const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                         void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadAlphaDataToNative(int width, int height, int depth,
                           const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                           void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadAlphaDataToBGRASSE2(int width, int height, int depth,
                             const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                             void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadAlphaFloatDataToRGBA(int width, int height, int depth,
                              const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                              void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadAlphaHalfFloatDataToRGBA(int width, int height, int depth,
                                  const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                  void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceDataToNative(int width, int height, int depth,
                               const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                               void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceDataToBGRA(int width, int height, int depth,
                             const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                             void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceFloatDataToRGBA(int width, int height, int depth,
                                  const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                  void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceFloatDataToRGB(int width, int height, int depth,
                                 const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                 void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceHalfFloatDataToRGBA(int width, int height, int depth,
                                      const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                      void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceAlphaDataToNative(int width, int height, int depth,
                                    const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                    void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceAlphaDataToBGRA(int width, int height, int depth,
                                  const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                  void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceAlphaFloatDataToRGBA(int width, int height, int depth,
                                       const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                       void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadLuminanceAlphaHalfFloatDataToRGBA(int width, int height, int depth,
                                           const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                           void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBUByteDataToBGRX(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBUByteDataToRGBA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGB565DataToBGRA(int width, int height, int depth,
                          const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                          void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGB565DataToRGBA(int width, int height, int depth,
                          const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                          void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBFloatDataToRGBA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBFloatDataToNative(int width, int height, int depth,
                              const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                              void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBHalfFloatDataToRGBA(int width, int height, int depth,
                                const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBAUByteDataToBGRASSE2(int width, int height, int depth,
                                 const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                 void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBAUByteDataToBGRA(int width, int height, int depth,
                             const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                             void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBAUByteDataToNative(int width, int height, int depth,
                               const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                               void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA4444DataToBGRA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA4444DataToRGBA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA5551DataToBGRA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA5551DataToRGBA(int width, int height, int depth,
                            const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                            void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBAFloatDataToRGBA(int width, int height, int depth,
                             const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                             void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBAHalfFloatDataToRGBA(int width, int height, int depth,
                                 const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                 void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadBGRADataToBGRA(int width, int height, int depth,
                        const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                        void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA2101010ToNative(int width, int height, int depth,
                             const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                             void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

void loadRGBA2101010ToRGBA(int width, int height, int depth,
                           const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                           void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch);

template <typename type, unsigned int componentCount>
void loadToNative(int width, int height, int depth,
                  const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                  void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch)
{
    const unsigned int rowSize = width * sizeof(type) * componentCount;
    const unsigned int layerSize = rowSize * height;
    const unsigned int imageSize = layerSize * depth;

    if (layerSize == inputDepthPitch && layerSize == outputDepthPitch)
    {
        ASSERT(rowSize == inputRowPitch && rowSize == outputRowPitch);
        memcpy(output, input, imageSize);
    }
    else if (rowSize == inputRowPitch && rowSize == outputRowPitch)
    {
        for (int z = 0; z < depth; z++)
        {
            const type *source = offsetDataPointer<type>(input, 0, z, inputRowPitch, inputDepthPitch);
            type *dest = offsetDataPointer<type>(output, 0, z, outputRowPitch, outputDepthPitch);

            memcpy(dest, source, layerSize);
        }
    }
    else
    {
        for (int z = 0; z < depth; z++)
        {
            for (int y = 0; y < height; y++)
            {
                const type *source = offsetDataPointer<type>(input, y, z, inputRowPitch, inputDepthPitch);
                type *dest = offsetDataPointer<type>(output, y, z, outputRowPitch, outputDepthPitch);
                memcpy(dest, source, width * sizeof(type) * componentCount);
            }
        }
    }
}

template <unsigned int blockWidth, unsigned int blockHeight, unsigned int blockSize>
void loadCompressedBlockDataToNative(int width, int height, int depth,
                                     const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                     void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch)
{
    int columns = (width + (blockWidth - 1)) / blockWidth;
    int rows = (height + (blockHeight - 1)) / blockHeight;

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < rows; ++y)
        {
            void *source = (void*)((char*)input + y * inputRowPitch + z * inputDepthPitch);
            void *dest = (void*)((char*)output + y * outputRowPitch + z * outputDepthPitch);

            memcpy(dest, source, columns * blockSize);
        }
    }
}

}

#endif // LIBGLESV2_RENDERER_LOADIMAGE_H_
