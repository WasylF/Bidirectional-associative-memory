//solution by Wsl_F
#include "ReadBMP.h"

using namespace std;

MatrixRGB ReadBMP:: GetRGBMatrix(string fileName, BITMAPINFOHEADER &bmiHeader)
{
    FILE* pFile = fopen(fileName.c_str(), "rb");

    // считываем заголовок файла
    BITMAPFILEHEADER header __attribute__((unused));
    readFileHeader(header, pFile);

    // считываем заголовок изображения
    readBMPHeader(bmiHeader, pFile);

    // считываем непосредственно само изображение
    MatrixRGB rgb= readPicture(bmiHeader, pFile);
    fclose(pFile);
    return rgb;
}

vi ReadBMP:: readBlackWhiteBMP(string fileName)
{
    BITMAPINFOHEADER bmiHeader;
    MatrixRGB rgbRotate= GetRGBMatrix(fileName, bmiHeader);

    MatrixRGB rgb= RotatePicture(rgbRotate, bmiHeader.biWidth, bmiHeader.biHeight);

    vi ans= convertColorMatrixToBWvector(rgb,bmiHeader.biWidth,bmiHeader.biHeight);
    // выводим результат
    printBlackWhite(ans, bmiHeader.biWidth,  bmiHeader.biHeight);

    return ans;
}

void ReadBMP:: printBlackWhite(vi ans, int width, int height)
{
    int k= 0;
    for (int i= 0; i<height; i++)
    {
        for (int j= 0; j<width; j++)
            if (ans[k++]) cout<<(char)178;
            else cout<<' ';
        cout<<endl;
    }
}

vi ReadBMP:: convertColorMatrixToBWvector(MatrixRGB rgb, int width, int height)
{
    vi ans;
    ans.clear();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (rgb[i][j].rgbRed + rgb[i][j].rgbGreen + rgb[i][j].rgbBlue > 255*1.5)  ans.pb(0);
            else ans.pb(1);
    return ans;
}

MatrixRGB ReadBMP:: RotatePicture(MatrixRGB rgbRotated, int width, int height)
{
    MatrixRGB rgb(height);
    vector<RGBQUAD> tmp;
    tmp.clear();
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            tmp.pb(rgbRotated[i][j]);

    for (int i= height-1; i>=0; i--)
        reverse(tmp.begin()+width*(i),tmp.begin()+width*(i+1));
    reverse(tmp.begin(),tmp.end());

    for (int i= 0; i<height; i++)
        for (int j= 0; j<width; j++)
            rgb[i].pb(tmp[width*i+j]);

    return rgb;
}

void ReadBMP:: readFileHeader(BITMAPFILEHEADER &header, FILE* pFile)
{
    header.bfType      = read_u16(pFile);
    header.bfSize      = read_u32(pFile);
    header.bfReserved1 = read_u16(pFile);
    header.bfReserved2 = read_u16(pFile);
    header.bfOffBits   = read_u32(pFile);
}

void ReadBMP:: readBMPHeader(BITMAPINFOHEADER &bmiHeader, FILE* pFile)
{
    bmiHeader.biSize          = read_u32(pFile);
    bmiHeader.biWidth         = read_s32(pFile);
    bmiHeader.biHeight        = read_s32(pFile);
    bmiHeader.biPlanes        = read_u16(pFile);
    bmiHeader.biBitCount      = read_u16(pFile);
    bmiHeader.biCompression   = read_u32(pFile);
    bmiHeader.biSizeImage     = read_u32(pFile);
    bmiHeader.biXPelsPerMeter = read_s32(pFile);
    bmiHeader.biYPelsPerMeter = read_s32(pFile);
    bmiHeader.biClrUsed       = read_u32(pFile);
    bmiHeader.biClrImportant  = read_u32(pFile);
}

MatrixRGB ReadBMP:: readPicture(BITMAPINFOHEADER bmiHeader, FILE* pFile)
{
    MatrixRGB rgb(bmiHeader.biWidth);

    RGBQUAD tmp;
    for (int i = 0; i < bmiHeader.biWidth; i++)
    {
        for (int j = 0; j < bmiHeader.biHeight; j++)
        {
            tmp.rgbBlue = getc(pFile);
            tmp.rgbGreen = getc(pFile);
            tmp.rgbRed = getc(pFile);
            rgb[i].pb(tmp);
        }

        // пропускаем последний байт в строке
        getc(pFile);
    }
    return rgb;
}

unsigned short ReadBMP:: read_u16(FILE *fp)
{
    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
}

unsigned int ReadBMP:: read_u32(FILE *fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int ReadBMP:: read_s32(FILE *fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}
