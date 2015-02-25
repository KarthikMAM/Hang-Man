#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

struct node
{
	char clue[100];
	char word[20];
	struct node * next;
};

struct player_data
{
	char player1[20];
	char player2[20];
	int score1, score2;
	int n;
};

typedef struct player_data * ptrtoplayerdata;

typedef struct node * ptrtonode;
typedef struct node identonode;

ptrtonode create_empty_node(ptrtonode node)
{
	node = (ptrtonode)malloc(sizeof(identonode));
	node->next = NULL;
	return node;
}

ptrtonode create_data_node(ptrtonode node, char word[20], char clue[100])
{
	node = create_empty_node(node);
	strcpy(node->word, word);
	strcpy(node->clue, clue);
	return node;
}

void trim_last_character(char string_name[100])
{
	int i;
	for (i = 0; string_name[i] != '\n'; i++);
	string_name[i] = '\0';
}

int max_number_of_turns(char a[10])
{
    FILE * f = fopen(a,"r");
    int i=1;
    char b[100];
    while(!feof(f))
    {
        fgets(b,100,f);
        i++;
    }
    fclose(f);
    return i;
}

void create_data(ptrtonode t, FILE * f)
{
    fgets(t->clue, 100, f);
    trim_last_character(t->clue);
    fgets(t->word, 20, f);
    trim_last_character(t->word);
}

void create_dummy_word(char original_word[20], char new_word[20])
{
	int i;
	for (i = 0; original_word[i] != '\0'; i++)
	{
		if (original_word[i] == ' ')
		{
			new_word[i] = ' ';
		}
		else
		{
			new_word[i] = '_';
		}
	}
	new_word[i] = '\0';
}

int build_dummy_word(char original_word[20], char new_word[20], char c)
{
	int i, j = 1;
	for (i = 0; original_word[i] != '\0'; i++)
	{
		if (original_word[i] == c)
		{
			new_word[i] = c;
			j = 0;
		}
	}
	return j;
}

int check_remaining_turns(char original_word[20], char new_word[20], char c, int j)
{
	return j -= build_dummy_word(original_word, new_word, c);
}

int game_over_condition(char original_word[20], char new_word[20])
{
	if (!strcmp(original_word, new_word))
	{
		return 0;
	}
	return 1;
}

void color(int i)
{
    switch(i)
    {
        case 0 :    system("COLOR 9C");
                    break;
        case 1 :    system("COLOR 9C");
                    break;
        case 2 :    system("COLOR 9D");
                    break;
        case 3 :    system("COLOR 9D");
                    break;
        case 4 :    system("COLOR 9D");
                    break;
        case 5 :    system("COLOR 9E");
                    break;
        case 6 :    system("COLOR 9E");
                    break;
        case 7 :    system("COLOR 9A");
                    break;
        case 8 :    system("COLOR 9A");
                    break;
    }
}

int win_or_lose(int j, int i, char word[100])
{
	if (j == 0)
	{
		printf("\n\n\tSORRY YOUR ASSUMPTIONS WERE WRONG !!!");
		//printf("\n\n\tTHE CORRECT WORD IS %s", word);
		color(0);
	}
	if (!i)
	{
		printf("\n\n\tYOUR ASSUMPTION IS CORRECT !!!");
		printf("\n\n\tCONGRATS !!!");
		color(8);
	}
	if (i && j)
	{
		return 1;
	}
	return 0;
}

void escape_display(int i)
{
    printf("\n\n\n\n");
    switch(i%4)
    {
        case 0 :    printf("\t\t\t\\    /\n\t\t\t_\\  /_  CONGRATS GAME COMPLETED!!!!!\n");
                    break;
        case 1 :    printf("\t\t\t |  |\n\t\t\t_|  |_  CONGRATS GAME COMPLETED!!!!!\n");
                    break;
        case 2 :    printf("\t\t\t  /\\\n\t\t\t_/  \\_  CONGRATS GAME COMPLETED!!!!!\n");
                    printf("\a");
                    break;
        case 3 :    printf("\t\t\t |  |\n\t\t\t_|  |_  CONGRATS GAME COMPLETED!!!!!\n");
                    break;
    }
    _sleep(1000/7);
    system("CLS");

}

