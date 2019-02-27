#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

class HillClimbing
{
private:
	long goalStateInt;
	long startStateInt;
	std::string goalState;
	std::string startState;
	
	
	
public:
	void stringToMatrix(int** matrix, std::string s, int* x0,int* y0)
	{
		matrix[0][0] = s[0] -48;
		matrix[0][1] = s[1] -48;
		matrix[0][2] = s[2] -48;
		matrix[1][0] = s[3]-48;
		matrix[1][1] = s[4] -48;
		matrix[1][2] = s[5] -48;
		matrix[2][0] = s[6]-48;
		matrix[2][1] = s[7] -48;
		matrix[2][2] = s[8] -48;
	
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				if(matrix[i][j] == 0)
				{
					*x0 = i;
					*y0 = j;
					return;
				}
	}
	
	std::string matrixToString(int** matrix)
	{
		string temp = "";
	
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
			{
				temp = temp+std::to_string(matrix[i][j]);
			}
			
		return temp;
	}
	
	int levelF( string child)
	{
		int score = 0;
		for(int i = 0; i < 9; i++)
		{
			if(goalState[i] == child[i])
				score++;
			
		}
		return score;
	}

	void solve(std::string startS, std::string goalS, std::string minMoves)
	{
		startStateInt = stoi(startS);
		goalStateInt = stoi(goalS);
		startState = startS;
		goalState = goalS;
		StackQueue* children = new StackQueue();
		int** matrix = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				matrix[i] = new int[3];
			}
		Node* nodeptr = new Node(startS);	
		Node* found = NULL;	
		recSolve(nodeptr, found, matrix, levelF(nodeptr->name));
			
			if(found != NULL)
			{
				cout<<"found something\n";
			}
			else
			{
				cout<<"found nothing\n";
			}
		
	}
	
	void recSolve(Node* nodeptr, Node* found, int ** matrix, int level)
	{
		int x, y;
		if(nodeptr->name == goalState)
		{
			found = nodeptr;
		}
		else
		{
				//cout<<nodeptr->name<<endl;
				stringToMatrix(matrix, nodeptr->name, &x, &y);
			
				if(x-1 >= 0)
				{
					int temp = matrix[x][y];
					matrix[x][y] = matrix[x-1][y];
					matrix[x-1][y] = temp;
					
					string childString = matrixToString(matrix);
					int l = levelF(childString);
					cout<<nodeptr->name<<" parent:"<<level<<"-"<<l<<":child "<<childString<<" goal: "<<goalState<<endl;
					if(level< l)
					{
						cout<<"in\n";
						Node* t = new Node(childString);
						nodeptr->up = t;
						t->parent = nodeptr;
						recSolve(t, found, matrix, l);
						cout<<"out\n";
					}

					temp = matrix[x][y];
					matrix[x][y] = matrix[x-1][y];
					matrix[x-1][y] = temp;
					
				}
				if(x+1 < 3)
				{
					int temp = matrix[x][y];
					matrix[x][y] = matrix[x+1][y];
					matrix[x+1][y] = temp;
					
					string childString = matrixToString(matrix);
					
					int l = levelF(childString);
					cout<<nodeptr->name<<" parent:"<<level<<"-"<<l<<":child "<<childString<<" goal: "<<goalState<<endl;
					if(level< l)
					{
						cout<<"in\n";
						Node* t = new Node(childString);
						nodeptr->down = t;
						t->parent = nodeptr;
						recSolve(t, found, matrix, l);
						cout<<"out\n";
					}

					temp = matrix[x][y];
					matrix[x][y] = matrix[x+1][y];
					matrix[x+1][y] = temp;
				}
				if(y-1 >= 0)
				{
					int temp = matrix[x][y];
					matrix[x][y] = matrix[x][y-1];
					matrix[x][y-1] = temp;
					
					string childString = matrixToString(matrix);
					
					int l = levelF(childString);
					cout<<nodeptr->name<<" parent:"<<level<<"-"<<l<<":child "<<childString<<" goal: "<<goalState<<endl;
					if(level< l)
					{
						cout<<"in\n";
						Node* t = new Node(childString);
						nodeptr->left = t;
						t->parent = nodeptr;
						recSolve(t, found, matrix, l);
						cout<<"out\n";
					}

					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y-1];
					matrix[x][y-1] = temp;
				}
				if(y+1 < 3)
				{
					int temp = matrix[x][y];
					matrix[x][y] = matrix[x][y+1];
					matrix[x][y+1] = temp;
					
					string childString = matrixToString(matrix);
					
					int l = levelF(childString);
					cout<<nodeptr->name<<" parent:"<<level<<"-"<<l<<":child "<<childString<<" goal: "<<goalState<<endl;
					if(level< l)
					{
						cout<<"in\n";
						Node* t = new Node(childString);
						nodeptr->right = t;
						t->parent = nodeptr;
						recSolve(t, found, matrix, l);
						cout<<"out\n";
					}

					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y+1];
					matrix[x][y+1] = temp;
				}
		}
		
	}
	
	
};

#endif