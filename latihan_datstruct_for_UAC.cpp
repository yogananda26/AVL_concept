#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;


int calculate = 1;

struct Car{
	char name_car[100];
	int year;
	int id; 
	
	int height; 
	Car* left, *right;
}*root, *temp = 0;

struct Car_linked{
	Car* linked;
	Car_linked* next; 
}*head;

//this is for inserting 
int get_height(Car* node){
	if(node==0){
		return 0;
	}
	return node->height; 
}

int get_balance(Car* node){
	if(node==0){
		return 0;
	}
	return get_height(node->left) - get_height(node->right);
}

int get_max(int a, int b){
	return (a > b) ?  a : b;
}

Car* left_rotation(Car* node){
	Car* child = node->right;
	Car* left_child = child->left;
	
	node->right = left_child;
	child->left = node;
	
	node->height = 1 + get_max(get_height(node->left), get_height(node->right));
	child->height = 1 + get_max(get_height(child->left), get_height(child->right));
	
	return child;
	
	
}
Car* right_rotation(Car* node){
	Car* child = node->left;
	Car* right_child = child->right;
	
	node->left = right_child; 
	child->right = node;
	
	node->height = 1 + get_max(get_height(node->left), get_height(node->right));
	child->height = 1 + get_max(get_height(child->left), get_height(child->right));
	
	return child;
}


Car* insert_new_car(Car* curr, Car* new_node){
	if(curr==0){
		return new_node;
	}
	else if(curr->year < new_node->year){
		curr->right = insert_new_car(curr->right, new_node);
	}
	else if(curr->year > new_node->year){
		curr->left = insert_new_car(curr->left, new_node);
	}
	
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right));
	int get_balance_factor = get_balance(curr);
	
	if(get_balance_factor > 1){
		if(get_balance(curr->left) < 0){
			curr->left = left_rotation(curr->left);
		}
		return right_rotation(curr);
	}
	if(get_balance_factor < -1){
		if(get_balance(curr->right) > 0){
			curr->right =  right_rotation(curr->right); 
		}
		return left_rotation(curr); 
	}
	return curr;
}

struct Car* delete_node(Car* curr, int year){
	if(curr == 0){
		return 0;
	}
	else if(curr->year > year){
		curr->left = delete_node(curr->left, year); 
	}
	else if(curr->year < year){
		curr->right = delete_node(curr->right, year);
	}
	else{
		if(!curr->left && !curr->right){
			return 0;
		}
		else if(!curr->left){
			return curr->right; 
		}
		else if(!curr->right){
			return curr->left;
		}
		else{
			temp = curr->right;
			while(temp->left){
				temp = temp->left;
			}
			strcpy(curr->name_car, temp->name_car); 
			curr->year = temp->year;
			curr->id = temp->id; 
			curr->right = delete_node(curr->right, temp->year);
		}
	}
	
	if(curr==0){
		return curr;
	}
	
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right)); 
	int get_balance_node = get_balance(curr); 
	
	if(get_balance_node < -1){
		if(get_balance(curr->right) >= 0){
			curr->right = right_rotation(curr->right);
		}
		return left_rotation(curr);
	}
	if(get_balance_node > 1){
		if(get_balance(curr->left) <= 0){
			curr->left = left_rotation(curr->left);
		}
		return right_rotation(curr); 
	}
	return curr; 
}

struct Car* make_new_car(const char* name, int year){
	temp = (Car*)malloc(sizeof(Car));
	strcpy(temp->name_car, name);
	temp->year = year; 
	temp->height = 1; 
	temp->id = calculate; 
	temp->right = temp->left = 0;
	calculate++; 
	
	return insert_new_car(root, temp);
}

void print(Car* node){
	if(node==0){
		return;
	}
	printf("%10s |  %10d  | %10d\n |", node->name_car, node->year, node->height); 
	print(node->left);
	print(node->right);
}


struct Car* find(Car* curr, int year){
	if(curr == 0){
		return 0;
	}
	else if(curr->year < year){
		return find(curr->right, year); 
	}
	else if(curr->year > year){
		return find(curr->left, year); 
	}
	return curr;
}

int main(){ 
	
	root = make_new_car("mustang", 2020);
	root = make_new_car("lambo", 2023);
	root = make_new_car("honda", 2022);
	root = make_new_car("toyota", 2029);
	root = make_new_car("maclaren", 2027);
	root = make_new_car("hyundai", 3000); 
	
	root = delete_node(root, 2020);
	
	printf("%s\n", temp->name_car);
	
	printf("=======================================\n");
	print(root); 
	return 0;
}
