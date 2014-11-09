void Pair_Motion::calculate_motion_vectors_overlap(int lambda_value)
{
	// SAD minimization
	//     Find a set of motion vectors with min SAD score.
	//     Calculate_SAD could be used here
	//     How to store the vectors?? MV_array?? Refer to onelevelspiral_BM_arrayed
	


	// Energy minimimization -- with block reduction
	//     Will have to write a function for Finding Volume. Implement eq (19)
	//     Use setMVs_iter for finding MVs as we reduce block size
	//     Pass the MVs to higher level


	// Hierarchial search: Implement that to get MVs for the next level via SAD minimization
	// 	Repeat the whole process again till we reach the highest level
	
  //Applies to all levels
  boundary_min = 100;//8;
  //This file is used for debugging
  fout.open("motion_vectors.txt");
  //total_count = 0;

  //--------------------Level 3----------------------------
  //Initializations for Level 3
  level = 3;
  width = width3;
  height = height3;
  add_height = add_height3;
  add_width = add_width3;
  step = step3;   
  search_size = level3_search_size;
  b_size = level3_block_size;
  start_pos = start_pos_level3;
  v_shift = v_shift3;
  v_shift_previous = v_shift3;
  data_a = data_level3a;
  data_b = data_level3b;
  v_x = v_x3; 
  //v_x_old = v_x3_old;
  v_y = v_y3;
  //v_y_old = v_y3_old;
  //End of initializations
  onelevlspiral_BM();
  //onelevl_BM();
  for(int k = 0; k < 2; k++)
  {
	b_size = level3_block_size;
	while (b_size > 1) //= (level2_block_size >> 1))
	{      
	  for(int l = 0; l < 2; l++)
	  {
        add_smoothness8((k+l+1)*(b_size << 1));  
	  }
	  setMVs_iter();
	  b_size = (b_size >> 1);
	}	
  } 
  b_size = (level2_block_size >> 1); // set to half of block size needed at next level
  
  //-----------------End of Level 3------------------------

  //---------------------Level 2---------------------------
  //Initializations for Level 2
  level = 2;
  width_previous = width3;
  width = width2;
  height_previous = height3;
  height = height2;
  add_height = add_height2;
  add_width = add_width2;
  step = step2;
  step_previous = step3;
  search_size = level2_search_size;
  b_size_previous = b_size; 
  b_size = level2_block_size;
  //start_pos no change at first
  v_shift = v_shift2;
  v_shift_previous = v_shift3;
  data_a = data_level2a;
  data_b = data_level2b;
  v_xprev = v_x3;
  v_yprev = v_y3;
  v_x = v_x2;
  //v_x_old = v_x2_old;
  v_y = v_y2;
  //v_y_old = v_y2_old;
  //End of initializations
  start_pos_prev = start_pos_level3;
  start_pos = start_pos_level2;
  nextlevlspiral_BM_adapt();
  //nextlevlspiral_BM();
  //nextlevl_BM();  
  for(int k = 0; k < 2; k++)
  {
    b_size = level2_block_size;
	while (b_size > 1) //= (level1_block_size >> 1))
	{
	  for(int l = 0; l < 2; l++)
	  {
        add_smoothness8((k+l+1)*(b_size << 1));   
	  }
      setMVs_iter();
	  b_size = (b_size >> 1);
	}
  }  
  b_size = (level1_block_size >> 1); //set to half of the block size needed at next level
    
  //-----------------End of Level 2------------------------  

  //---------------------Level 1---------------------------
  //Initializations for Level 1
  level = 1;
  width_previous = width2;
  width = width1;
  height_previous = height2;
  height = height1;
  add_height = add_height1;
  add_width = add_width1;
  step = step1;
  step_previous = step2;
  search_size = level1_search_size;
  b_size_previous = b_size;
  b_size = level1_block_size;
  //start_pos no change at first
  v_shift = v_shift1;
  v_shift_previous = v_shift2;
  data_a = data_level1a;
  data_b = data_level1b;
  v_xprev = v_x2;
  v_yprev = v_y2;
  v_x = Computed_Data.v_x1;
  //v_x_old = v_x1_old;
  v_y = Computed_Data.v_y1;
  //v_y_old = v_y1_old;
  //End of initializations    
  start_pos_prev = start_pos_level2;
  start_pos = start_pos_level1;
  nextlevlspiral_BM_adapt();
  //nextlevlspiral_BM();
  //nextlevl_BM();      
  //reliability_threshold = (b_size << 12); 
  for(int k = 0; k < 2; k++)
  {
	b_size = level1_block_size;
	while(b_size > 1)
	{
	  for(int l = 0; l < 2; l++)
 	  {
        add_smoothness8((k+l+1)*(b_size << 1));
	  }
      setMVs_iter();
      b_size = (b_size >> 1);
	}
  }  
  //b_size = 2;
  //setMVs_iter();
  //setMVs_iter_oddbsize();
  //We have 1x1 now
  //b_size = 1;//(b_size >> 1);
  
  //-----------------End of Level 1------------------------  

  //calculate_reliability();
  
}


void Pair_Motion::calculate_reliability()
{
;
}

void Pair_Motion::calculate_pixel_reliability()
{
;
}

void Pair_Motion::validity_for_SR()
{
;
}

void Pair_Motion::calculate_pixel_reliability_multiplevectors()
{
;
}

void Pair_Motion::calculate_smoothness_reliability()
{
;
}

void Pair_Motion::calculate_smoothness_reliability2()
{
;
}

void Pair_Motion::calculate_deviation_reliability()
{
;
}

void Pair_Motion::calculate_gradient_reliability()
{
;
}

void Pair_Motion::calculate_block_overlap()
{
;
}

void Pair_Motion::calculate_pixel_overlap()
{
;
}

void Pair_Motion::calculate_pixel_overlap_multiplevectors(double& mean)
{
;
}

double Pair_Motion::find_overlap_max()
{
;
}

int Pair_Motion::get_overlap_volume(int x_pos, int y_pos)
{
;
}

void Pair_Motion::calculate_singleMV_overlap(int b_size, int pos_y, int pos_x, int& top_left, int& top_right, int& bottom_left, int& bottom_right)
{
;
}

void Pair_Motion::onelevlspiral_BM_minoverlap()
{
;
}

void Pair_Motion::nextlevlspiral_BM_minoverlap(int start_direction)
{
;
}

void Pair_Motion::nextlevlspiral_BM_weightedoverlap(int start_direction)
{
;
}

void Pair_Motion::nextlevlspiral_minoverlap2()
{
;
}

void Pair_Motion::minimize_overlap()
{
;
}
 
void Pair_Motion::minimize_overlap2()
{
;
}

double Pair_Motion::calc_derivX(int k, int l)
{
;
}

double Pair_Motion::calc_derivY(int k, int l)
{
;
}

double Pair_Motion::cost_fn_top_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_left_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_right_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_bottom_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_leftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_rightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_bottomleftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::cost_fn_bottomrightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
;
}

double Pair_Motion::angle_similarity(int y, int x, int i, int j)
{
;
}

