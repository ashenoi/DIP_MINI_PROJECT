
#include "stdafx.h"
#include "pair_motion.h"
#include <iostream>

using namespace cv;
using namespace std;

//int main(int argc)//, _TCHAR* argv[])
int main(int argc, char** argv )
{			
  //NOTE!!!! THESE SEARCH SIZES CANNOT BE THE SAME SIZE -- THEY NEED TO GO DOWN BY A FACTOR OF TWO AT EACH LEVEL!!!!!

  int search_sizes[] = {64, 64, 64, 128}; //searchsizes for middlebury most recent -- interpolation factor of 4 -- 4 levels of hierarchy instead of 3 -- smaller block sizes
  int block_sizes[] = {32, 32, 32, 32};
  
  int search_sizes_nonsquare_x[] = {16, 32, 64};
  int search_sizes_nonsquare_y[] = {16, 32, 64};

  int block_sizes_nonsquare_x[] = {8, 8, 16};
  int block_sizes_nonsquare_y[] = {8, 8, 16};  

  std::ofstream fout1; 

  const char* FILENAME_FRAME1;// = "./middlebury/images/Dimetrodon/frame10.png";
  const char* FILENAME_FRAME2;// = "./middlebury/images/Dimetrodon/frame11.png";
  IplImage *image1, *image2, *image1_interp, *image2_interp;

  Pair_Motion Pair1(search_sizes, block_sizes, search_sizes_nonsquare_x, block_sizes_nonsquare_x, search_sizes_nonsquare_y, block_sizes_nonsquare_y); //for the first set of images
       
  //double correlation_value;
  double interp_factor = 4.0;
    
 
  //-----------------------MIDDLEBURY SEQUENCES WITH KNOWN GROUND TRUTH------------------------------

    if (argc != 3) 
    {
	    std::cout<<"Pass the two images\n";
	    return 1;
    }
  
    //Dimetrodoon
    FILENAME_FRAME1 = argv[1];
    FILENAME_FRAME2 = argv[2];  
    image1 = cvLoadImage(FILENAME_FRAME1, CV_LOAD_IMAGE_UNCHANGED);
    image1_interp = cvCreateImage(cvSize(image1->width*(int)interp_factor, image1->height*(int)interp_factor), IPL_DEPTH_8U, 3);
    cvResize(image1, image1_interp, CV_INTER_CUBIC);
    image2 = cvLoadImage(FILENAME_FRAME2, CV_LOAD_IMAGE_UNCHANGED);
    image2_interp = cvCreateImage(cvSize(image2->width*(int)interp_factor, image2->height*(int)interp_factor), IPL_DEPTH_8U, 3);
    cvResize(image2, image2_interp, CV_INTER_CUBIC);  	
//    std::cout<<"ASHWIN"<<image1->height<<" "<<image1->width<<"\n";
//    std::cout<<"ASHWIN"<<image1_interp->height<<" "<<image1_interp->width<<"\n";
	//cvNamedWindow("main", CV_WINDOW_AUTOSIZE); 
    Pair1.start_calculation_nointerp(image2_interp, image1_interp, 24);
    //MVs stored in Pair1.Computed_Data.v_x1, Pair1.Computed_Data.v_y1  
    Pair1.clean_up_nointerp();  
    cvReleaseImage(&image1);
    cvReleaseImage(&image2); 
    cvReleaseImage(&image1_interp);
    cvReleaseImage(&image2_interp); 	
  	
    return 0;
}
