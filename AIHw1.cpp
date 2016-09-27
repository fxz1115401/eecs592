#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

struct node {
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
	int health;
	int distance;
};

bool added(int** record, int row, int col) {
	if (record[row][col] == 1)
		return true;
	else
		return false;

}

void printInfo(node* finish, int num_nodes) {
	cout << "Path:" << endl;
	for (vector<char>::const_iterator i = finish->path.begin();
			i != finish->path.end(); ++i)
		cout << *i;
	cout << endl << '\n';
	cout << "Path Length: " << finish->path_length << endl;
	cout << "Path Cost: " << finish->path_cost << endl;
	cout << "# Nodes Examined: " << num_nodes << endl;
}

void find_frontier_s(int** record, char** map, node* now,
		stack<node*>& frontier, int map_row, int map_col) {

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('S');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {
		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('E');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('W');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('N');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

}

vector<char> depth_search(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int& G_row, int& G_col) {
	int** record = new int*[map_row];
	for (int i = 0; i < map_row; ++i)
		record[i] = new int[map_col];
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			record[i][j] = 0;
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	start->path_cost = 1;
	start->path_length = 0;
	record[S_row][S_col] = 1;
	stack<node*> frontier;

	find_frontier_s(record, map, start, frontier, map_row, map_col);
	//frontier.pop();

	bool stop = false;
	node* now = start;
	int i = 0;
	while (stop == false) {
		i++;

		if (frontier.empty()) {
			cout << "OH NO";
			return path;
		}

		if (now->contains == 'G') {
			cout << '\n';
			cout << "Depth First Search: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);
			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];
			}
			delete[] record;
			return now->path;
		}

		now = frontier.top();

		frontier.pop();
		find_frontier_s(record, map, now, frontier, map_row, map_col);
		num_nodes++;
	}

	return path;
}
;

void find_frontier_q(int** record, char** map, node* now,
		queue<node*>& frontier, int map_row, int map_col) {

	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('N');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;

		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('W');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {
		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('E');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('S');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}
}

vector<char> breath_search(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int& G_row, int& G_col) {
	int** record = new int*[map_row];
	for (int i = 0; i < map_row; ++i)
		record[i] = new int[map_col];
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			record[i][j] = 0;
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	queue<node*> frontier;

	find_frontier_q(record, map, start, frontier, map_row, map_col);
	//frontier.pop();

	bool stop = false;
	node* now = start;
	int i = 0;
	while (stop == false) {
		i++;

		if (frontier.empty()) {
			cout << "OH NO";
			return path;
		}

		if (now->contains == 'G') {
			cout << '\n';
			cout << "Breath First Search: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];
			}
			delete[] record;
			return now->path;
		}

		now = frontier.front();

		frontier.pop();
		find_frontier_q(record, map, now, frontier, map_row, map_col);
		num_nodes++;
	}

	return path;
}
;

