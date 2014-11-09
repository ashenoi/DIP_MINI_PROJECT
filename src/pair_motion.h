#ifndef __Pair_Motion__
#define __Pair_Motion__

#include "stdafx.h"

class MF_data { //motion vectors and frame data
  public:
    int * v_x1, * v_y1, *overlap;
	double *reliability;
	IplImage *frame1;
};

class MV_array { //this is the class which just has the x and y component of the MV.  This makes it easier for when we store multiple MVs in the BM step.
  public:
	MV_array();
	int count;
	int x[30];
	int y[30];
	int SAD[30];
	int dup;
};

class Pair_Motion {
  public:       
    MF_data Computed_Data;
	double * v_x1sub, * v_y1sub; //For subpixel MVs using the method of Stanely Chan which requires no interpolation
	IplImage *frame_predict;
	IplImage *debug, *debug2;
	int width2, height2, step1, step2, level2_search_size, level2_block_size, v_shift2, start_pos_level2;
	int width1, height1, level1_search_size, level1_block_size, v_shift1, start_pos_level1; //need these for the non_interpME
	int add_height, add_width, add_height1, add_width1, add_height2, add_width2, add_height3, add_width3, add_height4, add_width4; //this is how much we pad the borders of the images
	
	//These are for non-square block sizes.
	int start_pos_level1_x, start_pos_level1_y;
	int level1_block_size_x, level1_block_size_y;

	Pair_Motion(int * search_sizes, int * block_sizes, int * search_sizes_nonsquare_x, int * block_sizes_nonsquare_x, int * search_sizes_nonsquare_y, int * block_sizes_nonsquare_y); //initializes both square block sizes and non-square block sizes together.
	void update_sizes(int * search_sizes, int * block_sizes);
	void start_calculation_nointerp(IplImage*& image1, IplImage*& image2, int lambda_value); 
	void start_calculation_nointerp_nonsquare(IplImage*& image1, IplImage*& image2, int lambda_value); 		
	double calculate_autocorr(IplImage *& image1, int b_size);
	void draw_motion_vectors();
	void draw_motion_vectors_nonsquare();
	void drawblock_currentframe();
	void draw_test_boxes();
	void draw_MCblocks_nonsquare();
	void frame_prediction();
	void frame_prediction_nonsquare();
	void clean_up();
	void clean_up_nointerp();
    ~Pair_Motion();
  
