#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h> 
#include <time.h>

using namespace std;

struct point{
	int x;
	int y;
	point (int x_,int y_){
		x = x_;
		y = y_;
	}

	point & operator * (const point &p) {
    	this->x *= p.x;
    	this->y *= p.y;
    	return *this;
	}
};


template<typename T>
struct Node{
	T nodeData[2];
	Node<T> * sons [2];
	Node (){
		nodeData[0] = NULL;
		nodeData[1] = NULL;
		sons[0] = NULL;
		sons[1] = NULL;
	}
	Node (T data){
		nodeData[0] = data;
		//nodeData[1] = NULL;
		sons[0] = NULL;
		sons[1] = NULL;
	}
	Node (T data1, T data2){
		nodeData[0] = data1;
		nodeData[1] = data2;
		sons[0] = NULL;
		sons[1] = NULL;
	}

	bool dataIsNull (){
		if ( nodeData[0] && nodeData[1]) {
			return false;
		}
		else
			return true;
	}
};

//Busqueda: interseccion de dos radios :D

template<typename T>
class bsTree{
public:
	Node<T> * head;
	bsTree( vector<T> data ){
		build_tree (data, &head);
	}

	int get_distance (string a, string b){
		int distance = 0;
		for (int i = 0; i < a.size() && i<b.size(); ++i){
			if ( a.at(i) != b.at(i) ){
				distance+=1;
			}
		}
		int d1 = a.size();
		int d2 = b.size();
		distance = distance + abs( d1-d2 );
		return distance;
	}

	double distance(point a, point b){
		return sqrt ( pow((b.x-a.x),2) + pow ((b.y-a.y),2) );
	}

	bool build_tree ( vector<T> data, Node<T> ** current){
		if (data.size() == 2){
			*(current)= new Node<T> (data.at(0), data.at(1));
			return true;
		}
		else if (data.size() == 1){
			*(current)= new Node<T> (data.at(0));
			return true;
		}
		else {
			srand (time(NULL));
			//getting random positions
			int pos1, pos2 = rand() % data.size();
			while (pos1 == pos2){
				pos2 = rand() % data.size();
			}
			*(current)=new Node<T> (data.at(pos1),data.at(pos2));
			//Deleting those elements
			data.erase(data.begin()+(pos1-1));
			data.erase(data.begin()+(pos2-1));

			vector <T> data_near_to_pos1;
			vector <T> data_near_to_pos2;
			for (int i = 0; i < data.size(); ++i){
				if ( get_distance(data.at(i),(*current)->nodeData[0] ) <= get_distance(data.at(i),(*current)->nodeData[1]) ){
					data_near_to_pos1.push_back(data.at(i));
				}
				else{
					data_near_to_pos2.push_back(data.at(i));
				}
			}
			
			build_tree( data_near_to_pos1,&((*current)->sons[0]) );
			build_tree( data_near_to_pos2,&((*current)->sons[1]) );
		}	
	}

	~bsTree(){}
	
};


int main(){
	cout<<"Hello World!";
	vector<point> points;
	points.push_back(point(2,3));
	points.push_back(point(8,2));
	/*points.push_back(point(6,7));
	points.push_back(point(3,3));
	points.push_back(point(1,3));
	*/bsTree<point> a (points);
	
	return 0;
}