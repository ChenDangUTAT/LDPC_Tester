#include "tanner_graph.h"

typedef unsigned short int model_int;
using std::make_pair;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG_MODEL

//#define DEBUG_TANNER

//#define SHOW_MATRIX

pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> tanner_graph(double r, char type, unsigned short int z) {

	pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> result;

	result.first.clear();

	result.second.clear();

	if (z % 4 != 0 || z > 96 || z < 24) {
		// invalid expansion factor

		return result;

	}

	if (r != 0.5 && r != 0.667 && r != 0.75 && r != 0.8333) {

		// code rate not supported 
		return result;



	}
	else {


		if (r == 0.667 || r == 0.75)
		{
			if (type != 'A'&&type != 'B')
			{
				// code type not supported

				return result;

			}
		}
	
	
	}



// first we grab the compact model 

	vector<vector<pair<unsigned short int, unsigned short int>>> model_matrix;

	const double z0 = 96.0;

	const unsigned short int nb = 24;

	const unsigned short int mb = nb-(model_int)nb*r;

	vector<pair<unsigned short int, unsigned short int>> row;


	if (r == 0.5) {

		model_matrix.reserve(mb);

// first row

// val = {94,73,55,83,7,0} pos = {2,3,9,10,13,14}
		
		model_matrix_row_push_back({ 94,73,55,83,7,0 }, { 2,3,9,10,13,14 }, z, row);

		model_matrix.push_back(row);
	
// second row

// val = {27,22,79,9,12,0,0} pos = {2,6,7,8,12,14,15}

		model_matrix_row_push_back({ 27,22,79,9,12,0,0 }, { 2,6,7,8,12,14,15 }, z, row);

		model_matrix.push_back(row);

// third row

// val = {24,22,81,33,0,0,0} pos = {4,5,6,8,12,15,16}

		model_matrix_row_push_back({ 24,22,81,33,0,0,0 }, { 4,5,6,8,12,15,16 }, z, row);

		model_matrix.push_back(row);

// fourth row

// val = {61,47,65,25,0,0} pos = {1,3,9,10,16,17}

		model_matrix_row_push_back({ 61,47,65,25,0,0 }, { 1,3,9,10,16,17 }, z, row);

		model_matrix.push_back(row);

// fifth row

// val = {39,84,41,72,0,0} pos = {3,7,10,11,17,18}

		model_matrix_row_push_back({ 39,84,41,72,0,0 }, { 3,7,10,11,17,18 }, z, row);

		model_matrix.push_back(row);

// sixth row

// val = {46,40,82,79,0,0,0} pos = {5,6,8,12,13,18,19}

		model_matrix_row_push_back({ 46,40,82,79,0,0,0 }, { 5,6,8,12,13,18,19 }, z, row);

		model_matrix.push_back(row);


// seventh row 


// val = {95,53,14,18,0,0} pos = {3,4,9,10,11,19,20}

		model_matrix_row_push_back({ 95,53,14,18,0,0 }, { 3,4,9,10,11,19,20 }, z, row);

		model_matrix.push_back(row);

// eighth row 

// val = {11,73,2,47,0,0} pos = {2,3,7,10,20,21}

		model_matrix_row_push_back({ 11,73,2,47,0,0 }, { 2,3,7,10,20,21 }, z, row);

		model_matrix.push_back(row);

//ninth row 

// val = {12,83,24,43,51,0,0} pos = {1,5,6,8,12,21,22}

		model_matrix_row_push_back({ 12,83,24,43,51,0,0 }, { 1,5,6,8,12,21,22 }, z, row);

		model_matrix.push_back(row);

// tenth row

// val = {94,59,70,72,0,0} pos = {6,8,11,12,22,23}

		model_matrix_row_push_back({ 94,59,70,72,0,0 }, { 6,8,11,12,22,23 }, z, row);

		model_matrix.push_back(row);

// eleventh row 

// val = {7,65,39,49,0,0} pos = {3,4,9,10,23,24}

		model_matrix_row_push_back({ 7,65,39,49,0,0 }, { 3,4,9,10,23,24 }, z, row);

		model_matrix.push_back(row);

// twelfth row 

// val = {43,66,41,26,7,0}  pos =  {1,6,8,12,13,24}


		model_matrix_row_push_back({ 43,66,41,26,7,0 }, { 1,6,8,12,13,24 }, z, row);

		model_matrix.push_back(row);


}
else if (r == 0.8333) {

	model_matrix.reserve(mb);

	// val = {1,25,55,47,4,91,84,8,86,52,82,33,5,0,36,20,4,77,80,0,}  pos = {1,2,3,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22}
	model_matrix_row_push_back({ 1,25,55,47,4,91,84,8,86,52,82,33,5,0,36,20,4,77,80,0}, { 1,2,3,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22} ,z, row);

	model_matrix.push_back(row);

	// val = {6,36,40,47,12,79,47,41,21,12,71,14,72,0,44,49,0,0,0,0} pos = {2,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23}
	model_matrix_row_push_back({ 1,25,55,47,4,91,84,8,86,52,82,33,5,0,36,20,4,77,80,0 }, { 1,2,3,5,6,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 }, z, row);

	model_matrix.push_back(row);


	// val = {51,81,83,4,67,21,31,24,91,61,81,19,86,78,60,88,67,15,0,0} pos = {1,2,3,4,5,7,9,10,11,12,13,14,15,16,17,18,19,20,23,24}
	model_matrix_row_push_back({ 51,81,83,4,67,21,31,24,91,61,81,9,86,78,60,88,67,15,0,0 }, { 1,2,3,4,5,7,9,10,11,12,13,14,15,16,17,18,19,20,23,24 }, z, row);

	model_matrix.push_back(row);

	// val = {68,-1,50,15,-1,36,13,10,11,20,53,90,29,92,57,30,84,92,11,66,80,-1,-1,0} pos= {1,3,4,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,24}
	model_matrix_row_push_back({ 68,50,15,36,13,10,11,20,53,90,29,92,57,30,84,92,11,66,80,0 }, { 1,3,4,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,24 }, z, row);
	model_matrix.push_back(row);



}

#ifdef DEBUG_MODEL



	for (model_int c = 0; c < mb; c++) {

		model_int counter = 0;

		for (model_int d = 0; d < nb; d++) {

			if (d != (model_matrix[c])[counter].second) {

				cout << " -1 ";

			}
			else {

				cout << " " << std::setfill(' ') << std::setw(2) << model_matrix[c][counter].first; 
				if (counter + 1<model_matrix[c].size())
					counter++;

			}







		}

		cout << endl;
	}

	system("pause");










#endif // DEBUG_MODEL



// other model matrix should come later with the varification of effectiveness of encoding algorithm

result.first.reserve(mb*z);

result.second.reserve(nb*z);

vector<model_int> null_vector;

null_vector.clear();

for (model_int c = 0; c < nb*z; c++) {
	result.second.push_back(null_vector);
}

vector<model_int> check_node;

for (unsigned short int c = 0; c < mb ; c++) {
	for (model_int d = 0; d < z; d++) {

		check_node.clear();

		check_node.reserve(model_matrix[c].size());
	
		for (model_int size = 0; size < model_matrix[c].size(); size++) {
		
			model_int new_value = (model_matrix[c][size].first+d)%z+ model_matrix[c][size].second*z;

			check_node.push_back(new_value);



			result.second[new_value].push_back(c*z + d);
		
		}

		result.first.push_back(check_node);
	
	}
}

#ifdef DEBUG_TANNER

cout << "The check nodes are :" << endl;

for (model_int c = 0; c < mb*z; c++) {
	cout << "node " << c << " is";

	for (model_int d = 0; d < result.first[c].size(); d++) {

		cout << " " << std::setw(4) << std::setfill(' ') << result.first[c][d]<<" ";

		
	
	}
	
	cout << " ; " << endl;


}

//system("pause");





#endif


#ifdef SHOW_MATRIX

for (model_int c = 0; c < mb*z; c++) {
	model_int e = 0;

	for (model_int d = 0; d < result.first[c].size(); d++) {


		for (; e < result.first[c][d]; e++)
		{
			cout << " " << std::setw(2) << std::setfill(' ') << 0 << ",";
		}

		cout << " " << std::setw(2) << std::setfill(' ') << 1 << ",";



	}

	for (; e < mb*z; e++)
	{
		cout << " " << std::setw(2) << std::setfill(' ') << 0 << ((e == mb*z - 1) ? ";\n" : ",");
	}


}









#endif



return result;


































}





