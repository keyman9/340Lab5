#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include<string>
#include<algorithm>

using namespace std;

string getCharPath(node<double>* root, int sizeOfTree, string c);
void Decode(node<double> *root, string encoded);
void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight);
void readPath(string fileName, vector<Path> *path_vec);
void sortVector(vector<node<double> > &weights);
void sortNodeVector(vector<node<double>* > &nodes);
void printTree(node<double>* root);
void printPath(node<double>* root,string letter);
string path;
int num;
int totalNum;

int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Enter the weights file name: ";
	cin >> input; 
	node<double>* first;
	vector<Path> path_vec;
	vector<node<double> > weights;
	double totalWeight = 0.0;
	readWeights(input, weights, totalWeight);
	cout << "Weights created" << endl;
	int sizeOfTree = weights.size();
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);
	
	//double totalWeight;
	
	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;
			 totalNum++;
		//totalWeight += weights[i].get_weight();
	}
	cout << "totalWeight: " << totalWeight << endl;
	
	sortVector(weights);
	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;
		//totalWeight += weights[i].get_weight();
	}
 	
 	vector<node<double>* > nodes;
	for(int i = 0; i < weights.size(); i++){
		nodes.push_back(new node<double>(weights[i].get_weight(),weights[i].get_char(),NULL,NULL));
	}
	cout << "Populated nodes vector" << endl;
	for(int i = 0; i < nodes.size(); i++){
		cout << "Nodes[" << i << "]: " << nodes[i]->get_weight() << endl;
	}
	node<double>* newNode;

	while(nodes[0]->get_weight() != totalWeight){
		sortNodeVector(nodes);					//sort the vector
		node<double>* smallest = nodes[0]; 		//the last item is smallest
		node<double>* nextSmallest = nodes[1];	//the second to last item is next smallest
		cout << "Building new node..." << endl;
		cout << "From characters: " 
				<< smallest->get_char() << " and "
				<< nextSmallest->get_char() << endl;
		cout << "From weights: "
				<< smallest->get_weight() << " and "
				<< nextSmallest->get_weight() << endl;
		newNode = new node<double>(smallest->get_weight()+nextSmallest->get_weight(),
					smallest->get_char()+nextSmallest->get_char(), smallest,nextSmallest);	//make a new node
		nodes.erase(nodes.begin());						//we used smallest already
		nodes.erase(nodes.begin());						//we used nextSmallest, too
		nodes.push_back(newNode);				//add new node into the vector
		
		cout << "Added node with weight " << nodes.back()->get_weight() << endl;
	}
	for(int i = 0; i < nodes.size(); i++){
		cout << "Nodes[" << i << "]: " << nodes[i]->get_weight() << endl;
	}
	node<double>* root = nodes[0];
	printTree(root);

	/*
	node<double>* root;
	double tempWeight;
	node<double>* lastConnection;
	for(int i = 0; i < sizeOfTree; i++){
		if(i == 0){
			node<double>* temp = new node<double>(weights[i].get_weight(),weights[i].get_char());
			root = temp;
			tempWeight += temp->get_weight();
			root->setBiNum(0);
		}
		else{
			node<double>* temp = new node<double>(weights[i].get_weight(),weights[i].get_char());
			lastConnection = new node<double>(root->get_weight() + temp->get_weight(), root, temp);
			root = lastConnection;
			root->setBiNum(0);
			temp->setBiNum(1);
			tempWeight += temp->get_weight();

			cout << "this is the binary on right child "<<root->getBiNum() <<endl;
			cout << "this is the binary on right child "<<temp->getBiNum() <<endl;
		}
	}
	*/
	cout << "Stuff set?" << endl;

	string letter;
	cout << "Insert letter: " << endl;
	cin >> letter;
	printTree(root);
	Decode(root,"1");

	// Diego is sending the path to this function
	printPath(root,letter);

/*
	node<double>* currentConnection;
	node<double>* smallest;
	node<double>* nextSmallest;
	for(int i = 0; i < weights.size(); i++){
		double tempWeights;
		if( i == 0){
			smallest = weights[0];
			nextSmallest = weights[1];
			if(weights[i] < smallest){
				smallest = weights[i];
			
			else if(weights[i] < nextSmallest){
				nextSmallest = weights[i];
			}
			node* toAdd = node(smallest->get_weight() + nextSmallest->get_weight(), smallest, nextSmallest);	
			currentConnection = nextSmallest;			
		}
		else{
			smallest = currentConnection;
		}

		node* toAdd = node(smallest->get_weight() + nextSmallest->get_weight(), smallest, nextSmallest);
	}
*/
	// for(double i = 0; i < pathSize; i++){
	// 	cout << "Item " << i << " is "
	// 		 << path_vec[i].get_data()
	// 		 << " with a path of "  
	// 		 << path_vec[i].get_path() << endl;
	// }
	/*
	int count;
	string path;
	cout << "Insert letter: " << endl;
	cin >> letter;
	path = getCharPath(root,sizeOfTree,letter);
	cout << "The path of " << letter << " is " << path << endl;
	*/
 	/*
	for(int i = weights.size()-1; i > 0; i--){
		// cout << "Item " << i << " is " << weights[i].get_char() << " with a weight of " << weights[i].get_weight() << endl;
		if(weights[i].get_char() == letter){
			if(i==weights.size()){
				path = "1";
			}
			else{
				path.insert(0,"1"); 
			}
			cout << "Path nigga! " << path << endl;
			break;
		}
		else{
			path = path + "0";
		}
		count++;
		//totalWeight += weights[i].get_weight();
	}
	*/

	cout << "End!" << endl;	
	return 0;
}

