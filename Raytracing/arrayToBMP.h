#include <iostream>
#include <fstream>
#include <string>

/* typedefs */
typedef unsigned char byte_t;
typedef unsigned int rgb24_t;

class arrayToBMP
{
private:

	static const uint32_t COLORTABLE_ENTRIES = 0x00;

	/*COMPRESSIONS*/
	static const uint16_t BI_RGB = 0;
	static const uint16_t BI_RLE8 = 1;
	static const uint16_t BI_RLE4 = 2;
	static const uint16_t BI_BITFIELDS = 3;

	/*META*/
	static const uint32_t FILEHEADER_SIZE = 0x0E;
	static const uint32_t INFOHEADER_SIZE = 0x28;

	/*BITMAPFILEHEADER*/
	static const uint16_t BF_TYPE = 0x4D42;
	static const uint32_t BF_RESERVED = 0x00;
	static const uint32_t BF_OFFBITS = FILEHEADER_SIZE + INFOHEADER_SIZE;
	
	/*BITMAPINFOHEADER*/
	static const uint16_t BI_PLANES = 0x01;
	static const uint16_t BI_BITCOUNT = 0x18;
	static const uint32_t BI_COMPRESSION = BI_RGB;
	static const uint32_t BI_XPELSPERMETER = 0x0000;
	static const uint32_t BI_YPELSPERMETER = 0x0000;
	static const uint32_t BI_CLRUSED = BI_BITCOUNT == 1 ? 0 : BI_BITCOUNT == 4 || BI_BITCOUNT == 8 ? COLORTABLE_ENTRIES : 0x00;
	static const uint32_t BI_CLRIMPORTANT = 0x00;


	static inline size_t bytesNeeded(size_t data)
	{
		size_t s = 1;
		while (s < 8 && data >= (size_t)(1L << (s * 8))) 
			s++;
		return s;
		
	}
	static inline size_t getPaddingByteCount(size_t bytes)
	{
		size_t paddingBytes = 0;
		for (size_t i = 0; i < bytes/2; i++)
		{
			if (i != 0 && i % 2 == 0)
			{
				paddingBytes += 2;
			}
		}
		return paddingBytes;
	}

	static inline void writeToByteArray(size_t data, size_t at, byte_t* destArray)
	{
		size_t length = bytesNeeded(data);
		size_t currentPosition = 0;
		size_t bitMask = 0x000000FF;
		//little endian
		for (size_t i = at; i < length + at; i++)
		{
			destArray[i] = (byte_t)((data & bitMask) >> (currentPosition * 8));
			currentPosition++;
			bitMask <<= 8;
		}
	}