void model_matrix_push_back(unsigned short int val, unsigned short int pos, unsigned short int z, vector<pair<unsigned short int, unsigned short int>>& row) {


	pair<unsigned short int, unsigned short int> entry;

	const double z0 = 96;

	entry = make_pair((unsigned short int)floor( val * (z / z0)), pos - 1);

	row.push_back(entry);



}







void model_matrix_row_push_back(vector<model_int> val, vector<model_int> pos, model_int z, vector<pair<unsigned short int, unsigned short int>>& row) {


	row.clear();

// invalid check

	if (val.empty() || pos.empty() || val.size() != pos.size()) {
	
		return;


	}

	model_int size = (model_int)val.size();

	for (model_int c = 0; c < size; c++) {
	
	
		model_matrix_push_back(val[c], pos[c], z, row);
	
	
	}

	return;








}


#define rows result.first
#define columns result.second

pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> easy_tanner_graph(void) {

	pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> result;

	result.first.clear();

	result.second.clear();


	result.first.reserve(3);

	result.second.reserve(6);

	vector<model_int> row;

	vector<model_int> column;

	column.clear();

	column.reserve(6);

	result.second.assign(12,column);

	row.reserve(12);

	result.first.assign(6, row);

// input 72 items....
// row one pos = {1,2,3,6,7,11}

	model_int row0[] = { 1,2,3,6,7,11 };

// row two pos = {1,2,3,4,5,12}
	model_int row1[] = { 1,2,3,4,5,12 };

// row three pos = {6,7,8,10,11,12}

	model_int row2[] = { 6,7,8,10,11,12 };

// row four pos = {1,4,8,9,10,12}

	model_int row3[] = { 1,4,8,9,10,12 };

// row five pos = {2,4,5,7,8,9}

	model_int row4[] = { 2,4,5,7,8,9 };

// row six pos = {3,5,6,9,10,11}

	model_int row5[] = { 3,5,6,9,10,11 };

	for (model_int row_counter = 0; row_counter < 6; row_counter++) {

		if (row_counter == 0) {

			rows[row_counter].assign(row0,row0+6);

		}

		if (row_counter == 1) {

			rows[row_counter].assign(row1, row1 + 6);


		}

		if (row_counter == 2) {
		
			rows[row_counter].assign(row2, row2 + 6);
		
		
		}

		if (row_counter == 3) {
			rows[row_counter].assign(row3, row3 + 6);
		
		}

		if (row_counter == 4) {

			rows[row_counter].assign(row4, row4 + 6);
		}

		if (row_counter == 5) {

			rows[row_counter].assign(row5, row5 + 6);
		
		}


		for (model_int c = 0; c < rows[row_counter].size(); c++) {

			rows[row_counter][c]--;
		
			columns[rows[row_counter][c]].push_back(row_counter);
		
		}



	}



#ifdef DEBUG_TANNER

	cout << "The check nodes are :" << endl;

	for (model_int c = 0; c < 6; c++) {
		cout << "node " << c << " is";

		for (model_int d = 0; d < result.first[c].size(); d++) {

			cout << " " << std::setw(4) << std::setfill(' ') << result.first[c][d] << " ";



		}

		cout << endl;


	}

	system("pause");





#endif

	return result;




















}
