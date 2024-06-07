#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
	struct node* prev;
};

typedef struct node node_t;

struct doubly_linked_list
{
	node_t* head;
	node_t* tail;
	int size;
};

typedef struct doubly_linked_list list_t;
 
list_t* create_list();                                 // return a newly created empty doubly linked list
void insert_front(list_t* list, int data);             // inserts data to the beginning of the linked list
void insert_back(list_t* list, int data);              // inserts data to the end of the linked list
void insert_after(list_t* list, int data, int prev);   // inserts data after the node with data “prev”
void delete_node(list_t* list, int data);              // delete the node with “data” from the linked list.
node_t* search(list_t* list, int data);                // returns the pointer to the node with “data” field
void display_list(list_t* list);                       // print the linked list by separating each item by a space and a new line at the end of the linked list.

struct queue
{
	list_t* list;
	node_t* front;
	node_t* rear;
	int size;
};

typedef struct queue queue_t;

queue_t* create_queue();              // return a newly created empty queue
void enqueue(queue_t* q, int data);   // insert data at the end of a queue
int dequeue(queue_t* q); 	          // return the data at the front of a queue
void que_disp(queue_t* q);
void delete_queue();                  // empty the contents of the queue

typedef node_t song_t;
typedef queue_t music_queue_t;

struct playlist
{
	list_t* list;
	int num_songs;
	song_t* last_song;                // last played song		
};

typedef struct playlist playlist_t;

