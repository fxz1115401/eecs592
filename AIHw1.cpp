#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <vector>


using namespace std;

struct node
{
  char contains;
  node *north;
  node *west;
  node *east;
  node *south;
  int row;
  int col;
  vector<char> path;
};

bool added(int** record,int row, int col ){
	if (record[row][col]==1)
		return true;
	else
		return false;

}

void find_frontier(int** record,char** map,node* now, stack<node*>& frontier,int map_row, int map_col)
{


     	if(now->row==map_row){
     		now->south=NULL;
     	}
     	else{
     		now->south=new node();
     		now->south->contains=map[now->row+1][now->col];
     		now->south->row=now->row+1;
     		now->south->col=now->col;
     		if (now->south->contains!='X'&&now->south->contains!='O'&&record[now->south->row][now->south->col]==0)
     		{frontier.push(now->south);
     		record[now->south->row][now->south->col]=1;
     		now->south->path=now->path;
     		now->south->path.push_back('S');
     		}
     	}


     	if(now->col==map_col){
     	     		now->east=NULL;
     	     	}
     	     	else{
     	     		now->east=new node();
     	     		now->east->contains=map[now->row][now->col+1];
     	     		now->east->row=now->row;
     	     		now->east->col=now->col+1;
     	     		if (now->east->contains!='X'&&now->east->contains!='O'&&record[now->east->row][now->east->col]==0)
     	     		{
     	     			frontier.push(now->east);
     	        		record[now->east->row][now->east->col]=1;
     	        		now->east->path=now->path;
     	        		now->east->path.push_back('E');
     	     		}
                }


     	if(now->col==0){
     	     	     		now->west=NULL;
     	     	     	}
     	     	     	else{
     	     	     	now->west=new node();
     	     	        now->west->contains=map[now->row][now->col-1];
     	     	        now->west->row=now->row;
     	     	        now->west->col=now->col-1;
     	     	     	if (now->west->contains!='X'&&now->west->contains!='O'&&record[now->west->row][now->west->col]==0)
     	     	     	{frontier.push(now->west);
     	        		record[now->west->row][now->west->col]=1;
     	        		now->west->path=now->path;
     	        		now->west->path.push_back('W');
     	     	     	}
     	     	     	}


     	if(now->row==0){
     	     		now->north=NULL;
     	     	}
     	     	else{
	     	        now->north=new node();
     	     		now->north->contains=map[now->row-1][now->col];
     	     		now->north->row=now->row-1;
     	     		now->north->col=now->col;
     	     		if (now->north->contains!='X'&&now->north->contains!='O'&&record[now->north->row][now->north->col]==0)
     	     		{frontier.push(now->north);
     	     		record[now->north->row][now->north->col]=1;
     	     		now->north->path=now->path;
     	     		now->north->path.push_back('N');
     	     		}
     	     	}

}

vector<char> depth_search(char** map,int& num_nodes,int S_row,int S_col,int map_row,int map_col)
{
	int** record = new int*[map_row];
		for(int i = 0; i < map_row; ++i)
			record[i] = new int[map_col];
	        for(int i=0;i<map_row;i++){
	        	for(int j=0;j<map_col;j++){
	        		record[i][j]=0;
	        	}
	        }
    stack<node*> frontier;
	vector<char> path;
	node* start=new node();
	start->contains=map[S_row][S_col];
    start->row=S_row;
    start->col=S_col;
    record[S_row][S_col]=1;

    find_frontier(record,map,start, frontier, map_row,  map_col);
    //frontier.pop();

    bool stop=false;
    node* now=start;
    int i=0;
    while(stop==false){
    	i++;


    	if (frontier.empty())
    	{
    		cout<<"OH NO";
    		return path;
    	}


    	if (now->contains=='G')
    	{
             cout<<"Yeah";
             cout<<num_nodes;

             for (int i = 0; i < map_row ; ++i){
    	    delete [] record[i];
    	}
    	delete[] record;
  	         return now->path;
    	}


    	now=frontier.top();

    	frontier.pop();
     	find_frontier(record,map,now, frontier, map_row,  map_col);
    	num_nodes++;
    }


    return path;
};


int main() {

	/******input the txt file as a 2 d char array********/

	int rows, columns;
	int S_row,S_col;
	int num_nodes;
	num_nodes=1;
	//row starting from 0 and column starting from 0
	ifstream ifs ("test_map1.txt", std::ifstream::in);

	ifs>>rows;
	ifs>>columns;
	columns=columns+1;//one extra column for the char newline
	char** map = new char*[rows];
	for(int i = 0; i < rows; ++i)
		map[i] = new char[columns];

		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++ ){
			    map[i][j] = ifs.get();
			    if (map[i][j]=='S')
			    {
			    	S_row=i;S_col=j-1;

			    }
			}
			//elminate the first column of /n
			for(int j=0;j<columns;j++ ){
						    map[i][j] =  map[i][j+1];
						}
		}
	ifs.close();
	columns=columns-1;

	/*********Depth first search**********/
	vector<char> path=depth_search(map,num_nodes,S_row,S_col,rows,columns);
	for (vector<char>::const_iterator i = path.begin(); i != path.end(); ++i)
	    cout << *i;
	/****delete the dynamic variables****/
	for (int i = 0; i < rows ; ++i){
	    delete [] map[i];
	}
	delete[] map;
	cout<<"program finish";
	return 0;
}
