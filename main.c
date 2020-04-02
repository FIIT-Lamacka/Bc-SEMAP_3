#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reset(int *palindrome_count,char **palindrome, int *longest){
    /*NA TO ABY PROGRAM FUNGOVAL SA MUSI PRI KAZDOM NOVOM STRINGU RESETOVAT PAMAT A ZNULOVAT HODNOTY
    TUTO FUNKCKIU POUZIVAM AJ NA UVOLNENIE DYNAMICKEJ PAMETE PRI KONCI PROGRAMU
    */

    int i;
    for(i=0;i<*palindrome_count;i++)
            free(palindrome[i]);
        *longest=0;
        *palindrome_count=0;
}
int is_palindrome(char input[]){
    int i,strlen_input = strlen(input);

    for(i=0;i<strlen_input;i++){
        if(input[i]!=input[strlen_input-1-i])
            return 0;
    }
    return 1;
}
void left_dominant(char input[]){
    char copy_input[strlen(input)+2];
    int i,j;



    for(i=0;i<=strlen(input);i++){
        copy_input[i]=input[i];
    }

    for(i=0;i<strlen(copy_input);i++){
        if(copy_input[i]!=copy_input[strlen(copy_input)-1-i]){
            for(j=strlen(input);j>=strlen(copy_input)-1-i;j--){
                copy_input[j+1]=copy_input[j];
            }
            copy_input[strlen(copy_input)-1-i]=copy_input[i];
            break;
        }
    }
    if(is_palindrome(copy_input)){
        printf("%s",copy_input);
        return;
    }

    printf("%s",copy_input);

}
void right_dominant(char input[]){
   char copy_input[strlen(input)+2];
    int i;

    if(is_palindrome(input)){
        printf("%s",input);
        return;
    }

    for(i=0;i<=strlen(input);i++){
        copy_input[i]=input[i];
    }


    printf("%s",copy_input);
}
int main()
{
    char input[1001];
    int input_len;

    while(fgets(input,1000,stdin)!=NULL){
        if(input[0]=='\0'){
            return 0;
        }
        input_len = strlen(input);
        input[input_len-1]='\0'; //Vyradenie \n z pola
        input_len--;

        if(is_palindrome(input)){
            printf("Povodne slovo: %s, Pocet uprav:0\n",input);
            continue;
        }
        left_dominant(input);
        //right_dominant(input);








    }
}
