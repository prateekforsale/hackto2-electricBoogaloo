#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

struct alphabet   
{  
    char c;
    int num;     
};

struct Node {
    char c;
    int num;
	struct Node * next;
};

struct key_Pf   
{  
    char arr[5][5];    
};

typedef struct key_Pf kpf;
typedef struct alphabet alphabet;
typedef struct Node NODE;

NODE * createNewNode(char c, int num) {
	NODE * newNode = (NODE *) malloc (sizeof(NODE));
	newNode -> c = c;
	newNode -> num = num;
	return newNode;
}

NODE * initialize_Alphabet_cll(NODE * tail) {
    for (size_t i = 0; i < 26; i++)
    {
        NODE * newNode = createNewNode('z' - i, 26 - i);
        if (tail == NULL) {
            tail = newNode;
            newNode -> next = newNode;
        } else {
            newNode -> next = tail -> next;
            tail -> next = newNode;
        }
    }
	return tail;
}

void display(NODE * tail) {
	NODE * current = tail;
    printf("Tail: \n %c -> ", tail -> c);
    printf(" %d -> ", tail -> num);
    printf("\n");
	if (tail != NULL) {
		do {
			current = current -> next;
			printf(" %c : ", current -> c);
			printf(" %d -> ", current -> num);
            printf("   ");
		} while (current != tail); 
	}
}

alphabet *initialize_Alphabet(alphabet *arr)  
{  
    for (size_t i = 0; i < 26; i++)
    {
        arr[i].c = 'a' + i;
        arr[i].num = i + 1;
        printf("Alphabet: %c, Number: %d\n", arr[i].c, arr[i].num);
    }
    return arr;
}

char *randomize_Key_Vigenere(int inp, char *k)
{
    srand(time(0));
    printf("Random vigenere key: \n");
    for (size_t i = 0; i < inp; i++)
    {
        k[i] = 'a' + (rand()%(26));
        printf("%c", k[i]);
    }
    printf("\n");
    return k;
}

char *gen_key_Vig(int inp, char *k)
{
    printf("enter your key:\n");
    scanf("%s", k);
    return k;
}

void playfair(char k[], int len, kpf key, char text[], alphabet arr[])
{
    char trimmed[len];
    int j = 0, count = 0;

    for (size_t i = 0; i < len; i++)
    {
        
        if (k[i] == ' ')
        {
            count++;
            continue;
        }
        trimmed[j] = k[i];
        
        j++;
    }
    int newlen = len - count;
    
    if (newlen%2 == 0)
    {
        trimmed[newlen] = '\0';
    }
    else
    {
        trimmed[newlen] = 'z';
        trimmed[newlen + 1] = '\0';
    }

    for (size_t i = 0; i < newlen; i++)
    {
        if(trimmed[i] == trimmed[i - 1])
        {
            trimmed[i] = 'z';
        }
    }
    char dig[(int)((3/2)*newlen)];
    j = 0;

    int i;

    for (i = 0; trimmed[j] != '\0'; ++i)
    {
        if ((i)%3 == 0)
        {
            dig[i] = ' ';
            continue;
        }

        dig[i] = trimmed[j];
        //printf("%c\n", dig[i]);
        j++;
    }
    dig[i] = '\0';
    
    printf("digraphd: %s\n", dig);
    
    int dg1i,dg2i,dg1j,dg2j;
    j = 0;
    int h = 0;
    //char ciphertext[i];
    for (size_t k = 0; dig[j] != '\0' && j < i; ++k)
    {
        printf("\nDigraph chunk: %c%c  ", dig[j+1], dig[j+2]);
        
        for (size_t l = 0; l < 5; l++)
        {
            
            for (size_t m = 0; m < 5; m++)
            {
                
                
                if (key.arr[l][m] == dig[j + 1])
                {   //printf("FOUND 1 at: l = %ld m = %ld\n", l,m);
                    h++;
                    dg1i = l;
                    dg1j = m;
                }
                if (key.arr[l][m] == dig[j + 2])
                {
                    //printf("FOUND 2 at: l = %ld m = %ld\n", l,m);
                    h++;
                    dg2i = l; 
                    dg2j = m;
                }
            }
            if (h == 2)
            {
                h = 0;
                break;
            }
        }
        if (dg1j != dg2j &&  dg1i != dg2i)
        {
            printf("DIAGONALS: %c%c ", key.arr[dg1i][dg2j], key.arr[dg2i][dg1j]);
        }
        if (dg1i == dg2i) //same row
        {
            if (dg1j == 4)
            {
                dg1j = -1;
            }
            if (dg2j == 4)
            {
                dg2j = -1;
            }
            printf("SAME ROW: %c%c ", key.arr[dg1i][dg1j+1], key.arr[dg2i][dg2j+1]);

        }
        if (dg1j == dg2j) //same columns
        {
            if (dg1i == 4)
            {
                dg1i = -1;
            }
            if (dg2i == 4)
            {
                dg2i = -1;
            }
            printf("SAME COLUMN: %c%c ", key.arr[dg1i + 1][dg1j], key.arr[dg2i + 1][dg2j]);
        }

        j = j+3;
    }
    


}

int generate_Key_Caesar()
{
    //srand(time(0));
    //int k = (rand()%(26));
    int k;
    printf("Caesar key: \n");
    scanf("%d", &k);
    return (k);
}