void display(int i)
{
    color(i);
	printf("\n\n\n\t###################################\n");
	printf("\t#                                 \n");
	printf("\t#                                 \n");
	printf("\t#");
	if (i <= 5)
	{
		printf("\t _______");
	}
	printf("\n\t#\t");
	if (i <= 6)
	{
		printf("|");
	}
	if (i <= 4)
	{
		printf("       |");
	}
	printf("\n\t#\t");
	if (i <= 6)
	{
		printf("|");
	}
	if (i <= 3)
	{
		printf("       %c",2);
	}
	printf("\n\t#\t");
	if (i <= 6)
	{
		printf("|");
	}
	if (i <= 2)
	{
		printf("      /");
	}
	if (i <= 1)
	{
		printf("|");
	}
	else
	{
		printf(" ");
	}
	if (i <= 2)
	{
		printf("\\");
	}
	printf("\n\t#\t");
	if (i <= 6)
	{
		printf("|");
	}
	if (i <= 1)
	{
		printf("       |");
	}
	printf("\n\t#\t");
	if (i <= 6)
	{
		printf("|");
	}
	if (i <= 0)
	{
		printf("      /");
		printf(" \\");
	}
	printf("\n\t#\t");
	if (i <= 7)
	{
		printf("|__________________\n\t#\t");
		printf("|                  |\n\t#\t");
		printf("|__________________|");
	}
	else
    {
        printf("\n\t#\t\n\t#\t");
    }
	printf("\n\t#\t\n\t###################################\n");
}

void display_credits(ptrtoplayerdata data)
{
    for(int i=0;i<19;i++)
    {
        printf("\n\n\n\n--------------------------------------------------------------------------------\n\n\t");
        printf("\n\n\tTHANK YOU %10s AND %10s FOR YOUR CO-OPERATION\n\n\t",data->player1,data->player2);
        if(i%4==0)
        {
            system("COLOR 9C");
            printf("\n\n\n\n\n");
            printf("\t\t\t\t#######################\n");
            printf("\t\t\t\t#   ______   ______   #\n");
            printf("\t\t\t\t#  |######| |######|  #\n");
            printf("\t\t\t\t#  |######| |######|  #\n");
            printf("\t\t\t\t#  |##### | | #####|  #\n");
            printf("\t\t\t\t#  |#### @| |@ ####|  #\n");
            printf("\t\t\t\t#  |##### | | #####|  #\n");
            printf("\t\t\t\t#  |######| |######|  #\n");
            printf("\t\t\t\t#  |######| |######|  #\n");
            printf("\t\t\t\t#  |______| |______|  #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#######################\n");
            _sleep(200);
        }

        if(i%4==1 || i%4==3)
        {
            system("COLOR 9E");
            printf("\n\n\n\n\n");
            printf("\t\t\t\t#######################\n");
            printf("\t\t\t\t#  |\\\\           //|  #\n");
            printf("\t\t\t\t#  |#\\\\         //#|  #\n");
            printf("\t\t\t\t#  |##\\\\       //##|  #\n");
            printf("\t\t\t\t#  |###\\\\     //###|  #\n");
            printf("\t\t\t\t#  |####|     |####|  #\n");
            printf("\t\t\t\t#  |####|     |####|  #\n");
            printf("\t\t\t\t#  |### |     | ###|  #\n");
            printf("\t\t\t\t#  |## @|     |@ ##|  #\n");
            printf("\t\t\t\t#  \\\\## |     | ##//  #\n");
            printf("\t\t\t\t#   \\\\##|     |##//   #\n");
            printf("\t\t\t\t#####\\\\#|#####|#//#####\n");
            printf("\t\t\t\t      \\\\|     |// \n");
        }
        if(i%4==2)
        {
            system("COLOR 9A");
            printf("\n\n\n\n\n");
            printf("\t\t\t\t#######################\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#    HANG MAN         #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#    BY               #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#    KARTHIK M A M    #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#    \a                 #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#                     #\n");
            printf("\t\t\t\t#######################\n");
            _sleep(300);
        }
        _sleep(700);
        if(i!=18)
            system("CLS");
    }
}

int ispresent(char c, char b[20])
{
	for (int i = 0; b[i] != '\0'; i++)
	{
		if (b[i] == c)
		{
			printf("\n\n\tTHE CHARACTER IS ALREADY PRESENT\n\n\t\a");
			return 1;
		}
	}
	return 0;
}

int is_valid_character(char c)
{
    if(c>='A' && c<='Z')
    {
        return 1;
    }
    else
    {
        printf("\n\n\tTHE CHARACTER IS NOT VALID\n\n\a");
        return 0;
    }
}

void display_assumptions(char a[20], char b[9])
{
	int i;
	printf("\n\n\tTHE ASSUMED WORD IS         : ");
	for (i = 0; a[i] != '\0'; i++)
	{
		printf("%c ", a[i]);
	}
	printf("\n\n\tTHE MIS-SPELT LETTERS ARE   : ");
	for (i = 0; b[i] != '\0'; i++)
	{
		printf("%c ", b[i]);
	}
}

void turn_display(ptrtoplayerdata data, int turn)
{
	if (turn == 0)
	{
		printf("\n\n\tPLAYER %10s", data->player1);
	}
	if (turn == 1)
	{
		printf("\n\n\tPLAYER %10s", data->player2);
	}
}