playlist_t* create_playlist();                            // return a newly created doubly linked list
void delete_playlist(playlist_t* playlist);               // delete the playlist
music_queue_t* create_music_queue();                      // return a newly created queue
void clear_music_queue(music_queue_t* q);                 // clear the queue q
void add_song(playlist_t* playlist, int id, int where);   // add a song id to playlist
void delete_song(playlist_t* playlist, int id);           // remove song id from the playlist
song_t* search_song(playlist_t* playlist, int id);        // return a pointer to the node where the song id is present in the playlist
void search_and_play(playlist_t* playlist, int song_id) ; // play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
void play_next(playlist_t* playlist, music_queue_t* q);   // play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
void play_previous(playlist_t* playlist);                 // play the previous song from the linked list
void play_from_queue(music_queue_t* q);                   // play a song from the queue
void insert_to_queue(music_queue_t* q, int id);           // insert a song id to the queue
void display_playlist(playlist_t* p);                     // Displays the playlist
void play_song(int song_id);                              // Call this function, to simulate playing of a song
void disp_queue(music_queue_t* q);
list_t* create_list()                                     // return a newly created empty doubly linked list
{
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}
node_t* create_node(int data)
{
	node_t* newnode = (node_t*) malloc(sizeof(node_t));
	newnode->data= data;
	newnode->next=NULL;
	newnode->prev=NULL;
	return newnode;
}
void insert_front(list_t* list, int data)                     // inserts data to the beginning of the linked list
{
	if(list->size==0)
	{
		list->head=create_node(data);
		list->tail=list->head;
	}
	else
	{
		node_t* newnode = create_node(data);
		newnode->next=list->head;
		list->head->prev=newnode;
		list->head=newnode;
	}
	list->size++;
}
void insert_back(list_t* list, int data)                       // inserts data to the end of the linked list
{
	if(list->size==0)
	{
		list->head=create_node(data);
		list->tail=list->head;
	}
	else
	{
		node_t* newnode = create_node(data);
		newnode->prev=list->tail;
		list->tail->next=newnode;
		list->tail=newnode;
	}
	list->size++;
}
void insert_after(list_t* list, int data, int prev)           // inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	node_t* temp = list->head;
	while(temp->data!=prev && temp!=NULL)
		temp=temp->next;
	if(temp!=NULL)
	{
		node_t* newnode = create_node(data);
		newnode->next=temp->next;
		newnode->prev=temp;
		newnode->next->prev=newnode;
		temp->next=newnode;
		list->size++;
	}
	else
		return;
}
void delete_node(list_t* list, int data)                      // delete the node with “data” from the linked list.
{
	node_t* del=list->head;
	while(del!=NULL && del->data!=data)
		del=del->next;
	if(del!=NULL)
	{
		if(del->prev!=NULL && del->next!=NULL)
		{
			del->prev->next=del->next;
			del->next->prev=del->prev;
		}
		else if(del->prev==NULL)
		{
			if(del->next!=NULL)
			{
				list->head=del->next;
				del->next->prev=NULL;
			}
		}
		else if(del->next==NULL)
		{
			if(del->prev!=NULL)
			{
				list->tail=del->prev;
				del->prev->next=NULL;
			}
		}
		if(del->prev==NULL && del->next==NULL)
		{
			list->head=list->tail=NULL;
		}
		free(del);
		list->size--;
	}
}
node_t* search(list_t* list, int data)            // returns the pointer to the node with “data” field. Return NULL if not found.
{
	node_t* ser = list->head;
	while(ser!=NULL && ser->data!=data)
		ser=ser->next;
	return ser;
}
void delete_nodes(node_t* head) 
{
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}
void delete_list(list_t* list)                   // free all the contents of the linked list
{
	delete_nodes(list->head);
	free(list);
}
void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	node_t* it = list->head;
	if(it==NULL)
	{
		printf("Playlist Empty!\n");
		return;
	}
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}
queue_t* create_queue()                     // return a newly created empty queue
{
	queue_t* Q = (queue_t*) malloc(sizeof(queue_t));
	Q->list = create_list();
	Q->front = Q->list->head;
	Q->rear = Q->list->tail;
	Q->size = Q->list->size;
	return Q;
}
node_t* node_create(int data)
{
	node_t* newnode = (node_t*) malloc(sizeof(node_t));
	newnode->data= data;
	newnode->next=NULL;
	newnode->prev=NULL;
	return newnode;
}
void enqueue(queue_t* q, int data)         // insert data at the end of a queue
{
	node_t* newnode = node_create(data);
	if(q==NULL)
	{
		q = (queue_t *)malloc(sizeof(queue_t));
		q->front = q->rear = NULL;
	}
	if(q->front==NULL)
	{
		q->front=newnode;
		q->rear=newnode;
	}
	else
	{
		q->rear->next=newnode;
		newnode->prev=q->rear;
		q->rear=newnode;
	}
	q->size++;
}
int dequeue(queue_t* q) 	// return the data at the front of a queue and remove it. Return -1 if queue is empty
{
	int deletedval = -1;
	if(q->size!=0)
	{
		deletedval = q->front->data;
		node_t* temp = q->front;
		q->front=q->front->next;
		if(q->front!=NULL)
		{
			q->front->prev=NULL;
		}
		else
		{
			if(temp->prev==NULL)
				q->front=q->rear=NULL;
		}
		free(temp);
		q->size--;
	}
	return deletedval;
}
void que_disp(queue_t* q)
{
	if(q->size==0 || q==NULL)
	{
		printf("No Songs added to queue yet!\n");
		return;
	}
	else
	{
		node_t* temp=q->front;
		while(temp!=q->rear)
		{
			printf("%d ",temp->data);
			temp=temp->next;
		}
		printf("%d\n",temp->data);
	}
}
void delete_queue(queue_t* q) // empty the contents of the queue
{
	delete_list(q->list);
	free(q);
	q->size = 0;
}
playlist_t* create_playlist()                 // return a newly created doubly linked list
{
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}
void delete_playlist(playlist_t* playlist)    // delete the playlist
{
	delete_list(playlist->list);
	free(playlist);
}
music_queue_t* create_music_queue()           // return a newly created queue
{
	return create_queue();
}
void clear_music_queue(music_queue_t* q)      // clear the queue q
{	
	delete_queue(q);
}
void add_song(playlist_t* playlist, int song_id, int where) // add a song id to the end of the playlist
{
	node_t *temp = search(playlist->list, song_id);
	if(temp!=NULL)
		{
			printf("Entered Song ID is already added\n");
			return;
		}
	if(where==-1)
		insert_front(playlist->list,song_id);
	else if(where==-2)
		insert_back(playlist->list,song_id);
	else
	{
		temp = search(playlist->list, where);
		if(temp == NULL)
			printf("Song ID does not exist\n");
		else
		insert_after(playlist->list,song_id,where);
	}
	playlist->num_songs=playlist->list->size;
}
void delete_song(playlist_t* playlist, int song_id)       // remove song id from the playlist
{
	if(playlist->last_song!=NULL)
	{
		if(playlist->last_song->data==song_id)
		{
			playlist->last_song=NULL;	
		}
	}
	delete_node(playlist->list,song_id);
	playlist->num_songs=playlist->list->size;
}
song_t* search_song(playlist_t* playlist, int song_id) // return a pointer to the node where the song id is present in the playlist
{
	song_t* ser = search(playlist->list,song_id);
	return ser;
}
void search_and_play(playlist_t* playlist, int song_id) // play the song with given song_id from the list
{
	song_t* ser = search(playlist->list,song_id);
	if(ser!=NULL)
	{
		play_song(ser->data);
		playlist->last_song=ser;
	}
	else
	{
		printf("\n Song id not found \n");
	}
}
void play_next(playlist_t* playlist, music_queue_t* q) // play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if(playlist->num_songs!=0)
	{
		int ps;
		if(q->size!=0)
			ps=dequeue(q);
		else
		{
			if(playlist->last_song!=NULL)
			{
				if(playlist->last_song->next==NULL)
				{
					ps=playlist->list->head->data;
					playlist->last_song=playlist->list->head;
				}
				else
				{
					ps=playlist->last_song->next->data;
					playlist->last_song=playlist->last_song->next;
				}
			}
			else
			{
				ps=playlist->list->head->data;
				playlist->last_song=playlist->list->head;
			}
		}
		if(ps!=-1)
			play_song(ps);
	}
	else
	{
		int ps=-1;
		if(q->size!=0)
			ps=dequeue(q);
		if(ps!=-1)
			play_song(ps);
	}
}
void play_previous(playlist_t* playlist)       // play the previous song from the linked list
{
	if(playlist->num_songs!=0)
	{
		int ps;
		if(playlist->last_song!=NULL)
		{
			if(playlist->last_song->prev==NULL)
			{
				ps=playlist->list->tail->data;
				playlist->last_song=playlist->list->tail;
			}
			else
			{
				ps=playlist->last_song->prev->data;
				playlist->last_song=playlist->last_song->prev;
			}
		}
		else
		{
			ps=playlist->list->tail->data;
			playlist->last_song=playlist->list->tail;
		}
		play_song(ps);
	}
	else
		return;
}
void play_from_queue(music_queue_t* q)              // play a song from the queue
{
		int ps;
		if(q->size!=0)
			ps=dequeue(q);
		else
			return
		play_song(ps);
}
void insert_to_queue(music_queue_t* q, int song_id) // insert a song id to the queue
{
	enqueue(q,song_id);
}
void display_playlist(playlist_t* p)               // Displays the playlist
{
	display_list(p->list);
}
void play_song(int song_id)
{
	printf("Playing: %d\n", song_id);
}
void disp_queue(music_queue_t* q)
{
	que_disp(q);
}