  private:	    
	void pad_images(IplImage*& imageA, IplImage*& imageB, IplImage*& imageA_pad, IplImage*& imageB_pad, int start_pos);
	void pad_images_nonsquare(IplImage*& imageA, IplImage*& imageB, IplImage*& imageA_pad, IplImage*& imageB_pad, int start_pos_x, int start_pos_y);	
	void pad_image_color(IplImage*& imageA, IplImage*& imageA_pad, int start_pos);	
	void calculate_motion_vectors_lagrange(int lambda_value);
	void calculate_motion_vectors_weighting(int lambda_value);
	void calculate_motion_vectors_overlap(int lambda_value);
	void calculate_motion_vectors_lagrange_nonsquare(int lambda_value);	
	void calculate_reliability();
	void calculate_pixel_reliability();
	void validity_for_SR();
	void calculate_pixel_reliability_multiplevectors();
	void calculate_smoothness_reliability();
	void calculate_smoothness_reliability2();
	void calculate_deviation_reliability();
	void calculate_gradient_reliability();
    void calculate_block_overlap();
	void calculate_pixel_overlap();
	void calculate_pixel_overlap_multiplevectors(double& mean);
	double find_overlap_max();
	int get_overlap_volume(int x_pos, int y_pos);
	void calculate_singleMV_overlap(int b_size, int pos_y, int pos_x, int& top_left, int& top_right, int& bottom_left, int& bottom_right);
	//int calculate_singleMV_overlap(int b_size, int i, int j);
	void onelevl_BM();
	void onelevl_BM_nonsquare();
	void onelevlspiral_BM();
	void onelevlspiral_BM_minoverlap();
	void onelevlspiral_BM_arrayed();
	void onelevlspiral_BM_sorted();
	void onelevlspiral_BM_sorted_v2();
	//void onelevlspiral_BM_adapt();
	void nextlevl_BM();
	void nextlevl_BM_nonsquare();
	void nextlevlspiral_BM();
	void nextlevlspiral_BM_smooth();
	void nextlevlspiral_BM_minoverlap(int start_direction);
	void nextlevlspiral_BM_weightedoverlap(int start_direction);
	void nextlevlspiral_minoverlap2();
	void nextlevlspiral_BM_adapt();
	void nextlevlspiral_BM_arrayed();
	void nextlevlspiral_BM_sorted();
	void nextlevlspiral_BM_sorted_v2();
	void setMVs_iter();
	void setMVs_iter_nonsquare();
	void setMVs_iter_nonsquare_obo();
	//void setMVs_iter_oddbsize();
	void copyto_oldMVs();
	int calculate_SAD(int y, int x, int l, int k);
	int calculate_SAD_nonsquare(int y, int x, int l, int k);
	int calculate_local_SAD(int y, int x, int l, int k);
	double calculate_SAD2(int y, int x, int l, int k);
	void refine_MVs();
	void search_near_MCblock();
	void search_near_MCblock2(); 
	void minimize_overlap(); 
	void minimize_overlap2();
	void add_smoothness8_old(double lambda_value);
	void add_smoothness8(double lambda_value);
	void add_smoothness8_overlap(double lambda_value); 
	void add_smoothness8_weighted(double lambda_value); 
	void add_smoothness8_weighted2(double lambda_value); 
	void add_smoothness4_nonsquare(double lambda_value);
	void add_smoothness8_nonsquare(double lambda_value);
	//void get_subpixel_MVs();
	double calc_derivX(int k, int l);
    double calc_derivY(int k, int l);
	double min_array(double * array_vals, int size, int &min_index);
	int min_array_val(int * array_vals, int size);
	double min_array_val(double * array_vals, int size);
	double max_array_val(double * array_vals, int size);
	int opt_med5(int * p);
	int opt_med9(int * p);
    void PIX_SORT(int a, int b);
    void PIX_SWAP(int a, int b);
	double cost_fn(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_dynamic_smoothness(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_top_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_left_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_right_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_bottom_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_leftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_rightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_bottomleftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn_bottomrightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x);
	double cost_fn4(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4a(int pos_y, int pos_x, int orig_y, int orig_x);	
	double cost_fn4a_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);	
	double cost_fn4b(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4b_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4c(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4c_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4d(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn4d_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8top(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8bottom(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8left(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8right(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8leftcorn(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8rightcorn(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8bottomleftcorn(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8bottomrightcorn(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8a(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8a_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8a_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	//double cost_fn8a_old(int pos_x, int pos_y, int orig_x, int orig_y);
	double cost_fn8b(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8b_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8b_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	//double cost_fn8b_old(int pos_x, int pos_y, int orig_x, int orig_y);
	double cost_fn8c(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8c_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8c_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8d(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8d_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8d_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8e(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8e_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8e_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	//double cost_fn8e_old(int pos_x, int pos_y, int orig_x, int orig_y);
	double cost_fn8f(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8f_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8f_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8g(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8g_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8g_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	//double cost_fn8g_old(int pos_x, int pos_y, int orig_x, int orig_y);
	double cost_fn8h(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8h_weighted(int pos_y, int pos_x, int orig_y, int orig_x);
	double cost_fn8h_nonsquare(int pos_y, int pos_x, int orig_y, int orig_x);
	double vector_cost1(int pos_y, int pos_x, int orig_y, int orig_x);
	double vector_cost2(int pos_y, int pos_x, int orig_y, int orig_x);
	double vector_cost3(int pos_y, int pos_x, int orig_y, int orig_x);
	double vector_cost4(int pos_y, int pos_x, int orig_y, int orig_x);
	double vector_cost5(int pos_y, int pos_x, int orig_y, int orig_x);
	int calculate_block_value(int y, int x);
	double angle_similarity(int y, int x, int i, int j);
	void reset_draw_image();
	double min(double x, double y);
	int min2(int x, int y);
	double max(double x, double y);
	double twomin_diff(int * array_vals, int size);

    uchar * data_level1a, * data_level1b; //Level 1 -- highest resolution
	int lambda1;
	double * reliability1; 
    int * overlap1; 
	MV_array *mult_vec1;
	IplImage *level1a, *level1b, *level1a_pad, *level1a_pad_color, *level1b_pad_color, *level1b_pad, *level1a_grey, *level1b_grey;
		
	IplImage *frame2, *frame2_interp, *level2a_pad, *level2b_pad, *level2a_grey, *level2b_grey;  //Level 2	 
	uchar * data_level2a, * data_level2b;
	int lambda2;
	int * v_x2, * v_y2;
	MV_array *mult_vec2;	
	int * overlap2;
				
	int width3, height3, step3, level3_search_size, level3_block_size, v_shift3; //Level 3 
	uchar * data_level3a, * data_level3b;
	int lambda3, start_pos_level3;
	int * v_x3, * v_y3;
	MV_array *mult_vec3;	
	int * overlap3;
	IplImage *level3a_grey, *level3b_grey, *level3a_pad, *level3b_pad;

	int width4, height4, step4, level4_search_size, level4_block_size, v_shift4; //Level 4 -- lowest resolution
	uchar * data_level4a, * data_level4b;
	int lambda4, start_pos_level4;
	int * v_x4, * v_y4;	
	int * overlap4;
	IplImage *level4a_grey, *level4b_grey, *level4a_pad, *level4b_pad;

	//These are going to hold the arguments for each level while it's been worked on
	int width, height, width_previous, height_previous, predict_step, color_step, step, step_previous, search_size, b_size, b_size_previous, v_shift, v_shift_previous, start_pos_prev; //Holds current level values
	uchar * data_a, * data_b, * data_predict, *data_color1;
	int lambda, start_pos, boundary_min;
	int * v_x, * v_y, * v_xprev, * v_yprev;
	MV_array *mult_vec;
	double spatial_test[8];
	std::ofstream fout; //for debugging		
	int total_count, level; //debugging

	//The variables below are all for handling block matching with non-square blocks.
	int v_shift1_x, v_shift1_y, v_shift2_x, v_shift2_y, v_shift3_x, v_shift3_y, v_shift_x, v_shift_y, v_shift_previous_x, v_shift_previous_y;
	int level1_search_size_x, level1_search_size_y, level2_search_size_x, level2_search_size_y, level3_search_size_x, level3_search_size_y;
	int level2_block_size_x, level2_block_size_y, level3_block_size_x, level3_block_size_y, b_size_previous_x, b_size_previous_y, b_size_x, b_size_y;
	int start_pos_level2_x, start_pos_level2_y, start_pos_level3_x, start_pos_level3_y, start_pos_x, start_pos_y, start_pos_x_prev, start_pos_y_prev; 

};

#endif