void leader_board(ptrtoplayerdata data, int turn)
{
	turn_display(data, turn);
	if (data->score1>data->score2)
	{
		printf("          WINNING : %10s ( %d POINTS )\n\n                                   LOSING  : %10s ( %d POINTS )", data->player1, data->score1, data->player2, data->score2);
	}
	if (data->score1<data->score2)
	{
		printf("          WINNING : %10s ( %d POINTS )\n\n                                   LOSING  : %10s ( %d POINTS )", data->player2, data->score2, data->player1, data->score1);
	}
	if (data->score1 == data->score2)
	{
		printf("          TIE     : %10s ( %d POINTS )\n\n                                   TIE     : %10s ( %d POINTS )", data->player2, data->score2, data->player1, data->score1);
	}
}

void check_winner(ptrtoplayerdata data)
{
	if (data->score1>data->score2)
	{
		printf("\n\n\tPLAYER %10s WINS %10s WITH %d POINTS BY A MARGIN OF %d", data->player1, data->player2,data->score1, data->score1 - data->score2);
	}
	if (data->score1<data->score2)
	{
		printf("\n\n\tPLAYER %10s WINS %10s WITH %d POINTS BY A MARGIN OF %d", data->player2, data->player1,data->score2, data->score2 - data->score1);
	}
	if (data->score1 == data->score2)
	{
		printf("\n\n\tPLAYERS %10s AND %10s TIE EACHOTHER WITH %d POINTS EACH", data->player1, data->player2, data->score1);
	}
}

void create_log(ptrtoplayerdata data)
{
    FILE *f = fopen("Log.txt","a");
    fprintf(f,"\n| %10s | %5d | %10s | %5d | %5d |",data->player1, data->score1, data->player2, data->score2,data->n);
	if (data->score1>data->score2)
	{
		fprintf(f," WINNER %10s |\n",data->player1);
	}
	if (data->score1<data->score2)
	{
		fprintf(f," WINNER %10s |\n",data->player2);
	}
	if (data->score1 == data->score2)
	{
		fprintf(f,"       TIED   GAME |\n");
	}
    fprintf(f,"-----------------------------------------------------------------------");
	fclose(f);
}

void display_log()
{
    char A[100];
    system("CLS");
    FILE *f=fopen("Log.txt","r");
    printf("\n\n   YOUR ACTIVITES SO FAR");
    while(!feof(f))
    {
        fgets(A,100,f);
        printf("   ");
        puts(A);
        printf("");
    }
    fclose(f);
}

ptrtoplayerdata create_player_data(ptrtoplayerdata data,char a[10])
{
	printf("\n\n\n\n--------------------------------------------------------------------------------");
	data = (ptrtoplayerdata)malloc(sizeof(struct player_data));
	printf("\n\n\tENTER THE NAMES OF THE PLAYERS AND THE MAX NUMBER OF TURNS PER PLAYER");
	printf("\n\n\tPLAYER 1                                           : ");
	scanf("%s", data->player1);
	printf("\n\n\tPLAYER 2                                           : ");
	scanf("%s", data->player2);
	printf("\n\n\tENTER THE NUMBER OF TURNS PER PLAYER ( MAX : %2d )  : ", max_number_of_turns(a) / 4);
	scanf("%d", &data->n);
	data->score2 = 0;
	data->score1 = 0;
	printf("\n\n\n\n--------------------------------------------------------------------------------");
	return data;
}

void file_chooser(char a[10])
{
    char chooser='1',maximum_no_of_files='1';
    FILE *CH = fopen("file_selector.txt","r");
    fscanf(CH,"%c\t",&maximum_no_of_files);
    fscanf(CH,"%c\t",&chooser);
    fclose(CH);
    CH = fopen("file_selector.txt","w");
    fprintf(CH,"%c\t",maximum_no_of_files);
    if(chooser+1<=maximum_no_of_files)
        fprintf(CH,"%c",chooser+1);
    else
        fprintf(CH,"%d",1);
    strcpy(a,"data .txt");
    a[4]=chooser;
    fclose(CH);
}

