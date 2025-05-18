class TQ{
	vector<vector<int>> blp ; // binary lifting parent ; 
	vector<int> h ; // height 
	vector<int> d ; 
public:
	TQ(vector<vector<int>> &t){
		int n = t.size() ; 
		blp.resize(n, vector<int>(ceil(log2(n))+1, -1))  ;
		h.resize(n, 0) ;
		d.resize(n, 0) ; 
		
		auto dfs = [&](auto self, int cn , int par)->void{
			if(par!=-1){
				d[cn] = d[par] + 1 ; 
				h[cn] = h[par]+1 ; 
				blp[cn][0] = par ; 
				for( int i=1 ; i<=ceil(log2(n)) ; i++){
					if( blp[ blp[cn][i-1] ][i-1] == -1) break ;
					blp[cn][i] = blp[ blp[cn][i-1] ][i-1] ; 
				}
			}	
			for( auto ch : t[cn] ){
				if(ch==par) continue ; 
				self(self, ch, cn) ;
			}
		};
		dfs(dfs, 0, -1) ;
	}
	TQ(vector<vector<int>> &t , map<pair<int,int>, int> &w){
		int n = t.size() ; 
		blp.resize(n, vector<int>(ceil(log2(n))+1, -1))  ;
		h.resize(n, 0) ;
		d.resize(n, 0) ; 
		
		auto dfs = [&](auto self, int cn , int par)->void{
			if(par!=-1){
				d[cn] = d[par] + w[{cn,par}] ; 
				h[cn] = h[par]+1 ; 
				blp[cn][0] = par ; 
				for( int i=1 ; i<=ceil(log2(n)) ; i++){
					if( blp[ blp[cn][i-1] ][i-1] == -1) break ;
					blp[cn][i] = blp[ blp[cn][i-1] ][i-1] ; 
				}
			}	
			for( auto ch : t[cn] ){
				if(ch==par) continue ; 
				self(self, ch, cn) ;
			}
		};
		dfs(dfs, 0, -1) ;
	}
	
	int ka( int node , int k ){
		for( int i=blp[0].size()-1 ; i>=0 ; i-- ){
			if((k&(1<<i)) == 0) continue ; 
			if( blp[node][i] ==-1 ) return -1 ; 
			node = blp[node][i] ;
		}
		return node ; 
	}
	
	int lca(int u , int v){
		if(h[u] < h[v]){
			v =  ka(v, h[v]-h[u]) ; 
		}
		if(h[u] > h[v]){
			u = ka(u, h[u]-h[v]) ; 
		}
		
		auto pred =[&](int mid)->bool{
			if(ka(u, mid) == ka(v, mid)) return true ; 
			return false ;
		};
		
		int l=-1 , r=h[u] ; 
		while(r-l>1){
			int mid = l + (r-l)/2 ; 
			if(pred(mid)) r = mid ; 
			else l = mid ;
		}
		return ka(u,r) ;
	}
	
	int dist(int u , int v){
		return d[u] + d[v] - (2*d[lca(u,v)]) ;
	}
	
};
