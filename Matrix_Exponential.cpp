int mod = 1e9 + 7 ; 
vector<vector<int>> matrix_mul(vector<vector<int>> &m1 , vector<vector<int>> &m2){
	
	int row1 = m1.size() ; 
	int col1 = m1[0].size() ; 
	int col2 = m2[0].size() ; 
	
	vector<vector<int>> matrix(row1 , vector<int>(col2,0)) ; 
	for( int i=0 ; i<row1 ; i++ ){
		for( int j=0 ; j<col2 ; j++ ){
			for( int k=0 ; k<col1 ; k++ ){
				matrix[i][j] += (m1[i][k] * m2[k][j]) ; 
				matrix[i][j] %= mod ; 
			}
			
		}
	} 
	
	return matrix ; 
}

vector<vector<int>> matrix_expo(vector<vector<int>> matrix , int pow){
	// matrix must be square matrix to make exponential 
	int n = matrix.size() ; 
	vector<vector<int>> fm(n , vector<int>(n,0)) ;
	for( int i=0 ; i<n ; i++ ) fm[i][i] = 1 ; 
	
	while(pow){
		if(pow&1){
			fm = matrix_mul(fm , matrix) ;
		}
		pow >>= 1 ; 
		matrix = matrix_mul(matrix , matrix) ; 
	} 
	
	return fm  ;
}
