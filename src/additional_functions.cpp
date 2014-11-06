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

