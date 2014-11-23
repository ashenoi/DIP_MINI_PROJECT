void Pair_Motion::calculate_motion_vectors_overlap(int lambda_value)
{
	int local_h;
	int local_w;
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

////  std::cout<<"ASHWIN1\n";
 
  //--------------------Level 4----------------------------
  //Initializations for Level 4
  level = 4;
  width = width4;
  height = height4;
  add_height = add_height4;
  add_width = add_width4;
  step = step4;   
  search_size = level4_search_size;
  b_size = level4_block_size;
  start_pos = start_pos_level4;
  v_shift = v_shift4;
  v_shift_previous = v_shift4;
  data_a = data_level4a;
  data_b = data_level4b;
  v_x = v_x4; 
  //v_x_old = v_x4_old;
  v_y = v_y4;
  //v_y_old = v_y4_old;
  //End of initializations
  Computed_Data.overlap = overlap4;
  onelevlspiral_BM();
  calculate_block_overlap();
////  std::cout<<"ASHWIN2\n";
  //onelevl_BM();
  for(int k = 0; k < 2; k++)
  {
	b_size = level4_block_size;
	while (b_size > 1) //= (level2_block_size >> 1))
	{      
  calculate_block_overlap();
	  for(int l = 0; l < 2; l++)
	  {
        add_smoothness8_overlap((k+l+1)*(b_size << 1));  
	  }
	  setMVs_iter();
	  b_size = (b_size >> 1);
	}	
  } 
  b_size = (level3_block_size >> 1); // set to half of block size needed at next level
  
////  std::cout<<"ASHWIN4\n";
  //-----------------End of Level 4------------------------


  //---------------------Level 3---------------------------
  //Initializations for Level 3
  level = 3;
  width_previous = width4;
  width = width3;
  height_previous = height4;
  height = height3;
  add_height = add_height3;
  add_width = add_width3;
  step = step3;
  step_previous = step4;
  search_size = level3_search_size;
  b_size_previous = b_size; 
  b_size = level3_block_size;
  //start_pos no change at first
  v_shift = v_shift3;
  v_shift_previous = v_shift4;
  data_a = data_level3a;
  data_b = data_level3b;
  v_xprev = v_x4;
  v_yprev = v_y4;
  v_x = v_x3;
  //v_x_old = v_x3_old;
  v_y = v_y3;
  //v_y_old = v_y3_old;
  //End of initializations
  start_pos_prev = start_pos_level4;
  start_pos = start_pos_level3;
  Computed_Data.overlap = overlap3;

  nextlevlspiral_BM_adapt();
  calculate_block_overlap();
  //nextlevlspiral_BM();
  //nextlevl_BM();  
  for(int k = 0; k < 2; k++)
  {
    b_size = level3_block_size;
	while (b_size > 1) //= (level1_block_size >> 1))
	{
  calculate_block_overlap();
	  for(int l = 0; l < 2; l++)
	  {
        add_smoothness8_overlap((k+l+1)*(b_size << 1));   
	  }
      setMVs_iter();
	  b_size = (b_size >> 1);
	}
  }  
  b_size = (level2_block_size >> 1); //set to half of the block size needed at next level
    
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
  Computed_Data.overlap = overlap2;
  nextlevlspiral_BM_adapt();
  calculate_block_overlap();
  //nextlevlspiral_BM();
  //nextlevl_BM();  
  for(int k = 0; k < 2; k++)
  {
    b_size = level2_block_size;
	while (b_size > 1) //= (level1_block_size >> 1))
	{
  calculate_block_overlap();
	  for(int l = 0; l < 2; l++)
	  {
        add_smoothness8_overlap((k+l+1)*(b_size << 1));   
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
  Computed_Data.overlap = overlap1;
  nextlevlspiral_BM_adapt();
  calculate_block_overlap();
  //nextlevlspiral_BM();
  //nextlevl_BM();      
  //reliability_threshold = (b_size << 12); 
  for(int k = 0; k < 2; k++)
  {
	b_size = level1_block_size;
	while(b_size > 1)
	{
  calculate_block_overlap();
	  for(int l = 0; l < 2; l++)
 	  {
        add_smoothness8_overlap((k+l+1)*(b_size << 1));
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


      
//  for(int i = 0 ; i< height1; i++)
//  {
//          for(int j= 0; j <width1 ; j++)
//          {
//        	  fout<<v_x[i*step1+j]<<","<<v_y[i*step1+j]<<"\n";
//        	  
//          }
//  } 
  local_w = 0 ;
  local_h = 0;
  	std::cout<<start_pos_level1<<" "<<add_width1<<" "<<add_height1<<" "<<start_pos_level1<<"\n";
  for (int i = start_pos_level1 ; i < height1-(add_height1 - start_pos_level1 ); i+=4) //goes through all vertical pixels
  {
	  local_h++;
	for (int j = start_pos_level1 ; j < width1-(add_width1 - start_pos_level1 ); j+=4) //goes through all horizontal pixels
    {	   
	    fout<<Computed_Data.v_x1[i*step1+j]<<","<<Computed_Data.v_y1[i*step1+j]<<"\n";	
	  local_w++;
				
    }
	
  }
  	std::cout<<local_h<<" "<<local_w<<"\n";
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
  	for (int i = 0; i < height; i+=1)  //goes through all vertical pixels
  	{
		for (int j = 0; j < width; j+=1)  //goes through all horizontal pizels
		{
					Computed_Data.overlap[i*step+j]=0;
			
		}
	}

  	for (int i = start_pos; i < height-(add_height - start_pos); i+=b_size)  //goes through all vertical pixels
  	{
		for (int j = start_pos; j < width-(add_width - start_pos); j+=b_size)  //goes through all horizontal pizels
		{
			for(int k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
				for(int l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
					Computed_Data.overlap[k*step+l]+=1;
			
		}
	}
			    	
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
// //std::cout<<"ASHWIN overlap "<<Computed_Data.overlap[y_pos*step+x_pos]<<"\n";
 return Computed_Data.overlap[y_pos*step+x_pos]; 
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
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  //sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  //sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_left_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  //sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  //sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  //sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_right_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  //sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  //sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_bottom_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  //sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  //sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  //sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_leftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  //sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  //sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  //sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  //sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_rightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  //sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  //sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  //sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  //sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_bottomleftcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  //sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  //sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  //sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  //sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::cost_fn_bottomrightcorn_overlap(int v_yval, int v_xval, int orig_y, int orig_x)
{
  // posx, pos y are for the neighboring block we will try
  // orig_x and orig_y are for the original center block

  double sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8;
  int entry_x = v_xval;
  int entry_y = v_yval;

  //assumes 8-connected neighborhood  
  sum_1 = 0;
  sum_2 = 0;
  sum_3 = 0;
  sum_4 = 0;
  sum_5 = 0;
  sum_6 = 0;
  sum_7 = 0;
  sum_8 = 0;

  //Function 3 in paper
  sum_1 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y-b_size)*step+orig_x]));
  sum_2 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x-b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x-b_size)]));
  //sum_3 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+orig_x]) + abs(entry_y - v_y[(orig_y+b_size)*step+orig_x]));
  //sum_4 = min(boundary_min, abs(entry_x - v_x[orig_y*step+(orig_x+b_size)]) + abs(entry_y - v_y[orig_y*step+(orig_x+b_size)]));
  sum_5 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x-b_size)]));
  //sum_6 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x-b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x-b_size)]));
  //sum_7 = min(boundary_min, abs(entry_x - v_x[(orig_y-b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y-b_size)*step+(orig_x+b_size)]));
  //sum_8 = min(boundary_min, abs(entry_x - v_x[(orig_y+b_size)*step+(orig_x+b_size)]) + abs(entry_y - v_y[(orig_y+b_size)*step+(orig_x+b_size)]));

  return (sum_1 + sum_2 + sum_3 + sum_4 + sum_5 + sum_6 + sum_7 + sum_8);     
}