int give_number(char c, alphabet *arr)  
{
    for (size_t i = 0; i < 26; i++)
    {
        if (arr[i].c == c)
        {
            return arr[i].num;
        }
    }  
    return -1;
}

void decrypt_Vigenere(char key[], char text[])
{
    int j = 0;
    int inp = strlen(key);
    printf("Decrypted Text:\n");
    for(size_t i = 0; text[i] != '\0'; i++)
    {
        printf("%c  ", text[i]);
        if (text[i] == ' ')
        {
            printf("\n");
            continue;
        }

        text[i] = (((text[i] - key[j] + 40)%26) + 'a');
        printf("%c\n", text[i]);

        ++j;
        if (j == inp)
        {
            j = 0;
        }
    }
}

void decrypt_Caesar(int key, char text[])
{
    printf("Decrypted Text:\n");
    for(size_t i = 0; text[i] != '\0'; i++)
    {
        printf("%c  ", text[i]);
        if (text[i] == ' ')
        {
            printf("\n");
            continue;
        }
        text[i] = 'a' + (text[i] - (char)key + 40)%26; 
        printf("%c\n", text[i]);  
    }
}


void vignere(char key[], char text[])
{
    int j = 0;
    int inp = strlen(key);
    printf("Ciphered Text:\n");
    for(size_t i = 0; text[i] != '\0'; i++)
    {
        printf("%c  ", text[i]);
        if (text[i] == ' ')
        {
            printf("\n");
            continue;
        }

        text[i] = ((key[j] + text[i])%26 + 'a');
        printf("%c\n", text[i]);

        ++j;
        if (j == inp)
        {
            j = 0;
        }
    }
    decrypt_Vigenere(key, text);
}

void caesar(int key, char text[])
{
    printf("Caesar cipher:\n");
    for(size_t i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            printf("\n");
            continue;
        }
        printf("%c  ", text[i]);
        text[i] = 'a' + (text[i] + (char)key)%26;
        printf("%c\n", text[i]);
    }
    decrypt_Caesar(key, text);
}

kpf initialize_5b5(alphabet *map)
{
    alphabet *temp = map;
    int inp;
    kpf ret;
    srand(time(0)); //
    printf("Initializing 5x5 key: \n");
    for(size_t i = 0; i < 5; i++)
    {
        
        for (size_t k = 0; k < 5; k++)
        {
            inp = rand() % 26;
            char c = temp[inp].c;
            if (c =='0' || c=='i')
            {
                --k;
                continue;
            }
            else if (c == 'j')
            {
                c = 'i';
                temp[8].c = '0';
            }
            ret.arr[i][k] = c;
            temp[inp].c = '0';
            printf("%c ", c);
        }
        printf("\n");
    }
    return ret;    
}

int main(int argc, char const *argv[])
{
    //NODE * abcll = NULL;
    
    alphabet *map;
    alphabet arr[26];
    map = initialize_Alphabet(arr);

    //abcll = initialize_Alphabet_cll(abcll);
    //display(abcll);

    //int inp;
    //printf("%s", "Enter length of a key. By default, we will generate a random key of your desired length:\n");
    //scanf("%d", &inp);

    

    FILE *fptr = fopen("process.txt", "r");
    if(fptr == NULL){
        printf("No file \n");
        return 0;
    }
    int size = 0;
    char c = fgetc(fptr);
    while(c != EOF){
        size++;
        c = fgetc(fptr);
    }
    fclose(fptr);
    fptr = fopen("process.txt", "r");
    if(fptr == NULL){
        printf("No file \n");
        return 0;
    }
    char* text = (char*)malloc(sizeof(char) * size);
    int n = 0;
    c = fgetc(fptr);
    while(c != EOF){
        text[n] = tolower(c);
        n++;
        c = fgetc(fptr);
    }
    fclose(fptr);

    int choice;
    printf("Choices 1-4 read from process.txt, 5-6 read from stdin \n");
    printf("Enter 1 to encrypt plaintext with caesar cipher\nEnter 2 to decrypt ciphertext with caesar cipher\nEnter 3 to encrypt plaintext with vigenere cipher\nEnter 4 to decrypt ciphertext with vigenere cipher: \nEnter 5 to encrypt with playfair cipher: \nEnter 6 to decrypt with playfair cipher: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: {
            int key_Cae = generate_Key_Caesar();
            caesar(key_Cae, text);
            break;
        }
        case 2: {
            int key;
            printf("Enter the key for offset: \n");
            scanf("%d", &key);
            decrypt_Caesar(key, text);
            break;
        }
        case 3: {
            char *key_Vig;
            //char k[inp];
        
            char k[1000]; 
            key_Vig = gen_key_Vig(1000,k);//randomize_Key_Vigenere(inp, k);


            
            //vignere(key_Vig, map, inp, text);
            vignere(key_Vig, text);
            break;
        }
        case 4: {
            int inpSize;
            printf("Enter a generous number for what you think is the size of your key: ");
            scanf("%d", &inpSize);
            char key[inpSize];
            printf("Enter your key: ");
            scanf("%s", key);
            decrypt_Vigenere(key, text);
        }
        case 5: {
            kpf keypf = initialize_5b5(map);   
            playfair(text, strlen(text),keypf, text, map);
            break;
        }
        case 6: {}
        default: {printf("Exiting..." ); exit(0);}
        }
    
    return 0;
}