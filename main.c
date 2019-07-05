#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//////////////////////
// ALGORITHM INPUT VALUES
//////////////////////
#define GCarray_width 4
#define pixel_size 3






//////////////////////
// MACROS
//////////////////////
#define GCarray_length pow(2,GCarray_width)




/////////////////////
// STRUCTURES AND VARIABLES
/////////////////////

struct FileHeader {
	char signature[2];		//signature to identify the file format. Bitmap = 'BM'
	char fsize[4];			//size of the BMP file in bytes
	char reserved[4];		//reserved; actual value depends on the application that creates the image
	char dataoffset[4];		//offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.
} FileHeader;

struct BMHeader {
	char headersize[4]; 		//size of this header (40 bytes)
	char imagewidth[4]; 		//bitmap width in pixels (signed integer)
	char imageheight[4]; 		//bitmap height in pixels (signed integer)
	char colorplanes[2]; 		//number of color planes (must be 1)
	char pixelsize[2]; 			//number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32.
	char compression[4]; 		//compression method being used. 0 = none used.
	char imagesize[4]; 			//image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
	char hres[4];				//horizontal resolution of the image. (pixel per metre, signed integer)
	char vres[4];				//vertical resolution of the image. (pixel per metre, signed integer)
	char colorpalette[4];		//number of colors in the color palette, or 0 to default to 2n
	char importantcolors[4];	//number of important colors used, or 0 when every color is important; generally ignored
} BMHeader;

//Prototypes
char *strrev(char *dest, char *str);
char *splitstr(char *str, int count);
char *gc_gen (int resolution);

int main () {
/*
    int resolution = 13;
    int gc_str_length = resolution * pow(2,resolution);

    double length = (resolution * pow(2, resolution)) + 1;
double row_length = pow(2, resolution)+1;
    char *gc_str = (char*) malloc(length);
    */



    //string functions

    char *gc_str = gc_gen(6);


    printf("\ngc_str length: %d",strlen(gc_str));
    printf("\n%s",gc_str);


    return 0;
}

//Inverts a string
//Needs destination string
char *strrev(char *dest, char *str)
{
      char *p1, *p2, *p3, *p4;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1, p3 = dest, p4 = dest + strlen(str) - 1; p2 > p1; ++p1, --p2, ++p3, --p4)
      {
            *p3 = *p1 ^ *p2;
            *p4 = *p2 ^ *p3;
            *p3 = *p3 ^ *p4;

      }
      //Add null char to the end.
      p4 = dest + strlen(str);
      *p4 = '\0';
      return str;
}
//Sets first half of the string to zeros and second half to ones.
char *splitstr(char *str, int length) {

char *p1;
int i = length;

    for (p1 = str; i > 0; ++p1, --i) {
        if(i < (length/2)+1)
        {
        *p1 = '1';

        } else {
        *p1 = '0';
        }
    }

    //Adding null char to the end

    *p1 = '\0';



    return str;

}

char *gc_gen (int resolution) {

	double length = (resolution * pow(2, resolution)) + 1;
	double row_length = pow(2, resolution)+1;
    char *gc_str = (char*) malloc(length);
    char *row_str = (char*) malloc(row_length);
    char *row_helper_str = (char*) malloc(row_length);
    char *last_row = (char*) malloc(row_length);
    int i;

    if (!row_str || !row_helper_str) {
        printf("gc_gen null");
        return 0;
        }
   //Setting this to null because in the end will crash when checking if gc_str is null.
   *gc_str = '\0';



    //Constructs each row starting from 1.
    for(i = 1;i < resolution+1;++i)
    {
    int a = pow(2,i);
    printf("\nRow : %d to power %d",i,a);
    splitstr(row_str, a);

    if (i != resolution) {
        strrev(row_helper_str, row_str);
            strcat(row_str, row_helper_str);
            strcpy(row_helper_str, row_str);

            printf("\nrow_str is : %s \nrow_helper_str is : %s", row_str, row_helper_str);

        //Lengthens current row to the total row length.
        for (int j = 1; j<pow(2,resolution-2)/pow(2,i)*2 ;++j)
        {
        strcat(row_str, row_helper_str);
        }

    }

    //Checking if gc_str is empty.
    if (! *gc_str || ! gc_str) {
    printf("\ngc_str null");
    strcpy(gc_str, row_str);
    } else {
    printf("\ngc_str not null");
            strcat(gc_str, row_str);
    }
    printf("\ngc_str :%s",gc_str);

    }

    return gc_str;
}






