int main()
{
    system("TITLE HANG MAN by KARTHIK M A M");
    system("COLOR 9A");
	system("CLS");
	char a[10];
	file_chooser(a);
    FILE * f = fopen(a,"r");
	ptrtoplayerdata data = create_player_data(data,a);
    ptrtonode temp = create_empty_node(temp);
	for (int i = 0; i<(data->n) * 2; i++)
	{
		char c;
		create_data(temp,f);
		char a[20], b[9];
		create_dummy_word(temp->word, a);
		create_dummy_word("12345678", b);
		int j = 8;
		while (win_or_lose(j, game_over_condition(temp->word, a), temp->word))
		{
		x:
            system("CLS");
			printf("\n\n\n\n--------------------------------------------------------------------------------");
			leader_board(data, i % 2);
			display(j);
			printf("\n\n\t\tCLUE : ");
			puts(temp->clue);
			display_assumptions(a, b);
			printf("\n\n\tENTER A CHARACTER\t    : ");
			c = getch();
			if (c >= 'a' && c<='z')
			{
				c = c - 32;
			}
			printf("%c", c);
			if (is_valid_character(c) && !ispresent(c, b) && !ispresent(c, a))
			{
				int k = check_remaining_turns(temp->word, a, c, j);
				if (k<j)
				{
					int l;
					for (l = 0; b[l] != '_'; l++);
					b[l] = c;
					printf("\a");
				}
				j = k;
			}
			else
			{
			    printf("\n\n\t");
			    system("PAUSE");
				goto x;
			}
		}
		system("CLS");
        int m=0;
        system("COLOR 9A");
		HAPPY_LABEL:
		printf("\n\n\n\n--------------------------------------------------------------------------------");
		display_assumptions(a, b);
		display(j);
		printf("\n\n\tTHE CORRECT WORD IS         : %s",temp->word);
		turn_display(data, i % 2);
		if (i % 2 == 0 && m==0)
		{
			data->score1 += j;
			color(j);
			printf(" SCORE FOR THIS TURN : %d", j);
		}
		else if(m==0)
		{
			data->score2 += j;
			color(j);
			printf(" SCORE FOR THIS TURN : %d", j);
		}
		if(j)
        {
            printf("\n\n\tYOUR ASSUMPTION WAS CORRECT....I AM SAVED!!!");
            for(;m<31;)
            {
                if(m%2==0)
                {
                    printf("\n\n");
                }
                printf("\n\n\n\t\t\t\t %C\n",2);
                if(m%2==0)
                    printf("\t\t\t\t\\|/\n");
                else
                    printf("\t\t\t\t/|\\\n");
                printf("\t\t\t\t |\n");
                if(m%2!=0)
                {
                    printf("\t\t\t\t/ \\\n\n");
                }
                else
                {
                    printf("\t\t\t\t| |");
                }
                m++;
                if(m!=31)
                {
                    _sleep(200);
                    system("CLS");
                    goto HAPPY_LABEL;
                }
            }
        }
        else
        {
            printf("\n\n\tYOUR ASSUMTION WAS WRONG....I AM DEAD!!!\n");
            for(;m<31;)
            {
                printf("\n\n\n\n\t");
                for(int h=0;h<=m;h++)
                {
                    printf(" ");
                }
                printf("  o ======\n\t");
                for(int h=0;h<=m;h++)
                {
                    printf(" ");
                }
                printf(" ----------\n\t");
                for(int h=0;h<=m;h++)
                {
                    printf(" ");
                }
                printf("|  CORPSE  |\n\t");
                for(int h=0;h<=m;h++)
                {
                    printf(" ");
                }
                printf(" ----------\n\t");
                m++;
                if(m!=31)
                {
                    _sleep(200);
                    system("CLS");
                    goto HAPPY_LABEL;
                }
            }
        }
		printf("\n\n\n\n--------------------------------------------------------------------------------\n\n\t");
        system("PAUSE");
	}
	system("CLS");
    printf("\n\n\n\n--------------------------------------------------------------------------------");
    system("COLOR 9A");
    check_winner(data);
    printf("\n");
    create_log(data);
	printf("\n\n\tDisplay History (Y/N) : ");
	char op = getch();
	printf("%c",op);
	if(op=='y' || op=='Y')
	{
	    display_log();
	}
	printf("\n\n\tDO YOU WANT TO CLEAR HISTORY (Y/N) : ");
	op = getch();
	printf("%c",op);
	if(op=='y' || op=='Y')
	{
	    FILE * CLEAR = fopen("Log.txt","w");
	    fprintf(CLEAR,"\n-----------------------------------------------------------------------\n|   PLAYER 1 | SCORE |   PLAYER 2 | SCORE | TURNS |   GAME STATISTICS |\n-----------------------------------------------------------------------");
	    fclose(f);
	}
	printf("\n\n\n\n\t");
	system("PAUSE");
	system("CLS");
    for(int i=0;i<50;i++)
    {
        printf("\n\n\n\n--------------------------------------------------------------------------------");
        //printf("\n\n\tBy KARTHIK M A M.......\n\n\tHope Love It..\n\n\t\tLive It..\n\n\t\t\tFeel It..\n\n\t\t\t\tCause It's Here..\n\n\t\t\t\t\tTechnology Is Here..");
        printf("\n\n\t\t\t\t\t(c) KARTHIK M A M");
        escape_display(i);
    }
    display_credits(data);
    printf("\n\n\t");
    system("PAUSE");
    _sleep(500);
	fclose(f);
	return 0;
}

