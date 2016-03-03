//solution by Wsl_F
#include <bits/stdc++.h>

using namespace std;

typedef struct
{
    unsigned int    bfType;
    unsigned long   bfSize;
    unsigned int    bfReserved1;
    unsigned int    bfReserved2;
    unsigned long   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int    biSize;
    int             biWidth;
    int             biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned int    biCompression;
    unsigned int    biSizeImage;
    int             biXPelsPerMeter;
    int             biYPelsPerMeter;
    unsigned int    biClrUsed;
    unsigned int    biClrImportant;
} BITMAPINFOHEADER;

typedef struct
{
    int   rgbBlue;
    int   rgbGreen;
    int   rgbRed;
    int   rgbReserved;
} RGBQUAD;

typedef vector<int> vi;
typedef vector<vector<RGBQUAD>> MatrixRGB;

#define pb(x)  push_back(x)

class ReadBMP
{
public:
    static vi readBlackWhiteBMP(string fileName);

private:
    static MatrixRGB GetRGBMatrix(string fileName, BITMAPINFOHEADER &bmiHeader);
    static void printBlackWhite(vi ans, int width, int height);
    static vi convertColorMatrixToBWvector(MatrixRGB rgb, int width, int height);
    static MatrixRGB RotatePicture(MatrixRGB rgbRotated, int width, int height);
    static void readFileHeader(BITMAPFILEHEADER &header, FILE* pFile);
    static void readBMPHeader(BITMAPINFOHEADER &bmiHeader, FILE* pFile);
    static MatrixRGB readPicture(BITMAPINFOHEADER bmiHeader, FILE* pFile);

    static unsigned short read_u16(FILE *fp);
    static unsigned int   read_u32(FILE *fp);
    static int            read_s32(FILE *fp);

};
