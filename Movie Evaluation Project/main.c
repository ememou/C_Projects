#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "unistd.h"
#include"fileutil.c"

#define HASH_TABLE_SIZE 100

/* DECLARE STRUCTS, GLOBAL VARIABLES AND FUNCTIONS*/
typedef struct entryT entryT;

struct entryT{
  char *word;
  int number;
  int score;
  entryT *next;
  entryT *prev;
};

typedef struct{
  int size;
  int num_entries;
  entryT **table;
} hashT;

hashT *hash_table; // The ONLY global variable to access the lists

//euresh me anadromikh tropo se mia lista th lexh me to megalitero score 
entryT *max_finder(entryT *list){
	
	entryT *max;
	double average, average_max;
	
	if(list==NULL){//an h lista einai kenh
		return (NULL);
	}
	
	max=max_finder(list->next);
	
	if(max==NULL){
		return (list);
	}
	
	average=(float)list->score/(float)list->number;
	average_max=(float)max->score/(float)max->number;
	
	if(average>=average_max){
		max=list;
	}
	
	return (max);
}

void  initialize_table_sc(entryT table_sc[hash_table->size]){
	
	int i, j=0;
	entryT *ptr;
	
	for(i=0; i<hash_table->size; i++){
		table_sc[i].word=NULL;
		table_sc[i].score=-1;
		table_sc[i].number=-1;
	}
	//arxikopoihsh tou table score me th lexh kathe listas pou exei to megisto score
	for(i=0; i<hash_table->size; i++){
		ptr=max_finder(hash_table->table[i]);
		if(ptr!=NULL){
			table_sc[j].word=ptr->word;
			table_sc[j].score=ptr->score;
			table_sc[j].number=ptr->number;
			j++;
		}
	}
}

//euresh me anadromiko tropo th lexh me to megalytero score mesa ston pinaka table_sc
entryT max_score(entryT table_sc[hash_table->size], int location){
	
	double average, average_max;
	entryT max;
	
	if(table_sc[location].word==NULL || location>hash_table->size){
		return(max);
	}
	
	max=max_score(table_sc,location+1);
	
	if(max.word==NULL){
		max=table_sc[location];
		return(max);
	}
	
	average=(float)table_sc[location].score/(float)table_sc[location].number;
	average_max=(float)max.score/(float)max.number;
	
	if(average>=average_max){
		max=table_sc[location];
	}
	
	return (max);
}

//metatroph hefalaiwn grammatwn se mikra
char* bigtosmall(char *word){
	
	int i;
	
	for(i=0; i<strlen(word); i++){
		if(*(word+i)>='A' && *(word+i)<='Z'){
			*(word+i)=*(word+i)+32;
		}
	}
	return word;
}

