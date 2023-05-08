#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
using namespace std;

struct Game{ 
	char name[100]; 
	char genre[100]; 
	int stock; 
	int height; 
	
	Game* left, *right; 
}*root, *temp = 0;

int get_height(Game* curr){
	if(curr == 0){
		return 0;
	}
	return curr->height;
}

int get_balance(Game* curr){
	if(curr == 0){
		return 0;
	}
	return get_height(curr->left) - get_height(curr->right); 
}

int get_max(int a, int b){
	return a > b ? a : b; 
}

struct Game* left_rotation(Game* curr){
	Game* child = curr->right;
	Game* left_child = child->left;
	
	curr->right = left_child;
	child->left = curr;
	
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right));
	child->height = 1 +  get_max(get_height(child->left), get_height(child->right));
	
	return child; 
}

struct Game* right_rotation(Game* curr){
	Game* child = curr->left;
	Game* right_child = child->right;
	
	curr->left = right_child;
	child->right = curr;
	
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right));
	child->height = 1 +  get_max(get_height(child->left), get_height(child->right));
	
	return child; 
}


struct Game* insert_new_game(Game* curr, Game* new_game){
	if(curr == 0){
		return new_game;
	}
	else if(strcmp(curr->name, new_game->name) < 0 ){
		curr->left = insert_new_game(curr->left, new_game); 
	}
	else if(strcmp(curr->name, new_game->name) > 0){
		curr->right = insert_new_game(curr->right, new_game); 
	}
	
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right)); 
	int balance = get_balance(curr); 
	
	if(balance < -1){
		if(get_balance(curr->right) > 0){
			curr->right = right_rotation(curr->right);
		}
		return left_rotation(curr); 
	}
	if(balance > 1){
		if(get_balance(curr->left) < 0){
			curr->left = left_rotation(curr->left);
		}
		return right_rotation(curr); 
	}
	return curr; 
}

struct Game* delete_node(Game* curr, const char* name){
	if(curr == 0){
		return 0;
	}
	else if(strcmp(curr->name, name) < 0){
		curr->right = delete_node(curr->right, name);
	}
	else if(strcmp(curr->name, name) > 0){
		curr->left = delete_node(curr->left, name);
	}
	else{
		if(!curr->right && !curr->left){
			free(curr);
			return 0;
		}
		else if(!curr->right){
			return curr->left;
		}
		else if(!curr->left){
			return curr->right;
		}
		else{
			temp = curr->right;
			while(temp->left){
				temp = temp->left;
			}
			strcpy(curr->name, temp->name);
			strcpy(curr->genre, temp->genre);
			curr->stock = temp->stock;
			curr->right = delete_node(curr->right, temp->name); 
		}
	}
	
	if(curr == 0){
		return 0;
	}
	curr->height = 1 + get_max(get_height(curr->left), get_height(curr->right)); 
	int balance = get_balance(curr); 
	
	if(balance < -1){
		if(get_balance(curr->right) > 0){
			curr->right = right_rotation(curr->right);
		}
		return left_rotation(curr); 
	}
	if(balance > 1){
		if(get_balance(curr->left) < 0){
			curr->left = left_rotation(curr->left);
		}
		return right_rotation(curr); 
	}
	
	return curr;
}

//this is for finding

Game* finding(Game* curr, const char* name){
	if(curr == 0){
		return 0;
	}
	else if(strcmp(curr->name, name) < 0){
		return finding(curr->left, name);
	}
	else if(strcmp(curr->name, name) > 0){
		return finding(curr->right, name);
	}
	return curr; 
}



//this is for inserting the new thing 
struct Game* make_new_game(const char* name, const char* genre, int stock){
	temp = (Game*)malloc(sizeof(Game));
	strcpy(temp->genre, genre);
	strcpy(temp->name, name);
	temp->stock  = stock; 
	temp->left = temp->right = 0;
	temp->height = 1; 
	return insert_new_game(root, temp);
}

void print(Game* curr){
	if(curr == 0){
		return;
	}
	print(curr->left);
	printf("=====================================\n");
	printf("%-10s | %10s | %10d | \n",curr->name, curr->genre, curr->stock);
	printf("=====================================\n");
	print(curr->right);	
}
int main(){
	
	
	int input = 0;
	do{ 
		char input_name[100];
		char input_game_type[100]; 
		int stock = 0; 
		char input_user[20];
		int temp_ = 0;
		
		printf("BlueJack Group\n");
		printf("======================\n");
		printf("1. Insert Game\n");
		printf("2. VIew Game\n");
		printf("3. Update Game\n"); 
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &input);getchar();
		
		
		switch (input){
			
			case 1 : 
				do{
					printf("Input Game Tittle [5 - 25] : ")	;
					scanf("%[^\n]", input_name); getchar();
				}while(strlen(input_name) > 25 || strlen(input_name) < 5);
				
				do{
					printf("Input game type [Action|RPG|Adventure|Card Game] : "); 	
					scanf("%[^\n]", input_game_type); getchar();
					if(strcmp(input_game_type, "RPG") == 0){
						temp_ = 1;
					}
					else if(strcmp(input_game_type, "Adventure") == 0){
						temp_ = 1;
					}
					else if(strcmp(input_game_type, "Card Game")== 0){
						temp_ = 1; 
					}
					else if(strcmp(input_game_type, "Action")== 0){
						temp_ = 1; 
					}
				}while(temp_ == 0);
				
				do{
					printf("Input game stock[>=1] : "); 
					scanf("%d", &stock); getchar();	
				}while(stock < 1); 
				root = make_new_game(input_name, input_game_type, stock);
				printf("Successfully insert your game to warehouse\n\n");
				
				printf("Press enter to continue...\n"); 
				getchar();
				
				break; 
			
			case 2 : 
				print(root);
				break;
			
			case 3 : 
				printf("Insert your game tittle : "); 
				scanf("%[^\n]", input_name); getchar();
				
				temp = finding(root, input_name);
				if(temp){
					printf("Current stock : %d\n\n", temp->stock); 
					do{	
						printf("Input update type[add|remove][case insensitive] : "); 
						scanf("%[^\n]", input_user);getchar();  
					}while(strcmp(input_user, "add") != 0 && strcmp(input_user, "remove") != 0); 
					
					if(strcmp(input_user, "remove") == 0){
						do{
							printf("Input stock to remove [1 - %d] : ", temp->stock);
							scanf("%d", &stock); getchar();  	
						}while(stock < 1 || stock > temp->stock); 
						
						printf("Data deleted succesfully !!!\n");
						printf("%d ==> %s`s stock is deleted to warehouse\n\n",stock,  temp->name);	
						temp->stock -= stock; 
						
						if(temp->stock == 0){
							root = delete_node(root, temp->name);
						}
					}
					else if(strcmp(input_user, "add") == 0){
						do{
							printf("Input stock to add [1>=] : ", temp->stock);
							scanf("%d", &stock); getchar();  	
						}while(stock < 1); 	
						temp->stock += stock; 
						
						printf("Data update succesfully !!!\n");
						printf("%d ==> %s`s stock is added from warehouse\n\n", stock, temp->name);;
					}
				}	
				else{
					printf("Data not found !!!\n"); 
				}
				printf("Press enter to continue...\n"); 
				getchar();	
				break;
				
			default:
				break; 
		}	
	}while(input != 4);
	
	return 0;
}
