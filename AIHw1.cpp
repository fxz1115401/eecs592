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
  int path_length;
  int path_cost;
};

bool added(int** record,int row, int col ){
	if (record[row][col]==1)
		return true;
	else
		return false;

}

void printInfo(node* finish,int num_nodes){
	cout<<"Path:"<<endl;
	for (vector<char>::const_iterator i = finish->path.begin(); i != finish->path.end(); ++i)
		    cout << *i;
	cout<<endl<<'\n';
    cout<<"Path Length: "<<finish->path_length<<endl;
    cout<<"Path Cost: "<<finish->path_cost<<endl;
    cout<<"# Nodes Examined: "<<num_nodes<<endl;
}

void find_frontier_s(int** record,char** map,node* now, stack<node*>& frontier,int map_row, int map_col)
{


     	if(now->row==map_row){
     		now->south=NULL;
     	}
     	else{
     		now->south=new node();
     		node* temp=now->south;
     		temp->contains=map[now->row+1][now->col];
     		temp->row=now->row+1;
     		temp->col=now->col;
     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
     		{frontier.push(temp);
     		record[temp->row][temp->col]=1;
     		temp->path=now->path;
     		temp->path.push_back('S');
     		temp->path_length=now->path_length+1;
     		if(now->contains==' ')
     			temp->path_cost=now->path_cost+1;
     		else if (now->contains=='*')
     			temp->path_cost=now->path_cost+3;
     		}
     	}


     	if(now->col==map_col){
     	     		now->east=NULL;
     	     	}
     	     	else{
     	     		now->east=new node();
     	     		node* temp=now->east;
     	     		temp->contains=map[now->row][now->col+1];
     	     		temp->row=now->row;
     	     		temp->col=now->col+1;
     	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
     	     		{frontier.push(temp);
     	     		record[temp->row][temp->col]=1;
     	     		temp->path=now->path;
     	     		temp->path.push_back('E');
     	     		temp->path_length=now->path_length+1;
     	     		if(now->contains==' ')
     	     			temp->path_cost=now->path_cost+1;
     	     		else if (now->contains=='*')
     	     			temp->path_cost=now->path_cost+3;
     	     		}
     	     	}


     	if(now->col==0){
     	     	     		now->west=NULL;
     	     	     	}
     	     	     	else{
     	     	     		now->west=new node();
     	     	     		node* temp=now->west;
     	     	     		temp->contains=map[now->row][now->col-1];
     	     	     		temp->row=now->row;
     	     	     		temp->col=now->col-1;
     	     	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
     	     	     		{frontier.push(temp);
     	     	     		record[temp->row][temp->col]=1;
     	     	     		temp->path=now->path;
     	     	     		temp->path.push_back('W');
     	     	     		temp->path_length=now->path_length+1;
     	     	     		if(now->contains==' ')
     	     	     			temp->path_cost=now->path_cost+1;
     	     	     		else if (now->contains=='*')
     	     	     			temp->path_cost=now->path_cost+3;
     	     	     		}
     	     	     	}


     	if(now->row==0){
     	     		now->north=NULL;
     	     	}
    	else{
         	     	     		now->north=new node();
         	     	     		node* temp=now->north;
         	     	     		temp->contains=map[now->row-1][now->col];
         	     	     		temp->row=now->row-1;
         	     	     		temp->col=now->col;
         	     	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
         	     	     		{frontier.push(temp);
         	     	     		record[temp->row][temp->col]=1;
         	     	     		temp->path=now->path;
         	     	     		temp->path.push_back('N');
         	     	     		temp->path_length=now->path_length+1;
         	     	     		if(now->contains==' ')
         	     	     			temp->path_cost=now->path_cost+1;
         	     	     		else if (now->contains=='*')
         	     	     			temp->path_cost=now->path_cost+3;
         	     	     		}
         	     	     	}


}

