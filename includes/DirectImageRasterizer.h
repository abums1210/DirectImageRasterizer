#pragma once

#include "Hooks.h"
#include <string>

#pragma pack(push, 1)
struct MipmapCacheHeader {
    uint32_t magic;             // 'MIPC' (0x4D495043)
    uint32_t version;           // 1
    FILETIME sourceLastWrite;   // Last-write timestamp of the source PNG/SVG
    uint64_t sourceFileSize;    // Source file size in bytes
    uint32_t width;             // Top-level width (mip 0)
    uint32_t height;            // Top-level height (mip 0)
    uint32_t numMipLevels;      // Number of mip levels (>= 1)
    uint32_t rasterFlags;       // RenderWare raster creation flags
    uint32_t dataSize;          // Total size of raw pixel data
};
#pragma pack(pop)

class DirectImageRasterizer {
public:
    static RwTexture* LoadSVGToRwTexture(const char* filePath, uint32_t width = 0, uint32_t height = 0, bool generateMipmaps = true, uint32_t mipLevels = 0);
    static RwTexture* LoadPNGToRwTexture(const char* filePath, uint32_t width = 0, uint32_t height = 0, bool generateMipmaps = true, uint32_t mipLevels = 0);
    static RwTexture* FindSVGinFolderPath(const char* folderPath, const char* fileName, uint32_t width = 0, uint32_t height = 0, bool generateMipmaps = true, uint32_t mipLevels = 0);
    static RwTexture* FindPNGinFolderPath(const char* folderPath, const char* fileName, uint32_t width = 0, uint32_t height = 0, bool generateMipmaps = true, uint32_t mipLevels = 0);

    static std::string GetCacheFilePath(const char* filePath, uint32_t width, uint32_t height);
    static RwTexture* TryLoadFromMipCache(const char* filePath, const char* cachePath, uint32_t targetW, uint32_t targetH, bool generateMipmaps, uint32_t mipLevels);
    static bool SaveToMipCache(const char* cachePath, const char* filePath, RwRaster* raster, uint32_t width, uint32_t height, uint32_t numMipLevels, uint32_t rasterFlags);
};