int main()
{
	playlist_t *pl = create_playlist();
	list_t *l1 = create_list();
	pl->list = l1;
	pl->num_songs = 0;
	pl->last_song = NULL;
	queue_t *q = create_queue();
	int opt;
	int id, aid;
	do
	{
		printf("======================================\n");
		printf("\n Welcome to AAA Music Player \n");
		printf("Enter 1 to add song in front\n");
		printf("Enter 2 to add song in rear\n");
		printf("Enter 3 to add song after a given song\n");
		printf("Enter 4 to delete song\n");
		printf("Enter 5 to display playlist\n");
		printf("Enter 6 to add song to queue\n");
		printf("Enter 7 to play next song\n");
		printf("Enter 8 to play previous song\n");
		printf("Enter 9 to search and play a song\n");
		printf("Enter 10 to display queue\n");
		printf("Enter 11 to delete queue\n");
		printf("Enter any other number to exit\n");
		printf("======================================\n");
		printf("Enter your option\n");
		scanf("%d",&opt);
		switch(opt)
		{
		case 1:
			printf("Enter the song id to be entered\n");
			scanf("%d",&id);
			add_song(pl, id, -1);
			break;
		case 2:
			printf("Enter the song id to be entered\n");
			scanf("%d",&id);
			add_song(pl, id, -2);
			break;
		case 3:
			printf("Enter the song id to be entered\n");
			scanf("%d",&id);
			printf("Enter the song id after which u want the song to be inserted\n");
			scanf("%d",&aid);
			add_song(pl,id,aid);
			break;
		case 4:
			printf("Enter the song id to be deleted\n");
			scanf("%d",&id);
			delete_song(pl,id);
			break;
		case 5:
			display_playlist(pl);
			break;
		case 6:
			printf("Enter the song id to be entered\n");
			scanf("%d",&id);
			insert_to_queue(q,id);
			break;
		case 7:
			play_next(pl, q);
			break;
		case 8:
			play_previous(pl);
			break;
		case 9:
			printf("Enter the song id to be played\n");
			scanf("%d",&id);
			search_and_play(pl, id);
			break;
		case 10:
			disp_queue(q);
			break;
	    case 11:
	    	delete_queue(q);
			queue_t *q = create_queue();
			printf("Your Queue has been cleared succesfully!\n");
	    	break;
		}
	}while(opt>0&&opt<12);
	delete_playlist(pl);
	clear_music_queue(q);
	printf("\n Thank you for using AAA Music player \n");
}