void find_frontier_q(int** record,char** map,node* now, queue<node*>& frontier,int map_row, int map_col)
{

	if(now->row==0){
	     	     		now->north=NULL;
	     	     	}
	    	else{
	         	     	     		now->north=new node();
	         	     	     		node* temp=now->north;
	         	     	     		temp->contains=map[now->row-1][now->col];
	         	     	     		temp->row=now->row-1;
	         	     	     		temp->col=now->col;
	         	     	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
	         	     	     		{frontier.push(temp);
	         	     	     		record[temp->row][temp->col]=1;
	         	     	     		temp->path=now->path;
	         	     	     		temp->path.push_back('N');
	         	     	     		temp->path_length=now->path_length+1;
	         	     	     		if(now->contains==' ')
	         	     	     			temp->path_cost=now->path_cost+1;
	         	     	     		else if (now->contains=='*')
	         	     	     			temp->path_cost=now->path_cost+3;
	         	     	     		}
	         	     	     	}

 	if(now->col==0){
 	     	     		now->west=NULL;
 	     	     	}
 	     	     	else{
 	     	     		now->west=new node();
 	     	     		node* temp=now->west;
 	     	     		temp->contains=map[now->row][now->col-1];
 	     	     		temp->row=now->row;
 	     	     		temp->col=now->col-1;
 	     	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
 	     	     		{frontier.push(temp);
 	     	     		record[temp->row][temp->col]=1;
 	     	     		temp->path=now->path;
 	     	     		temp->path.push_back('W');
 	     	     		temp->path_length=now->path_length+1;
 	     	     		if(now->contains==' ')
 	     	     			temp->path_cost=now->path_cost+1;
 	     	     		else if (now->contains=='*')
 	     	     			temp->path_cost=now->path_cost+3;
 	     	     		}
 	     	     	}


 	if(now->col==map_col){
 	     		now->east=NULL;
 	     	}
 	     	else{
 	     		now->east=new node();
 	     		node* temp=now->east;
 	     		temp->contains=map[now->row][now->col+1];
 	     		temp->row=now->row;
 	     		temp->col=now->col+1;
 	     		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
 	     		{frontier.push(temp);
 	     		record[temp->row][temp->col]=1;
 	     		temp->path=now->path;
 	     		temp->path.push_back('E');
 	     		temp->path_length=now->path_length+1;
 	     		if(now->contains==' ')
 	     			temp->path_cost=now->path_cost+1;
 	     		else if (now->contains=='*')
 	     			temp->path_cost=now->path_cost+3;
 	     		}
 	     	}



 	if(now->row==map_row){
 		now->south=NULL;
 	}
 	else{
 		now->south=new node();
 		node* temp=now->south;
 		temp->contains=map[now->row+1][now->col];
 		temp->row=now->row+1;
 		temp->col=now->col;
 		if (temp->contains!='X'&&temp->contains!='O'&&record[temp->row][temp->col]==0)
 		{frontier.push(temp);
 		record[temp->row][temp->col]=1;
 		temp->path=now->path;
 		temp->path.push_back('S');
 		temp->path_length=now->path_length+1;
 		if(now->contains==' ')
 			temp->path_cost=now->path_cost+1;
 		else if (now->contains=='*')
 			temp->path_cost=now->path_cost+3;
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
	vector<char> path;
	node* start=new node();
	start->contains=map[S_row][S_col];
    start->row=S_row;
    start->col=S_col;
    start->path_cost=1;
    start->path_length=0;
    record[S_row][S_col]=1;
    stack<node*> frontier;

    find_frontier_s(record,map,start, frontier, map_row,  map_col);
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
             cout<<"Yeah"<<endl;

             printInfo(now,num_nodes);
             for (int i = 0; i < map_row ; ++i){
    	    delete [] record[i];
    	}
    	delete[] record;
  	         return now->path;
    	}


    	now=frontier.top();

    	frontier.pop();
     	find_frontier_s(record,map,now, frontier, map_row,  map_col);
    	num_nodes++;
    }


    return path;
};


vector<char> breath_search(char** map,int& num_nodes,int S_row,int S_col,int map_row,int map_col)
{
	int** record = new int*[map_row];
		for(int i = 0; i < map_row; ++i)
			record[i] = new int[map_col];
	        for(int i=0;i<map_row;i++){
	        	for(int j=0;j<map_col;j++){
	        		record[i][j]=0;
	        	}
	        }
	vector<char> path;
	node* start=new node();
	start->contains=map[S_row][S_col];
    start->row=S_row;
    start->col=S_col;
    record[S_row][S_col]=1;
    start->path_cost=1;
    start->path_length=0;
    queue<node*> frontier;

    find_frontier_q(record,map,start, frontier, map_row,  map_col);
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
    		cout<<"Yeah"<<endl;
    		printInfo(now,num_nodes);

             for (int i = 0; i < map_row ; ++i){
    	    delete [] record[i];
    	}
    	delete[] record;
  	         return now->path;
    	}


    	now=frontier.front();

    	frontier.pop();
     	find_frontier_q(record,map,now, frontier, map_row,  map_col);
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
	vector<char> path_depth=depth_search(map,num_nodes,S_row,S_col,rows,columns);
	/*********DBreath first search**********/
	num_nodes=1;
	vector<char> path_breath=breath_search(map,num_nodes,S_row,S_col,rows,columns);

	/****delete the dynamic variables****/
	for (int i = 0; i < rows ; ++i){
	    delete [] map[i];
	}
	delete[] map;
	cout<<"program finish";
	return 0;
}