void find_frontier_v(int** record, char** map, node* now,
		vector<node*>& frontier, int map_row, int map_col) {
	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push_back(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('W');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}
	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push_back(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('N');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {
		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push_back(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('E');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O'
				&& record[temp->row][temp->col] == 0) {
			frontier.push_back(temp);
			record[temp->row][temp->col] = 1;
			temp->path = now->path;
			temp->path.push_back('S');
			temp->path_length = now->path_length + 1;
			if (now->contains == ' ')
				temp->path_cost = now->path_cost + 1;
			else if (now->contains == '*')
				temp->path_cost = now->path_cost + 3;
			else
				temp->path_cost = now->path_cost;
		}
	}
}

int minimum_cost(vector<node*> frontier) {
	int min_cost = frontier[0]->path_cost;
	int min_index = 0;
	int min_index_row = frontier[0]->row;
	int min_index_col = frontier[0]->col;
	for (int i = 0; i < frontier.size(); i++) {
		if (frontier[i]->path_cost < min_cost) {
			min_cost = frontier[i]->path_cost;
			min_index = i;
			min_index_row = frontier[i]->row;
			min_index_col = frontier[i]->col;

		}

		else if (frontier[i]->path_cost == min_cost) {
			if (frontier[i]->row < min_index_row) {
				min_cost = frontier[i]->path_cost;
				min_index = i;
				min_index_row = frontier[i]->row;
				min_index_col = frontier[i]->col;
			} else if (frontier[i]->row == min_index_row) {
				if (frontier[i]->col < min_index_col) {
					min_cost = frontier[i]->path_cost;
					min_index = i;
					min_index_row = frontier[i]->row;
					min_index_col = frontier[i]->col;
				}
			}
		}
	}
	return min_index;

}

vector<char> uniform_search(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int& G_row, int& G_col) {

	int** record = new int*[map_row];
	for (int i = 0; i < map_row; ++i)
		record[i] = new int[map_col];
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			record[i][j] = 0;
		}
	}

	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	vector<node*> frontier;

	find_frontier_v(record, map, start, frontier, map_row, map_col);

	bool stop = false;
	node* now = start;
	int i = 0;
	while (stop == false) {
		i++;

		if (frontier.empty()) {
			cout << "OH NO";
			return path;
		}

		if (now->contains == 'G') {
			cout << '\n';
			cout << "Uniform Cost Search: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];
			}
			delete[] record;
			return now->path;
		}

		int min = minimum_cost(frontier);
		now = frontier[min];
		frontier.erase(frontier.begin() + min);
		find_frontier_v(record, map, now, frontier, map_row, map_col);
		num_nodes++;
	}

	return path;
}
;
//TODO: Solve the health problem
int manhattan(node* now, int G_row, int G_col) {

	int distance = abs(G_col - now->col) + abs(G_row - now->row);
	return distance;
}

int mover_horizon(node* now, int G_row, int G_col) {

	int distance = abs(G_col - now->col) + 1 / 4 * abs(G_row - now->row);
	return distance;
}

int zero_h(node* now, int G_row, int G_col) {

	return 0;
}

int damage(char** map, int row, int col) {
	int number_tower = 0;

	if (map[row - 1][col] == 'O')
		number_tower++;
	if (map[row + 1][col] == 'O')
		number_tower++;
	if (map[row][col - 1] == 'O')
		number_tower++;
	if (map[row][col + 1] == 'O')
		number_tower++;
	if (map[row][col] == '*')
		return 3 * number_tower;
	else
		return number_tower;
}

int minimum_m_distance(vector<node*> frontier) {
	int min_dist = frontier[0]->distance;
	int min_index = 0;
	int min_index_row = frontier[0]->row;
	int min_index_col = frontier[0]->col;
	int min_index_health = frontier[0]->health;
	for (int i = 0; i < frontier.size(); i++) {
		if (frontier[i]->distance < min_dist) {
			min_dist = frontier[i]->distance;
			min_index = i;
			min_index_row = frontier[i]->row;
			min_index_col = frontier[i]->col;
			min_index_health = frontier[i]->health;
		}

		else if (frontier[i]->distance == min_dist) {
			if (frontier[i]->row < min_index_row) {
				min_dist = frontier[i]->distance;
				min_index = i;
				min_index_row = frontier[i]->row;
				min_index_col = frontier[i]->col;
				min_index_health = frontier[i]->health;

			} else if (frontier[i]->row == min_index_row) {
				if (frontier[i]->col < min_index_col) {
					min_dist = frontier[i]->distance;
					min_index = i;
					min_index_row = frontier[i]->row;
					min_index_col = frontier[i]->col;
					min_index_health = frontier[i]->health;

				}

				else if (frontier[i]->col == min_index_col) {
					if (frontier[i]->health < min_index_health) {
						min_dist = frontier[i]->distance;
						min_index = i;
						min_index_row = frontier[i]->row;
						min_index_col = frontier[i]->col;
						min_index_health = frontier[i]->health;
					}
				}
			}
		}
	}
	return min_index;

}

