//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//

//*****************************************************************************

#include "Image.h"
#include <math.h> 


// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	BandW = NULL;
	Width = -1;
	Height = -1;
	ImagePath[0] = 0;
}

MyImage::~MyImage()
{
	if ( Data )
		delete Data;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Data   = new char[Width*Height*3];
	BandW = new char[Width*Height];
	strcpy(otherImage->ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}
	for (int i = 0; i<(Height*Width ); i++)
	{
		BandW[i] = otherImage->BandW[i];
	}


}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	Data   = new char[Width*Height*3];
	BandW = new char[Width*Height];
	strcpy( (char *)otherImage.ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	for (int i = 0; i<(Height*Width); i++)
	{
		BandW[i] = otherImage.BandW[i];
	}
	
	return *this;

}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile `");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	 
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int j,k;
	long int i;

	char *Rbuf = new char[Height*Width*1000];
	char *Gbuf = new char[Height*Width*1000];
	char *Bbuf = new char[Height*Width*1000];
	j = 0;
	for (j = 0; j <1000; j++)
	{
	
		for (i = j*Width*Height; i < (j+1)*Width*Height; i++)
		{
			Rbuf[i] = fgetc(IN_FILE);
		}
		for (i = j*Width*Height; i < (j+1)*Width*Height; i++)
		{
			Gbuf[i] = fgetc(IN_FILE);
		}
		for (i = j*Width*Height; i < (j+1)*Width*Height; i++)
		{
			Bbuf[i] = fgetc(IN_FILE);

		}
		
		
	}
	/**


	for (i = Width*Height; i<2 * Width*Height; i++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = Width*Height; i<2 * Width*Height; i++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = Width*Height; i<2 * Width*Height; i++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}

	for (j = 0; j < 300 * Width*Height; j++)
	{
		fgetc(IN_FILE);
	}


	for (i = 2*W*H;i<3*W*H;i++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 2 * W*H; i<3* W*H; i++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 2* W*H; i<3*W*H; i++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}

	for (j = 0; j < 330 * W*H; j++)
	{
		fgetc(IN_FILE);
	}

	for (i = 3 * W*H; i<4 * W*H; i++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 3 * W*H; i<4 * W*H; i++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i =3* W*H; i<4* W*H; i++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	**/

	// Allocate Data structure and copy
	Data = new char[Width*Height*3000];
	BandW = new char[Width*Height*1000];
	for (i = 0; i < 1000*Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
		BandW[i] = char((1.0*float(Rbuf[i] + Gbuf[i] + Rbuf[i])) / 3.0);
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
 char* MyImage::Modify()
{
	int* key_frames = (int *)calloc(999, sizeof(int));
	for (int i = 0; i < 999; i++)
	{
		key_frames[i] = 0;
	}
	key_frames = Shot_Detection();
	int sum=0;
	for (int i = 0; i < 999; i++)
	{
		sum = sum + key_frames[i];
	}
	int size = sum*Height*Width * 3;
	char *Data2 = new char[Height*Width * 15];
	long int i,j,count;
	count = 0;
	int tryin = 0;
	for (j = 0; j < 999; j++)
	{
		if (key_frames[j] == 1)
		{
		
			for (i = j*Width*Height*3; i < (j + 1)*Width*Height*3; i++)
			{
				Data2[count] = Data[i];
				count++;
			}

			tryin++;
			if (tryin == 5)
			{
				break;
			}

		}
	
	}



	return Data2;
}
 int* MyImage::Shot_Detection()
 {
	 char *frame_1 = new char[Height*Width];
	 char *frame_2 = new char[Height*Width];
	float Hist_Differences[1000];
	int*slot_frames = (int *)calloc(999, sizeof(int));
	int*key_frames = (int *)calloc(999, sizeof(int));
	 int *Hist_frame_1 = (int *)calloc(256, sizeof(int)) ;
	 int *Hist_frame_2 = (int *)calloc(256, sizeof(int));
	 float Mean,Standard_derivation;
	 long int i = 0;
	 int j;
	 //Converting Frames into Gray-scale images
	 for ( j = 0; j < 999; j++)
	 {
		 for ( i = (j*Width*Height ); i < (j + 1)*Height*Width ; i++)
		 {
			 frame_1[i - (j*Width*Height)] = BandW[i];
		 }
		 for ( i = ((j+1)*Width*Height ); i < (j + 2)*Height*Width ; i++)
		 {
			 frame_2[i -( (j + 1)*Width*Height)] = BandW[i];
		 }

		 Hist_frame_1 = Hist_calculation(frame_1, Hist_frame_1);
		 Hist_frame_2 = Hist_calculation(frame_2, Hist_frame_2);

		 float diff = 0;
		 for (int k = 0; k < 256; k++)
		 {
			 diff = float((Hist_frame_1[k] - Hist_frame_2[k])*(Hist_frame_1[k] - Hist_frame_2[k]))+diff;

		 }
		 Hist_Differences[j] = diff;
	 }


	 float sum=0;

	 for (int j = 0; j < 999; j++)
	 {
		 sum = Hist_Differences[j]+sum;
	 }

	 Mean = sum / 999;

	  sum = 0;

	 for (int j = 0; j < 999; j++)
	 {
		 sum = ((Hist_Differences[j] - Mean)* (Hist_Differences[j] - Mean ))+ sum;
	 }
	 Standard_derivation = sqrt(sum / 999);

	 float Threshold = Mean + Standard_derivation;

	 slot_frames[0] = 1;

	 for (int j = 1; j < 999; j++)
	 {
		 if (Hist_Differences[j] > Threshold)
		 {
			 slot_frames[j] = 1;
		 }
		 else
			 slot_frames[j] = 0;
	 }

	// key_frames = Key_Frame_Detection(slot_frames);
	 return(slot_frames);
	 }


 int* MyImage::Key_Frame_Detection(int* slot_frames)
 {
	 int k = 0;
	 int j = 1;
	 int save;
	 char *frame_1 = new char[Height*Width];
	 char *frame_2 = new char[Height*Width];
	 int*key_frames = (int *)calloc(999, sizeof(int));
	 int *Hist_frame_1 = (int *)calloc(256, sizeof(int));
	 int *Hist_frame_2 = (int *)calloc(256, sizeof(int));
	 float Hist_Diff;
	 for (int i = 0; i < 999; i++)
	 {
		 key_frames[i] = 0;
	 }
	 for(k = 0; k < 999;k++)
	 {
		 
		 
		 if (!(slot_frames[k] == 0))
		 {
			 save = 0;
			 j = 1;
			 
			 while (!(slot_frames[k + j])&& (k+j<999))
			 {
				 for (int i = (k*Width*Height); i < (k+ 1)*Height*Width; i++)
				 {
					 frame_1[i - k*Width*Height] = BandW[i];
				 }
				 for (int i = ((k+j)*Width*Height); i < (k+j + 1)*Height*Width; i++)
				 {
					 frame_2[i - (k + j)*Width*Height] = BandW[i];
				 }

				 Hist_frame_1 = Hist_calculation(frame_1, Hist_frame_1);
				 Hist_frame_2 = Hist_calculation(frame_2, Hist_frame_2);

				 float diff = 0;
				 for (int k = 0; k < 256; k++)
				 {
					 diff = (float((Hist_frame_1[k] - Hist_frame_2[k])*(Hist_frame_1[k] - Hist_frame_2[k])) / float(Hist_frame_1[k])) + diff;

				 }
				 if (k==0)
				 {
				 Hist_Diff = diff;
			 }
				 if (diff == max(diff, Hist_Diff))
				 {
					 save = k + j;
				 }
				 j = j + 1;
			 }


			 key_frames[save] = 1;
			 k = k + j;
			

		 }
		

	 }
	
	 return(key_frames);
 }
 
 int* Hist_calculation(char* frame,int* Hist)
 {
	
	int  height = 288;
	 int width = 352;
	 for (int j = 0; j < 256; j++)
	 {
		 Hist[j] = 0;
	 }
	 for (int i = 0; i < height*width; i++)
	 {
		 Hist[int(frame[i])]++;
	 }
	 return Hist;
 }
 