	/* Functions for writing the BMP file */
	static inline void writeFileHeader(byte_t* destArray,size_t fileSize)
	{

		writeToByteArray(BF_TYPE,		0x00, destArray);			// bfType
		writeToByteArray(fileSize,		0x02, destArray);			// bfSize
		writeToByteArray(BF_RESERVED,   0x06, destArray);			// bfReserved	
		writeToByteArray(BF_OFFBITS,	0x0A, destArray);			// bfOffbits

	}
	static inline void writeInfoHeader(byte_t* destArray,size_t width, size_t height)
	{

		const size_t imageSizeWithoutPadding = (width * height * 3);
		const size_t BI_IMAGESIZE = imageSizeWithoutPadding + getPaddingByteCount(imageSizeWithoutPadding);
		writeToByteArray(INFOHEADER_SIZE,	0x0E, destArray);	// biSize 
		writeToByteArray(width,				0x12, destArray);	// biWidth
		writeToByteArray(height,			0x16, destArray);	// biHeight
		writeToByteArray(BI_PLANES,			0x1A, destArray);	// biPlanes
		writeToByteArray(BI_BITCOUNT,		0x1C, destArray);	// biBitCount
		writeToByteArray(BI_COMPRESSION,	0x1E, destArray);	// biCompression
		writeToByteArray(BI_IMAGESIZE,		0x22, destArray);	// biSizeImage
		writeToByteArray(BI_XPELSPERMETER,	0x26, destArray);	// biXPelsPerMeter
		writeToByteArray(BI_YPELSPERMETER,	0x2A, destArray);	// biYPelsPerMeter
		writeToByteArray(BI_CLRUSED,		0x2E, destArray);	// biClrUsed 
		writeToByteArray(BI_CLRIMPORTANT,	0x32, destArray);	// biClrImportant 
	
	}
	static inline void writeImageData(byte_t* destArray, rgb24_t* colorArray, size_t width, size_t height)
	{
		const size_t imageSizeWithoutPadding = (width * height * 3);
		const size_t paddingNeeded = getPaddingByteCount(imageSizeWithoutPadding);
		const size_t BI_IMAGESIZE = imageSizeWithoutPadding + paddingNeeded;
		size_t index = 0;
		size_t writtenBytes = 0;
		size_t paddingOffset = 0;

		size_t i; 
		for (i = BF_OFFBITS; i <= BF_OFFBITS + BI_IMAGESIZE; i = i + 3)
		{
			if (writtenBytes % 6 == 0 && writtenBytes != 0)
			{
				//Two bytes padding for every 6 bytes written. To allign memory
				destArray[paddingOffset + i] = 0x00;
				destArray[paddingOffset + i + 1] = 0x00;
				paddingOffset += 2;
			}
			rgb24_t color = colorArray[index++];
			byte_t R = (color & 0xFF0000) >> 16;
			byte_t G = (color & 0x00FF00) >> 8;
			byte_t B = (color & 0x0000FF);
			destArray[paddingOffset + i + 2]	 = B;
			destArray[paddingOffset + i + 1] = G;
			destArray[paddingOffset + i] = R;	

			writtenBytes += 3;
		}

	}

	/* Functions for writing files byte-wise */

	static inline bool fileExists(const char *filename)
	{
		std::ifstream ifile(filename);
		return (bool)ifile;
	}

	static std::string correctFileName(std::string fileName)
	{
		size_t lastIndex = fileName.length() - 1;
		std::string extention = fileName.substr(fileName.length() - 4, 4);
		if (extention == ".bpm")
		{
			fileName += ".bpm";
		}
		size_t i = 1;
		std::string toCheck = fileName;
		std::string temp = fileName;
		while (fileExists(toCheck.c_str()))
		{
			toCheck = temp.insert(temp.length() - 4, std::to_string(i));
			temp = fileName;
			i++;
		}
		return toCheck;
	}

	static inline void writeOut(byte_t* toWrite,size_t length,const char* path)
	{
		std::string correctedPath = correctFileName(path);
		std::ofstream fileStream;
		fileStream.open(correctedPath,std::ios::binary);
		for (size_t i = 0; i < length; i++)
		{
			fileStream << toWrite[i];
		}
		fileStream.close();
	}
public:
	
	static inline rgb24_t getColor(byte_t R, byte_t G, byte_t B)
	{
		rgb24_t ret = 0x000000;

		ret = (ret | R) << 8;
		ret = (ret | G) << 8;
		ret = (ret | B);
		return ret;
	}

	static inline int ArrayToBMP(rgb24_t* colorArray, size_t width, size_t height, const char* path)
	{
		const size_t imageSizeWithoutPadding = (width * height * 3);
		const size_t padding = getPaddingByteCount(imageSizeWithoutPadding);
		const size_t BI_IMAGESIZE = imageSizeWithoutPadding + padding;
		size_t arrayLength = width * height;
		size_t fileHeaderSize = 14;
		size_t infoHeaderSize = 40;
		size_t fileSize = infoHeaderSize + fileHeaderSize + BI_IMAGESIZE;
		byte_t* bitmap = new byte_t[fileSize];
		for (size_t i = 0; i < fileSize; i++)
		{
			bitmap[i] = 0x00;
		}


		writeFileHeader(bitmap, fileSize);
		writeInfoHeader(bitmap, width, height);
		writeImageData(bitmap, colorArray, width, height);
		writeOut(bitmap, fileSize, path);

		delete[] bitmap;
		return 0;
	}
};