double Pair_Motion::angle_similarity(int y, int x, int i, int j)
{
;
}
void Pair_Motion::add_smoothness8_overlap(double lambda_value) 
{
  int min_index, i, j, k, l, n;
  double lambda;
  double candidate[9];  
  
  //The variables below are for removing duplicate MVs
  int duplicate_list[9] = {0};
  int hash[9] = {0};
  int MV_x[9];
  int MV_y[9];
    
  int bs_squared = b_size;
//  std::cout<<"ASHWIN 1\n"; 
  lambda = lambda_value;
	  
  for (i = start_pos + b_size; i < height-(add_height - start_pos + b_size); i+=b_size) //goes through all vertical pixels
  {
	for (j = start_pos + b_size; j < width-(add_width - start_pos + b_size); j+=b_size) //goes through all horizontal pixels
    {	   

	  //Initalize duplicate list to zero -- no duplicates
	  for(k = 0; k < 9; k++)
	  {
       duplicate_list[k] = 0;  
	   hash[k] = 0;
	  }

	  MV_x[0] = v_x[i*step+j];
	  MV_y[0] = v_y[i*step+j];
	  MV_x[1] = v_x[(i-b_size)*step+j];
	  MV_y[1] = v_y[(i-b_size)*step+j];
	  MV_x[2] = v_x[i*step+(j-b_size)];
	  MV_y[2] = v_y[i*step+(j-b_size)];
	  MV_x[3] = v_x[(i+b_size)*step+j];
	  MV_y[3] = v_y[(i+b_size)*step+j];
	  MV_x[4] = v_x[i*step+(j+b_size)];
	  MV_y[4] = v_y[i*step+(j+b_size)];
	  MV_x[5] = v_x[(i-b_size)*step+(j-b_size)];
	  MV_y[5] = v_y[(i-b_size)*step+(j-b_size)];
	  MV_x[6] = v_x[(i+b_size)*step+(j-b_size)];
	  MV_y[6] = v_y[(i+b_size)*step+(j-b_size)];
	  MV_x[7] = v_x[(i-b_size)*step+(j+b_size)];
	  MV_y[7] = v_y[(i-b_size)*step+(j+b_size)];	  
	  MV_x[8] = v_x[(i+b_size)*step+(j+b_size)];
	  MV_y[8] = v_y[(i+b_size)*step+(j+b_size)];

	  //Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
      for(k = 1; k < 9; k++)
      {
        for(l = 0; l < 9; l++)
	    {
	      if ((l == k) || (duplicate_list[k] == 1))
	        continue;
          else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	      {
	        duplicate_list[l] = 1;
	      } 	    
	    }
      }	  
	 
	  //Subtract out the overlap for the one already assigned prior to smoothness function.
	  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	    for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    {
//  	  	  //std::cout<<"ASHWIN 3\n"; 
//  	  	  //std::cout<<"ASHWIN"<<k<<"\n"; 
//  	  	  //std::cout<<"ASHWIN"<<step<<"\n"; 
//  	  	  //std::cout<<"ASHWIN"<<l<<"\n"; 
		  Computed_Data.overlap[k*step+l] -= 1;
	    }

	  n = 0;
	  for(k = 0; k < 9; k++)
	  {
		if (duplicate_list[k] == 0)
		{
		  hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	      candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn(MV_y[k], MV_x[k], i, j);
		}
	  }

	  min_array(candidate, n, min_index); 	
	  v_x[i*step+j] = MV_x[hash[min_index]];
	  v_y[i*step+j] = MV_y[hash[min_index]];

	  //Next, add the overlap for the minimum found from min_array() above.
	  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	    for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
		  Computed_Data.overlap[k*step+l] += 1;    	
	}	
//  	std::cout<<"ASHWIN 2\n"; 
  }  
  
  //Top row
  i = start_pos;
  for (j = start_pos + b_size; j < width-(add_width - start_pos + b_size); j+=b_size)
  {    

    //Initalize duplicate list to zero -- no duplicates
	for(k = 0; k < 6; k++)
	{
      duplicate_list[k] = 0;  
	  hash[k] = 0;
	}

	MV_x[0] = v_x[i*step+j];
    MV_y[0] = v_y[i*step+j];
	MV_x[1] = v_x[i*step+(j-b_size)];
	MV_y[1] = v_y[i*step+(j-b_size)];
	MV_x[2] = v_x[(i+b_size)*step+j];
	MV_y[2] = v_y[(i+b_size)*step+j];
	MV_x[3] = v_x[i*step+(j+b_size)];
	MV_y[3] = v_y[i*step+(j+b_size)];
	MV_x[4] = v_x[(i+b_size)*step+(j-b_size)];
	MV_y[4] = v_y[(i+b_size)*step+(j-b_size)];		
	MV_x[5] = v_x[(i+b_size)*step+(j+b_size)];
	MV_y[5] = v_y[(i+b_size)*step+(j+b_size)];	  

	//Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
    for(k = 1; k < 6; k++)
    {
      for(l = 0; l < 6; l++)
	  {
	    if ((l == k) || (duplicate_list[k] == 1))
	      continue;
        else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	    {
	      duplicate_list[l] = 1;
	    } 	    
	  }
    }	  
	
	//Subtract out the overlap for the one already assigned prior to smoothness function.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] -= 1;

	n = 0;
	for(k = 0; k < 6; k++)
	{
	  if (duplicate_list[k] == 0)
	  {
		hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	    candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_top_overlap(MV_y[k], MV_x[k], i, j);
	  }
	}
	
	min_array(candidate, n, min_index); 
	v_x[i*step+j] = MV_x[hash[min_index]];
	v_y[i*step+j] = MV_y[hash[min_index]];

	//Next, add the overlap for the minimum found from min_array() above.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] += 1; 				  	
  }

  //Left column
  j = start_pos;
  for (i = start_pos + b_size; i < height-(add_height - start_pos + b_size); i+=b_size)
  {        
    //Initalize duplicate list to zero -- no duplicates
	for(k = 0; k < 6; k++)
	{
      duplicate_list[k] = 0;  
	  hash[k] = 0;
	}

	MV_x[0] = v_x[i*step+j];
	MV_y[0] = v_y[i*step+j];
	MV_x[1] = v_x[(i-b_size)*step+j];
	MV_y[1] = v_y[(i-b_size)*step+j];
	MV_x[2] = v_x[(i+b_size)*step+j];
	MV_y[2] = v_y[(i+b_size)*step+j];
	MV_x[3] = v_x[i*step+(j+b_size)];
	MV_y[3] = v_y[i*step+(j+b_size)];	 
	MV_x[4] = v_x[(i-b_size)*step+(j+b_size)];
	MV_y[4] = v_y[(i-b_size)*step+(j+b_size)];	
	MV_x[5] = v_x[(i+b_size)*step+(j+b_size)];
	MV_y[5] = v_y[(i+b_size)*step+(j+b_size)];	 
	
	//Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
    for(k = 1; k < 6; k++)
    {
      for(l = 0; l < 6; l++)
	  {
	    if ((l == k) || (duplicate_list[k] == 1))
	      continue;
        else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	    {
	      duplicate_list[l] = 1;
	    } 	    
	  }
    }	  

	//Subtract out the overlap for the one already assigned prior to smoothness function.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] -= 1;
	 
	n = 0;
	for(k = 0; k < 6; k++)
	{
	  if (duplicate_list[k] == 0)
	  {
		hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	    candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_left_overlap(MV_y[k], MV_x[k], i, j);
	  }
	}
	
	min_array(candidate, n, min_index); 
	v_x[i*step+j] = MV_x[hash[min_index]];
	v_y[i*step+j] = MV_y[hash[min_index]];

	//Next, add the overlap for the minimum found from min_array() above.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] += 1;     
  }

  //Right column
  if (((width - add_width) % b_size) == 0)
    j = width - (add_width - start_pos + b_size); 
  else
	j = width - (add_width - start_pos + ((width - add_width) % b_size));

  for (i = start_pos + b_size; i < height-(add_height - start_pos + b_size); i+=b_size)
  {       
    //Initalize duplicate list to zero -- no duplicates
	for(k = 0; k < 6; k++)
	{
      duplicate_list[k] = 0;  
	  hash[k] = 0;
	}

	MV_x[0] = v_x[i*step+j];
	MV_y[0] = v_y[i*step+j];
	MV_x[1] = v_x[(i-b_size)*step+j];
	MV_y[1] = v_y[(i-b_size)*step+j];
	MV_x[2] = v_x[i*step+(j-b_size)];
	MV_y[2] = v_y[i*step+(j-b_size)];
	MV_x[3] = v_x[(i+b_size)*step+j];
	MV_y[3] = v_y[(i+b_size)*step+j];
	MV_x[4] = v_x[(i-b_size)*step+(j-b_size)];
	MV_y[4] = v_y[(i-b_size)*step+(j-b_size)];		 
	MV_x[5] = v_x[(i+b_size)*step+(j-b_size)];
	MV_y[5] = v_y[(i+b_size)*step+(j-b_size)];	

	//Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
    for(k = 1; k < 6; k++)
    {
      for(l = 0; l < 6; l++)
	  {
	    if ((l == k) || (duplicate_list[k] == 1))
	      continue;
        else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	    {
	      duplicate_list[l] = 1;
	    } 	    
	  }
    }	  
	 
	//Subtract out the overlap for the one already assigned prior to smoothness function.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] -= 1;

	n = 0;
	for(k = 0; k < 6; k++)
	{
	  if (duplicate_list[k] == 0)
	  {
		hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	    candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_right_overlap(MV_y[k], MV_x[k], i, j);
	  }
	}
	
	min_array(candidate, n, min_index); 
	v_x[i*step+j] = MV_x[hash[min_index]];
	v_y[i*step+j] = MV_y[hash[min_index]];

	//Next, add the overlap for the minimum found from min_array() above.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] += 1;      
  }

  //Bottom row   
  if (((height - add_height) % b_size) == 0) 
    i = height - (add_height - start_pos + b_size);
  else
	i = height - (add_height - start_pos + ((height - add_height) % b_size));

  for (j = start_pos + b_size; j < width-(add_width - start_pos + b_size); j+=b_size)
  { 
    //Initalize duplicate list to zero -- no duplicates
	for(k = 0; k < 6; k++)
	{
      duplicate_list[k] = 0;  
	  hash[k] = 0;
	}

	MV_x[0] = v_x[i*step+j];
	MV_y[0] = v_y[i*step+j];
	MV_x[1] = v_x[(i-b_size)*step+j];
	MV_y[1] = v_y[(i-b_size)*step+j];
	MV_x[2] = v_x[i*step+(j-b_size)];
	MV_y[2] = v_y[i*step+(j-b_size)];
	MV_x[3] = v_x[i*step+(j+b_size)];
	MV_y[3] = v_y[i*step+(j+b_size)];
	MV_x[4] = v_x[(i-b_size)*step+(j-b_size)];
	MV_y[4] = v_y[(i-b_size)*step+(j-b_size)];	
	MV_x[5] = v_x[(i-b_size)*step+(j+b_size)];
	MV_y[5] = v_y[(i-b_size)*step+(j+b_size)];	

	//Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
    for(k = 1; k < 6; k++)
    {
      for(l = 0; l < 6; l++)
	  {
	    if ((l == k) || (duplicate_list[k] == 1))
	      continue;
        else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	    {
	      duplicate_list[l] = 1;
	    } 	    
	  }
    }	  
	
	//Subtract out the overlap for the one already assigned prior to smoothness.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] -= 1;

	n = 0;
	for(k = 0; k < 6; k++)
	{
	  if (duplicate_list[k] == 0)
	  {
		hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	    candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_bottom_overlap(MV_y[k], MV_x[k], i, j);
	  }
	}
	  	 	  
	min_array(candidate, n, min_index); 
	v_x[i*step+j] = MV_x[hash[min_index]];
	v_y[i*step+j] = MV_y[hash[min_index]];   

	//Next, add the overlap for the minimum found from min_array() above.
	for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	  for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	    Computed_Data.overlap[k*step+l] += 1;
	
  }  

  //CORNERS!

  //Left corner
  i = start_pos;
  j = start_pos;

  //Initalize duplicate list to zero -- no duplicates
  for(k = 0; k < 4; k++)
  {
    duplicate_list[k] = 0;  
	hash[k] = 0;
  }

  MV_x[0] = v_x[i*step+j];
  MV_y[0] = v_y[i*step+j];
  MV_x[1] = v_x[(i+b_size)*step+j];
  MV_y[1] = v_y[(i+b_size)*step+j];	
  MV_x[2] = v_x[i*step+(j+b_size)];
  MV_y[2] = v_y[i*step+(j+b_size)];	     
  MV_x[3] = v_x[(i+b_size)*step+(j+b_size)];
  MV_y[3] = v_y[(i+b_size)*step+(j+b_size)];	 

  //Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
  for(k = 1; k < 4; k++)
  {
    for(l = 0; l < 4; l++)
	{
	  if ((l == k) || (duplicate_list[k] == 1))
	    continue;
      else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	  {
	    duplicate_list[l] = 1;
	  } 	    
	}
  }	  
	 
  //Subtract out the overlap for the one already assigned prior to smoothness.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] -= 1;

  n = 0;
  for(k = 0; k < 4; k++)
  {
	if (duplicate_list[k] == 0)
	{
	  hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	  candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_leftcorn_overlap(MV_y[k], MV_x[k], i, j);
	}
  }
	  	 	  
  min_array(candidate, n, min_index); 
  v_x[i*step+j] = MV_x[hash[min_index]];
  v_y[i*step+j] = MV_y[hash[min_index]];   

  //Next, add the overlap for the minimum found from min_array() above.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] += 1; 
  
  
  //Right corner
  i = start_pos;

  if (((width - add_width) % b_size) == 0)
    j = width - (add_width - start_pos + b_size); 
  else
	j = width - (add_width - start_pos + ((width - add_width) % b_size));
  
  //Initalize duplicate list to zero -- no duplicates
  for(k = 0; k < 4; k++)
  {
    duplicate_list[k] = 0;  
	hash[k] = 0;
  }

  MV_x[0] = v_x[i*step+j];
  MV_y[0] = v_y[i*step+j]; 
  MV_x[1] = v_x[(i+b_size)*step+j];
  MV_y[1] = v_y[(i+b_size)*step+j]; 
  MV_x[2] = v_x[i*step+(j-b_size)];
  MV_y[2] = v_y[i*step+(j-b_size)];    
  MV_x[3] = v_x[(i+b_size)*step+(j-b_size)];
  MV_y[3] = v_y[(i+b_size)*step+(j-b_size)]; 

  //Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
  for(k = 1; k < 4; k++)
  {
    for(l = 0; l < 4; l++)
	{
	  if ((l == k) || (duplicate_list[k] == 1))
	    continue;
      else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	  {
	    duplicate_list[l] = 1;
	  } 	    
	}
  }	  
	 
  //Subtract out the overlap for the one already assigned prior to smoothness.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] -= 1;

  n = 0;
  for(k = 0; k < 4; k++)
  {
	if (duplicate_list[k] == 0)
	{
	  hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	  candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_rightcorn_overlap(MV_y[k], MV_x[k], i, j);
	}
  }
	  	 	  
  min_array(candidate, n, min_index); 
  v_x[i*step+j] = MV_x[hash[min_index]];
  v_y[i*step+j] = MV_y[hash[min_index]];   

  //Next, add the overlap for the minimum found from min_array() above.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] += 1;


  //Bottom left corner
  if (((height - add_height) % b_size) == 0) 
    i = height - (add_height - start_pos + b_size);
  else
	i = height - (add_height - start_pos + ((height - add_height) % b_size));

  j = start_pos;

  //Initalize duplicate list to zero -- no duplicates
  for(k = 0; k < 4; k++)
  {
    duplicate_list[k] = 0;  
	hash[k] = 0;
  }

  MV_x[0] = v_x[i*step+j];
  MV_y[0] = v_y[i*step+j];
  MV_x[1] = v_x[(i-b_size)*step+j];
  MV_y[1] = v_y[(i-b_size)*step+j]; 
  MV_x[2] = v_x[i*step+(j+b_size)];
  MV_y[2] = v_y[i*step+(j+b_size)];    
  MV_x[3] = v_x[(i-b_size)*step+(j+b_size)];
  MV_y[3] = v_y[(i-b_size)*step+(j+b_size)];  

  //Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
  for(k = 1; k < 4; k++)
  {
    for(l = 0; l < 4; l++)
	{
	  if ((l == k) || (duplicate_list[k] == 1))
	    continue;
      else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	  {
	    duplicate_list[l] = 1;
	  } 	    
	}
  }	  

  //Subtract out the overlap for the one already assigned prior to smoothness.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] -= 1;

  n = 0;
  for(k = 0; k < 4; k++)
  {
	if (duplicate_list[k] == 0)
	{
	  hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	  candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_bottomleftcorn_overlap(MV_y[k], MV_x[k], i, j);
	}
  }
	  	 	  
  min_array(candidate, n, min_index); 
  v_x[i*step+j] = MV_x[hash[min_index]];
  v_y[i*step+j] = MV_y[hash[min_index]];   

  //Next, add the overlap for the minimum found from min_array() above.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] += 1;
   

  //Bottom right corner
  if (((height - add_height) % b_size) == 0) 
    i = height - (add_height - start_pos + b_size);
  else
	i = height - (add_height - start_pos + ((height - add_height) % b_size));

  if (((width - add_width) % b_size) == 0)
    j = width - (add_width - start_pos + b_size); 
  else
	j = width - (add_width - start_pos + ((width - add_width) % b_size));

  //Initalize duplicate list to zero -- no duplicates
  for(k = 0; k < 4; k++)
  {
    duplicate_list[k] = 0;  
	hash[k] = 0;
  }

  MV_x[0] = v_x[i*step+j];
  MV_y[0] = v_y[i*step+j];  
  MV_x[1] = v_x[(i-b_size)*step+j];
  MV_y[1] = v_y[(i-b_size)*step+j];
  MV_x[2] = v_x[i*step+(j-b_size)];
  MV_y[2] = v_y[i*step+(j-b_size)]; 
  MV_x[3] = v_x[(i-b_size)*step+(j-b_size)];
  MV_y[3] = v_y[(i-b_size)*step+(j-b_size)];

  //Check for duplicates, a duplicate is assigned a value of '1' in the duplicate list
  for(k = 1; k < 4; k++)
  {
    for(l = 0; l < 4; l++)
	{
	  if ((l == k) || (duplicate_list[k] == 1))
	    continue;
      else if ((MV_x[k] == MV_x[l]) && (MV_y[k] == MV_y[l]))
	  {
	    duplicate_list[l] = 1;
	  } 	    
	}
  }	  
	 
  //Subtract out the overlap for the one already assigned prior to smoothness.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] -= 1;

  n = 0;
  for(k = 0; k < 4; k++)
  {
	if (duplicate_list[k] == 0)
	{
	  hash[n] = k; // this tell us which position of MV_x and MV_y the candidate is stored at.
	  candidate[n++] = (1 + calculate_SAD(i, j, MV_x[k] + j, MV_y[k] + i))*(1 + ((double)get_overlap_volume(MV_x[k] + j, MV_y[k] + i)/bs_squared)) + lambda*cost_fn_bottomrightcorn_overlap(MV_y[k], MV_x[k], i, j);
	}
  }
	  	 	  
  min_array(candidate, n, min_index); 
  v_x[i*step+j] = MV_x[hash[min_index]];
  v_y[i*step+j] = MV_y[hash[min_index]];   

  //Next, add the overlap for the minimum found from min_array() above.
  for(k = v_y[i*step+j] + i; k < v_y[i*step+j] + i + b_size; k++)
	for(l = v_x[i*step+j] + j; l < v_x[i*step+j] + j + b_size; l++)
	  Computed_Data.overlap[k*step+l] += 1;

}