string getCharPath(node<double>* root, int sizeOfTree, string c){
	string path = "";
	char left = '0';
	char right = '1';
	node<double>* lastRoot;
	for(int i = 0; i < sizeOfTree ; i++){
		if(root->right_child()->get_char() == c){
			cout << "Added 1 -- i == size - 1 if" << endl;
			path += right;
			break;
		}
		else{
			if(root->left_child()->get_char() == c){
				cout << "Added 1 -- else if" << endl;
				path += right;
				break;
			}
			else{
				cout << "Added 0 -- else else if" << endl;
				path += left;
				if(root->left_child()){
					lastRoot = root;
					cout << "Changed root to left child" << endl;
					root = root->left_child();
				}
			}			
		}
	}
	return path;	
}

void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight){
	//for line in file
	ifstream infile;
	string key;  			//first character is the data for node
	double weight;
	//second string is weight of character 
	infile.open(fileName.c_str());
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		//cout << "This line: " << temp << endl;
		if(temp != ""){
			key = temp[0];
			//cout << "Key: " << key << endl;
			weight = atof(temp.substr(2,temp.size()-1).c_str());
			totalWeight += weight;
			//cout << "weight: " << weight<<endl;
			node<double> tempnode = node<double>(weight, key);
		//	cout << "About to push" << endl;
			weights.push_back(tempnode);
		}
	}
}

void readPath(string fileName, vector<Path> *path_vec, int pathSize){
	//for line in file
	ifstream infile;
	//sting key;		//first character is the data for node
	double 	pathBinary = 0;		//second string is path of character 
	infile.open(fileName.c_str());
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		// cout << "This line: " << temp << endl;
		if(temp != " "){
			string key = temp.substr(0, 1);
			// cout << "Key: " << key << endl;
			//pathBinary = atof(temp.substr(2).c_str());
			pathBinary= atof(temp.substr(1).c_str());
			// cout <<setprecision(4) << "pathBinary: " << pathBinary <<endl;
			Path tempPath = Path(key, pathBinary);
			path_vec->push_back(tempPath);
			pathSize ++;
		}
		// cout <<"Path size is " << pathSize<<endl;
	}	
}

void sortVector(vector<node<double> > &weights){
	int i, j;
	node<double> temp;
	for(i = weights.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(weights[j-1].get_weight() > weights[j].get_weight()){
				temp = weights[j-1];
				weights[j-1] = weights[j];
				weights[j] = temp;
			}
		}
	}
}

void sortNodeVector(vector<node<double>* > &nodes){
	int i, j;
	node<double>* temp;
	for(i = nodes.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(nodes[j-1]->get_weight() > nodes[j]->get_weight()){
				temp = nodes[j-1];
				nodes[j-1] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}

// THIS IS DIEGO'S METHOD
void printPath(node<double>* root, string letter){
	// cout << root->get_weight() << endl;
	if(root == NULL){
		cout << "End" << endl;
	}
	else{
		if(root->isLeaf()){
			// cout << "Leaf: " << root->get_char() 
				 // << "\t weighs " << root->get_weight() << endl;
			string curr =root->get_char();
			if(curr == letter){
				int newNum = totalNum-(num/2);
				for(int i = 0; i<(newNum-1); i++){
					if(i == 0){
						path = "1";
					}
					else{
						path = path + "0";
					}
				}
				cout << "Path nigga! " << path << endl;
			}

		}
		else{

			printPath(root->left_child(),letter);
			printPath(root->right_child(),letter);
		}
	}
	num++;
	//num =num/2;
}

void printTree(node<double>* root){
	// cout << root->get_weight() << endl;
	if(root != NULL){
		cout << "Root contents: "
			 << root->get_char() << " "
			 << root->get_weight() << endl;
		if(root->left_child()){ 
			cout << "Left" << endl; 
			printTree(root->left_child());
		}
		if(root->right_child()){
			cout << "Right" << endl;
			printTree(root->right_child());
		}
		//cout << root->get_char() << endl;
	}
}

void Decode(node<double> *root, string encoded){
	 node<double>* ptrRoot;
	 string finalCharacter;
	 int size = 0;
	 //cout << "this is root left_child: " << root->get_weight() << endl; 
	 for (int i = 0; i < encoded.size(); i ++){
	 	char x = encoded[i];
	 	if (x == '0'){
	 		ptrRoot = root->left_child();
	 		//cout << "this is the left child " << ptrRoot->right_child()->get_char() <<endl;
	 		finalCharacter = ptrRoot->right_child()->get_char();
	 		root = ptrRoot;
	 	}
 		else{
 			if (encoded.size() > 1){
	 			if(ptrRoot->right_child() != NULL){
		 			root = ptrRoot->left_child();
		 			//cout << "this is the right child " << root->right_child()->get_char() <<endl;
	 				finalCharacter = ptrRoot->right_child()->get_char();
	 			}
	 		}
	 		else{
	 			finalCharacter = root->right_child()->get_char();
	 		}
	 	}
		size ++;
	 }
	 cout << "The decoded binary code is: " << finalCharacter << endl;
}