unsigned long hash_function(char *str){
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

void create_hash_table(int size){
	int i;
	
	if (size<1){
		exit(0); // invalid size for table 
	}
// 	Attempt to allocate memory for the table structure 
	if ((hash_table = malloc(sizeof(hashT))) == NULL){
		exit(0);
	}
// 	Attempt to allocate memory for the table itself 
	if ((hash_table->table = malloc(sizeof(entryT *) * size)) == NULL){
		exit(0);
	}
// 	Initialize the elements of the table 
	for(i=0; i<size; i++){
		hash_table->table[i] = NULL;
	}
// 	Set the table's size
	hash_table->size = size;
// 	Set num_entries = 0 
	hash_table->num_entries=0;
	
}

entryT* search(char *word, unsigned long hash_location){
	
	entryT *list; //temp pointer to
	
// 	Go to the correct list, pointed by the hash_location, and search the list
	for (list=hash_table->table[hash_location]; list!=NULL; list=list->next){
		if (strcmp(word, list->word) == 0){
			return list; //if found
		}
	}
	return NULL;
}

//exagwgh kombou 
entryT* ExtractANode(int i){
	entryT *node;
	
	node=hash_table->table[i];
	
	if(hash_table->table[i]->next!=NULL){
		hash_table->table[i]->next->prev=hash_table->table[i]->prev;
		hash_table->table[i]=hash_table->table[i]->next;
	}
	else{
		hash_table->table[i]=NULL;
	}
	
	return(node);
}

//thetoume toys deiktes prev kai next isous me NULL etsi wste na prostethoun sth nea lista 
entryT* GetNewNode(entryT* new_node) {
	
	entryT* newNode = new_node;
	
	newNode->prev = NULL;
	newNode->next = NULL;
	
	return newNode;
}

//eisagwgh kombou ston pinaka help 
void InsertAtHead(entryT* new_node, entryT **help, int hash_location) {
	
	entryT* newNode = GetNewNode(new_node);
	
	if(help[hash_location] == NULL) {// an einai o prwtos kombos pou eisagetai
		help[hash_location] = newNode;
		return;
	}
	//alliws eisagetai sthn arxh ths listas
	help[hash_location]->prev = newNode;
	
	newNode->next = help[hash_location]; 
	
	help[hash_location] = newNode;
}

void rehash(){
	
	entryT **help, *new_node;
	int new_size = hash_table->size*2, i;//, j;
	unsigned long hashval, hash_location;
	
	if((help=malloc(sizeof(entryT*)*new_size))== NULL){
		exit(0);
	}
	
	for(i=0; i<hash_table->size; i++){
		help[i]=NULL;
	}
	
// 	find each node/word, calculate its hash value and put it in the right place 
	for (i = 0; i < new_size/2; i++) {
		
		while(hash_table->table[i]!=NULL){
			
			new_node=ExtractANode(i);
			
			hashval=hash_function(new_node->word);
			hash_location = hashval%new_size;
			
			InsertAtHead(new_node, help, hash_location);
		}
	}
	
	//diplasiasmos ths desmeumenhs mnhmhs gia ton hash table
	if ((hash_table->table = realloc(hash_table->table,sizeof(entryT *) * new_size )) == NULL){
		exit(0);
	}
	
	//o hash table pairnei ta dedomena tou help
	for(i=0; i<new_size; i++){
		hash_table->table[i]=help[i];
	}
	
	//diplasiasmos toy megethous tou pinaka
	hash_table->size=hash_table->size*2;
}

void up(entryT* list, int grade){
	
	list->number++;
	list->score= list->score+grade;
}

int add_entry(char* word,unsigned long hash_location, int grade){
	
	entryT* new_node;
	
//	 Attempt to allocate memory for list node 
	if ((new_node = malloc(sizeof(entryT))) == NULL){
		return 0;
	}
	
//	fill the node info
	
	new_node->word=strdup(word);
	new_node->number=1;
	new_node->score=grade;
	
	
// 	Linking the new node with the list, Put the new node, in the beggining of the list
	
	if (hash_table->table[hash_location] == NULL) {
// 		if it is the first node inserted to list
		
		hash_table->table[hash_location] = new_node;
		new_node->next=NULL;
		new_node->prev=NULL;
	}
	else{
// 		any other node
		new_node->next=hash_table->table[hash_location];
		new_node->prev=NULL;
		hash_table->table[hash_location]->prev=new_node;
		
		hash_table->table[hash_location] = new_node;
	}
// 	number of entries in hash_table +1
	
	hash_table->num_entries++;
	
	return 1;
}

//apomonwsh toy bathou kai kathe lexhhs poy periexei mia grammh
void extract(char* next_line){
	int grade,k=1;
	char *word, *token;
	entryT* found;
	unsigned long hashval, hash_location, load_factor;
	
	token = strtok(next_line," \t");
	
	while (token != NULL){
		
		if(k==1){ //if it is integer
			grade = *token- '0'; //char to int
			k=0;
		}
		else{ //if it is a word
			word = bigtosmall(token);
			
// 			euresh tou hash value kathe lexhs kai ths theshs ths ston hash table 
 			hashval= hash_function(word);
			hash_location=hashval%hash_table->size;
			
// 			find word in Hash Tables
			found = search(word,hash_location);
			
			if (found){ //if found, add up the number of sh
				up(found,grade);
 			}
 			else{ //if not, add an entry
				add_entry(word,hash_location,grade);
// 				 check if need rehashing
				load_factor=(hash_table->num_entries)/(hash_table->size);
				
				if (load_factor>4) {
					rehash();
				}
 			}
		}
		token = strtok (NULL, " \t");
	}
	k=1;
// 	end of line
}

//ektupwsh tou hash table
void print_hash_table(entryT* list, int hash_location){
	
	entryT* head;
	
	if(list!=NULL){
		printf("%4d: ", hash_location);
		for(head=list; head!=NULL; list=list->next){
			printf("[ %c%s%c %d %.2lf ]", '"', list->word, '"', list->number, (float)list->score);
			if(list->next!=NULL){
				printf(", ");
			}
			else{
				printf("\n");
				break;
			}
		}
	}
}

//upologismos toy mesou score mias lexhs  
double average_word(entryT* list, char *word){
	double average;
	entryT *head;
	
	for(head=list; head!=NULL; head=head->next){
		if(strcmp(head->word,word)==0){//ean yparxei h lexh sth lista
			average=(float)head->score/(float)head->number;
		}
	}
	return(average);
}

//eisagwgh kritikhs 
void enter_review(char *line){
	
	char *word, *token;
	unsigned long hashval, hash_location;
	entryT* found;
	int sum=0;
	double average=0, average_line;
	
	token = strtok(line," \t");
	
	while (token!=NULL){
		
		word = bigtosmall(token); 
		
		hashval= hash_function(word);
		hash_location=hashval%hash_table->size;
		
		//find word in Hash Tables
		found = search(word,hash_location);
		
		if (found){//an brethei ypologizei to athroistiko score twn lexewn poy brethhkan 
			average+=average_word(hash_table->table[hash_location], word);
			sum++;//poses lexeis brethhkan
		}
		
		token = strtok (NULL, " \t");
	}
	
	if(sum==0){
		printf("Sorry, there is no score for this review!\n");
	}
	else{
		average_line=(float)average/(float)sum;//ypologismos mesou score ths neas kritikhs
		printf("Review score: %.4lf\n", average_line );
		
		if(average_line<2){
			printf("This review is negative.\n");
		}
		else if(average_line==2){
			printf("This review is neutral.\n");
		}
		else{
			printf("This review is positive.\n");
		}
	}
} 

int main(int argc, char *argv[]) {
	char *next_line, *filename, *line = NULL;
	entryT table_data;
	double average;
	int i;
	size_t len = 0; 
	ssize_t read;
	
	if(argc!=2 && (strcmp(argv[2],"-p")!=0)){
		printf("Incorrect number of parameters.\n");
		exit(0);
	}
	
	filename=argv[1]; //set filename
	
//	create and Initialize HASH table
	create_hash_table(HASH_TABLE_SIZE);
	
	next_line = read_next_line(filename);
	
//	extract integer and words from line
	while (next_line!= NULL) {
		
//		extraction of integer and words
		extract(next_line);
		
		next_line=read_next_line(filename);
	}
	
	entryT table_sc[hash_table->size];
	
	//Initialize table score
	initialize_table_sc(table_sc);
	
	//find the word with max score
	table_data=max_score(table_sc,0);
	
	//upologismos average ths lexhs me to max score
	average=(float)table_data.score/(float)table_data.number;
	printf("The most positive word is %c%s%c with a score of %.3lf\n\n", '"', table_data.word, '"', average);
	
	if(argc==3 && (strcmp(argv[2],"-p")==0)){
		for(i=0; i<hash_table->size; i++){
			print_hash_table(hash_table->table[i],i);
		}
		printf("\n");
	}
	
	printf("\nEnter review or DONE to finish:\n");
	read=getline(&line, &len, stdin);
	*(line+strlen(line)-1)='\0';
	
	//an o xrhsths eisagei th lexh DONNE to programma teleiwnei
	while(read!=-1 && strcmp(line,"DONE")!=0){
		
		if(read==1){
			printf("Sorry, there is no score for this review!\n");
		}
		else{
			enter_review(line);
		}
		printf("\nEnter review or DONE to finish:\n");
		read=getline(&line, &(len), stdin);
		
		*(line+strlen(line)-1)='\0';
	}
	
	//apodesmeush dynakika desmeumenhs mnhmhs
	entryT *current, *next;
	
	for(i=0; i<hash_table->size; i++){
		
		current=hash_table->table[i];
		
		while( current != NULL ) {
			next = current->next;
			free( current );
			current = next;
		}
	}
	
	free(hash_table->table);
	free(hash_table);
	
	
	return 0;
}