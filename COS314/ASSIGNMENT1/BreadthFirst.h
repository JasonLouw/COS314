#ifndef BREADTHFIRST_H
#define BREADTHFIRST_H

#include "StackQueue.h"
#include <iostream>
#include <string>

using namespace std;

class BreadthFirst
{
	private:
		long goalStateInt;
		long startStateInt;
		std::string goalState;
		std::string startState;
		bool* close;
	Node* head;
	
	public:
		BreadthFirst()
		{
			close = new bool[999999999];
			for(int i = 0; i < 999999999; i++)
			{
				close[i] = false;
			}
		}
		
		void clear()
		{
			for(int i = 0; i < 999999999; i++)
			{
				close[i] = false;
			}
		}
		
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
		
		void printMatrix(Node* p)
		{
				int move = 0;
				StackQueue* stack = new StackQueue();
				int totalNode = p->nem;
				
				while(p != head)
				{
					move++;
					stack->addFront(p);
					p = p->parent;
				}
				stack->addFront(p);
				cout<<p->name<<", Nodes created: "<<totalNode<<", Moves: "<<move<<endl;
				p = stack->removeFront();
				while(p != NULL)
				{
					for(int i = 0; i < 9; i++)
					{	
							//comment in to print changes
							//cout<<p->name[i]<<" ";
							//~ if(i == 2)
								//~ cout<<endl;
							//~ if(i == 5)
								//~ cout<<endl;
							//~ if(i == 8)
								//~ cout<<endl;
						
					}
					//cout<<endl;	
					p = stack->removeFront();
				}
				
				
		}

		void solve(std::string startS, std::string goalS, std::string minMoves)
		{
			clear();
			startStateInt = stoi(startS);
			goalStateInt = stoi(goalS);
			startState = startS;
			goalState = goalS;
			//from here you need to go breadth first by creating new nodes
			StackQueue* children = new StackQueue();
			Node* nodeptr = new Node(startS);
			head = nodeptr;
			children->addBack(nodeptr);
			int** matrix = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				matrix[i] = new int[3];
			}
	
			int x, y;
			
			int temp = 0;
			int atemp = 0;
		
			while(nodeptr->name != goalState )
			{
			
				nodeptr = children->removeFront();
		
				
				if(nodeptr == NULL)
				{
					cout<<"broken\n";
					break;
				}
				//cout<<nodeptr->name<<endl;
		
				stringToMatrix(matrix, nodeptr->name, &x, &y);

				if(x-1 >= 0)
				{
					temp = matrix[x][y];
					matrix[x][y] = matrix[x-1][y];
					matrix[x-1][y] = temp;
					
					string s = matrixToString(matrix);
					atemp = stoi(s);
					if(close[atemp] == false)
					{
						Node* t = new Node(s);
						nodeptr->up = t;
						t->parent = nodeptr;
						children->addBack(t);
						close[atemp] = true;
					}
					
					temp = matrix[x][y];
					matrix[x][y] = matrix[x-1][y];
					matrix[x-1][y] = temp;
					
					
				}
				if(x+1 < 3)
				{
					temp = matrix[x][y];
					matrix[x][y] = matrix[x+1][y];
					matrix[x+1][y] = temp;
					
					string s = matrixToString(matrix);
					atemp = stoi(s);
					if(close[atemp] == false)
					{
						Node* t = new Node(s);
						nodeptr->down = t;
						t->parent = nodeptr;
						children->addBack(t);
						close[atemp] = true;
					}
					
					temp = matrix[x][y];
					matrix[x][y] = matrix[x+1][y];
					matrix[x+1][y] = temp;
	
				
				}
				if(y-1 >= 0)
				{
					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y-1];
					matrix[x][y-1] = temp;
					
					string s = matrixToString(matrix);
					atemp = stoi(s);
					if(close[atemp] == false)
					{
						Node* t = new Node(s);
						nodeptr->left = t;
						t->parent = nodeptr;
						children->addBack(t);
						close[atemp] = true;
					}
				
					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y-1];
					matrix[x][y-1] = temp;
				}
				if(y+1 < 3)
				{
					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y+1];
					matrix[x][y+1] = temp;
					
					string s = matrixToString(matrix);
					atemp = stoi(s);
					if(close[atemp] == false)
					{
						Node* t = new Node(s);
						nodeptr->right = t;
						t->parent = nodeptr;
						children->addBack(t);
						close[atemp] = true;
					}
					
					temp = matrix[x][y];
					matrix[x][y] = matrix[x][y+1];
					matrix[x][y+1] = temp;
				}
			
		
			}
		
			printMatrix(nodeptr);
			
			
		}
};

#endif