void find_frontier_h(int*** record, char** map, node* now,
		vector<node*>& frontier, int map_row, int map_col, int G_row,
		int G_col) {

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = manhattan(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('S');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {

		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = manhattan(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('E');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = manhattan(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('W');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}
	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {

				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = manhattan(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('N');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

}

void find_frontier_h_move_h(int*** record, char** map, node* now,
		vector<node*>& frontier, int map_row, int map_col, int G_row,
		int G_col) {

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = mover_horizon(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('S');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {

		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = mover_horizon(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('E');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = mover_horizon(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('W');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}
	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {

				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = mover_horizon(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('N');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

}



void find_frontier_0(int*** record, char** map, node* now,
		vector<node*>& frontier, int map_row, int map_col, int G_row,
		int G_col) {

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = zero_h(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('S');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {

		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = zero_h(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('E');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = zero_h(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('W');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}
	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {

				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = zero_h(temp, G_row, G_col);
				temp->path = now->path;
				temp->path.push_back('N');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

}


vector<char> greedy(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int G_row, int G_col) {
	int*** record = new int**[map_row];
	for (int i = 0; i < map_row; ++i) {
		record[i] = new int*[map_col];
		for (int j = 0; j < map_col; j++) {
			record[i][j] = new int[5];
		}
	}

	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			for (int k = 0; k < 5; k++) {
				record[i][j][k] = 0;
			}
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col][4] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	start->health = 5;
	start->distance = manhattan(start, G_row, G_col);
	vector<node*> frontier;
	find_frontier_h(record, map, start, frontier, map_row, map_col, G_row,
			G_col);

	bool stop = false;
	node* now = start;

	while (stop == false) {

		//cout << "Row: " << now->row + 1 << " Col: " << now->col << " Dist: "
		//<< now->distance << " Heath: " << now->health << endl;

		if (frontier.empty()) {
			cout << "OH NO!!!!!!!!!!!!!!!!!";
			vector<char> a;
			return a;
		}
		if (now->contains == 'G') {
			cout << '\n';
			cout << "Greedy  Search: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];

			}

			delete[] record;
			return now->path;
		}

		int min = minimum_m_distance(frontier);
		now = frontier[min];

		frontier.erase(frontier.begin() + min);
		find_frontier_h(record, map, now, frontier, map_row, map_col, G_row,
				G_col);
		num_nodes++;
	}

	return path;
}

int minimum_a_distance(vector<node*> frontier) {
	int min_dist = frontier[0]->distance + frontier[0]->path_cost;
	int min_index = 0;
	int min_index_row = frontier[0]->row;
	int min_index_col = frontier[0]->col;
	int min_index_health = frontier[0]->health;
	for (int i = 0; i < frontier.size(); i++) {
		if (frontier[i]->distance + frontier[i]->path_cost < min_dist) {
			min_dist = frontier[i]->distance + frontier[i]->path_cost;
			min_index = i;
			min_index_row = frontier[i]->row;
			min_index_col = frontier[i]->col;
			min_index_health = frontier[i]->health;
		}

		else if (frontier[i]->distance + frontier[i]->path_cost == min_dist) {
			if (frontier[i]->row < min_index_row) {
				min_dist = frontier[i]->distance + frontier[i]->path_cost;
				min_index = i;
				min_index_row = frontier[i]->row;
				min_index_col = frontier[i]->col;
				min_index_health = frontier[i]->health;

			} else if (frontier[i]->row == min_index_row) {
				if (frontier[i]->col < min_index_col) {
					min_dist = frontier[i]->distance + frontier[i]->path_cost;
					min_index = i;
					min_index_row = frontier[i]->row;
					min_index_col = frontier[i]->col;
					min_index_health = frontier[i]->health;

				}

				else if (frontier[i]->col == min_index_col) {
					if (frontier[i]->health < min_index_health) {
						min_dist = frontier[i]->distance
								+ frontier[i]->path_cost;
						min_index = i;
						min_index_row = frontier[i]->row;
						min_index_col = frontier[i]->col;
						min_index_health = frontier[i]->health;
					}
				}
			}
		}
	}
	return min_index;

}

vector<char> a_search(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int G_row, int G_col) {
	int*** record = new int**[map_row];
	for (int i = 0; i < map_row; ++i) {
		record[i] = new int*[map_col];
		for (int j = 0; j < map_col; j++) {
			record[i][j] = new int[5];
		}
	}

	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			for (int k = 0; k < 5; k++) {
				record[i][j][k] = 0;
			}
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col][4] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	start->health = 5;
	start->distance = manhattan(start, G_row, G_col);
	vector<node*> frontier;
	find_frontier_h(record, map, start, frontier, map_row, map_col, G_row,
			G_col);

	bool stop = false;
	node* now = start;

	while (stop == false) {

		//cout << "Row: " << now->row + 1 << " Col: " << now->col << " Dist: "
		//<< now->distance << " Heath: " << now->health << endl;

		if (frontier.empty()) {
			cout << "OH NO!!!!!!!!!!!!!!!!!";
			vector<char> a;
			return a;
		}
		if (now->contains == 'G') {
			cout << '\n';
			cout << "A*  Search: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];

			}

			delete[] record;
			return now->path;
		}

		int min = minimum_a_distance(frontier);
		now = frontier[min];
		cout << now->distance << " ";

		frontier.erase(frontier.begin() + min);
		find_frontier_h(record, map, now, frontier, map_row, map_col, G_row,
				G_col);
		num_nodes++;
	}

	return path;
}


vector<char> a_search_1(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int G_row, int G_col) {
	int*** record = new int**[map_row];
	for (int i = 0; i < map_row; ++i) {
		record[i] = new int*[map_col];
		for (int j = 0; j < map_col; j++) {
			record[i][j] = new int[5];
		}
	}

	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			for (int k = 0; k < 5; k++) {
				record[i][j][k] = 0;
			}
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col][4] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	start->health = 5;
	start->distance = zero_h(start, G_row, G_col);
	vector<node*> frontier;
	find_frontier_0(record, map, start, frontier, map_row, map_col, G_row,
			G_col);

	bool stop = false;
	node* now = start;

	while (stop == false) {

		//cout << "Row: " << now->row + 1 << " Col: " << now->col << " Dist: "
		//<< now->distance << " Heath: " << now->health << endl;

		if (frontier.empty()) {
			cout << "OH NO!!!!!!!!!!!!!!!!!";
			vector<char> a;
			return a;
		}
		if (now->contains == 'G') {
			cout << '\n';
			cout << "Zero : " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];

			}

			delete[] record;
			return now->path;
		}

		int min = minimum_a_distance(frontier);
		now = frontier[min];

		frontier.erase(frontier.begin() + min);
		find_frontier_0(record, map, now, frontier, map_row, map_col, G_row,
				G_col);
		num_nodes++;
	}

	return path;
}

vector<char> a_search_3(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int G_row, int G_col) {
	int*** record = new int**[map_row];
	for (int i = 0; i < map_row; ++i) {
		record[i] = new int*[map_col];
		for (int j = 0; j < map_col; j++) {
			record[i][j] = new int[5];
		}
	}

	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			for (int k = 0; k < 5; k++) {
				record[i][j][k] = 0;
			}
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col][4] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	start->health = 5;
	start->distance = mover_horizon(start, G_row, G_col);
	vector<node*> frontier;
	find_frontier_h_move_h(record, map, start, frontier, map_row, map_col, G_row,
			G_col);

	bool stop = false;
	node* now = start;

	while (stop == false) {

		//cout << "Row: " << now->row + 1 << " Col: " << now->col << " Dist: "
		//<< now->distance << " Heath: " << now->health << endl;

		if (frontier.empty()) {
			cout << "OH NO!!!!!!!!!!!!!!!!!";
			vector<char> a;
			return a;
		}
		if (now->contains == 'G') {
			cout << '\n';
			cout << "Move Horizontally: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];

			}

			delete[] record;
			return now->path;
		}

		int min = minimum_a_distance(frontier);
		now = frontier[min];

		frontier.erase(frontier.begin() + min);
		find_frontier_h_move_h(record, map, now, frontier, map_row, map_col, G_row,
				G_col);
		num_nodes++;
	}

	return path;
}


int wall(char** map,node* now, int G_row, int G_col,int map_row,int map_col) {
	int distance=0;
    if ((map[now->row][now->col+1]=='X'||map[now->row][now->col+1]=='O')&&now->col+1!=map_col-1)
    {
    	int north=-1;
    	int south=-1;
    	for (int i=now->row;i>=0;i--){
    		if (map[now->row][now->col+1]!='X'&&map[now->row][now->col+1]!='O'){
    			north=i;
    			break;
    		}
    	}
    	for (int i=now->row;i<map_row;i++){
    	    		if (map[now->row][now->col+1]!='X'&&map[now->row][now->col+1]!='O'){
    	    			south=i;
    	    			break;
    	    		}
    	    	}
    	if (north!=-1&&south!=-1){
    	int dis_n=now->row-north+abs(G_col - now->col) + abs(G_row - north);
    	int dis_s=now->row-south+abs(G_col - now->col) + abs(G_row - south);
    	distance=(dis_n < dis_s) ? dis_n : dis_s;}
    	else if (north!=-1&&south==-1){
        	distance=now->row-north+abs(G_col - now->col) + abs(G_row - north);

    	}
    	else if (north==-1&&south!=-1){
    	        	distance=now->row-south+abs(G_col - now->col) + abs(G_row - south);

    	    	}
    	else{
    		distance=abs(G_col - now->col) + abs(G_row - now->row);
    	}
    }
    else
    {
    	return 10*(map_row+map_col);
    }



    return distance;
}

void find_frontier_wall(int*** record, char** map, node* now,
		vector<node*>& frontier, int map_row, int map_col, int G_row,
		int G_col) {

	if (now->row == map_row) {
		now->south = NULL;
	} else {
		now->south = new node();
		node* temp = now->south;
		temp->contains = map[now->row + 1][now->col];
		temp->row = now->row + 1;
		temp->col = now->col;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = wall(map,temp, G_row, G_col,map_row,map_col);
				temp->path = now->path;
				temp->path.push_back('S');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == map_col) {
		now->east = NULL;
	} else {

		now->east = new node();
		node* temp = now->east;
		temp->contains = map[now->row][now->col + 1];
		temp->row = now->row;
		temp->col = now->col + 1;

		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = wall(map,temp, G_row, G_col,map_row,map_col);
				temp->path = now->path;
				temp->path.push_back('E');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

	if (now->col == 0) {
		now->west = NULL;
	} else {
		now->west = new node();
		node* temp = now->west;
		temp->contains = map[now->row][now->col - 1];
		temp->row = now->row;
		temp->col = now->col - 1;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {
				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = wall(map,temp, G_row, G_col,map_row,map_col);
				temp->path = now->path;
				temp->path.push_back('W');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}
	if (now->row == 0) {
		now->north = NULL;
	} else {
		now->north = new node();
		node* temp = now->north;
		temp->contains = map[now->row - 1][now->col];
		temp->row = now->row - 1;
		temp->col = now->col;
		if (temp->contains != 'X' && temp->contains != 'O') {
			temp->health = now->health - damage(map, temp->row, temp->col);
			if (temp->health > 0
					&& record[temp->row][temp->col][temp->health - 1] == 0) {

				record[temp->row][temp->col][temp->health - 1] = 1;
				temp->distance = wall(map,temp, G_row, G_col,map_row,map_col);
				temp->path = now->path;
				temp->path.push_back('N');
				temp->path_length = now->path_length + 1;
				if (now->contains == ' ')
					temp->path_cost = now->path_cost + 1;
				else if (now->contains == '*')
					temp->path_cost = now->path_cost + 3;
				else
					temp->path_cost = now->path_cost;
				frontier.push_back(temp);

			}
		}
	}

}




vector<char> a_search_4(char** map, int& num_nodes, int S_row, int S_col,
		int map_row, int map_col, int G_row, int G_col) {
	int*** record = new int**[map_row];
	for (int i = 0; i < map_row; ++i) {
		record[i] = new int*[map_col];
		for (int j = 0; j < map_col; j++) {
			record[i][j] = new int[5];
		}
	}

	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			for (int k = 0; k < 5; k++) {
				record[i][j][k] = 0;
			}
		}
	}
	vector<char> path;
	node* start = new node();
	start->contains = map[S_row][S_col];
	start->row = S_row;
	start->col = S_col;
	record[S_row][S_col][4] = 1;
	start->path_cost = 1;
	start->path_length = 0;
	start->health = 5;
	start->distance = wall(map,start, G_row, G_col,map_row,map_col);
	vector<node*> frontier;
	find_frontier_wall(record, map, start, frontier, map_row, map_col, G_row,
			G_col);

	bool stop = false;
	node* now = start;

	while (stop == false) {

		//cout << "Row: " << now->row + 1 << " Col: " << now->col << " Dist: "
		//<< now->distance << " Heath: " << now->health << endl;

		if (frontier.empty()) {
			cout << "OH NO!!!!!!!!!!!!!!!!!";
			vector<char> a;
			return a;
		}
		if (now->contains == 'G') {
			cout << '\n';
			cout << "Wall: " << endl;
			G_row = now->row;
			G_col = now->col;
			printInfo(now, num_nodes);

			for (int i = 0; i < map_row; ++i) {
				delete[] record[i];

			}

			delete[] record;
			return now->path;
		}

		int min = minimum_a_distance(frontier);
		now = frontier[min];

		frontier.erase(frontier.begin() + min);
		find_frontier_wall(record, map, now, frontier, map_row, map_col, G_row,
				G_col);
		num_nodes++;
	}

	return path;
}



int main() {

	/******input the txt file as a 2 d char array********/

	int rows, columns;
	int S_row, S_col;
	int G_row, G_col;
	int num_nodes;
	num_nodes = 1;
	//row starting from 0 and column starting from 0
	ifstream ifs("test_map3.txt", std::ifstream::in);

	ifs >> rows;
	ifs >> columns;
	columns = columns + 1; //one extra column for the char newline
	char** map = new char*[rows];
	for (int i = 0; i < rows; ++i)
		map[i] = new char[columns];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = ifs.get();
			if (map[i][j] == 'S') {
				S_row = i;
				S_col = j - 1;

			}

		}
		//elminate the first column of /n
		for (int j = 0; j < columns; j++) {
			map[i][j] = map[i][j + 1];
		}
	}
	ifs.close();
	columns = columns - 1;

	/**********Depth first search***********/
	vector<char> path_depth = depth_search(map, num_nodes, S_row, S_col, rows,
			columns, G_row, G_col);
	/*********DBreath first search**********/
	num_nodes = 1;
	vector<char> path_breath = breath_search(map, num_nodes, S_row, S_col, rows,
			columns, G_row, G_col);
	/**********Uniform cost search**********/
	num_nodes = 1;
	vector<char> path_uniform = uniform_search(map, num_nodes, S_row, S_col,
			rows, columns, G_row, G_col);
	/***********Greedy Search***************/
	num_nodes = 1;
	vector<char> path_greedy = greedy(map, num_nodes, S_row, S_col, rows,
			columns, G_row, G_col);

	num_nodes = 1;
	vector<char> path_a = a_search(map, num_nodes, S_row, S_col, rows, columns,
			G_row, G_col);


	num_nodes = 1;
	vector<char> path_a_1 =a_search_1(map, num_nodes, S_row, S_col, rows, columns, G_row, G_col);
	/**********2C 3************/
	num_nodes = 1;
	vector<char> path_a_3 =a_search_3(map, num_nodes, S_row, S_col, rows, columns, G_row, G_col);


	num_nodes = 1;
		vector<char> path_a_4 =a_search_4(map, num_nodes, S_row, S_col, rows, columns, G_row, G_col);
	/******delete the dynamic variables******/
	for (int i = 0; i < rows; ++i) {
		delete[] map[i];
	}
	delete[] map;
	cout << "program finish";
	return 0;
}
