#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_WORD 100000
char *lowerString(char *str);
int checkProperNoun(char *str, int checkDot);
void swapStr(char *str1, char *str2);
void swapInt(int *a, int *b);
int main()
{
  char *str1[MAX_WORD], *str2[10000], *lineNumber[MAX_WORD], str[100], str3[100], str4[100];
  int count[MAX_WORD];
  int i,j,k, l1,l2, check1, check2, checkDot, lineN = 1;
  char c1, c2, c3;
  // Cap phat bo nho cho str1, str2, lineNumber;
  for(i=0;i<MAX_WORD;i++){
    str1[i] = malloc(sizeof(char)*100);
    str2[i] = malloc(sizeof(char)*100);
    lineNumber[i] = malloc(sizeof(char)*10000);
  }

  for(i=0;i<MAX_WORD;i++){
    count[i] = 1;
  }
    FILE *f1, *f2;
    // Mo 2 file van ban
      f1 = fopen("alice30.txt", "r");
      f2 = fopen("stopw.txt", "r");
      if (f1 == NULL || f2 == NULL){
        printf("Ko mo duoc file");
        return 0;
      }
      i = 0;
    // Luu cac tu doc duoc tu stopw.txt vao str2
    while(fscanf(f2,"%s", str) != EOF){
      strcpy(str2[i], str);
      i++;
    }
    l2 = i;
    // doc tung ki tu 1 cua file alice30.txt
    j = 0;
    i = 0;
    checkDot = 0;
    lineN = 1;
    while(1){
      c2 = fgetc(f1);
      c3 = fgetc(f1);
      if(c2 == '\n') lineN++;
      
      if(c2>= 'a' && c2 <= 'z' || c2>= 'A' && c2 <= 'Z' || c2 == '\'' || c2 == '-' ){ // doc cac ki tu trong 1 tu
        if(c2 == '\'' || c2 == '-' ){
          if((c1>= 'a' && c1 <= 'z' || c1>= 'A' && c1 <= 'Z')  && (c3>= 'a' && c3 <= 'z' || c3>= 'A' && c3 <= 'Z')){
            str[j] = c2;
            j++;
          } 
        } else{
          str[j] = c2;
          j++;
        }
      } else{
        str[j] = '\0';
          if(strcmp(str, "") != 0){
            check1 = 0; // kiem tra xem da co trong str1 hay chua
            check2 = 0;// kiem tra xem str co trong file stopw.txt hay ko
            strcpy(str4, str);
            lowerString(str4);
            for(k=0;k<l2;k++){
              if(strcmp(str2[k], str4) == 0) check2++;
            }

            // if(checkDot == 1){
            //   printf("Tai day checkDot = 1 %s\n", str );
            // } else{
            //   printf("Tai day checkDot = 0 %s\n", str);
            // }

            // if(strcmp(str, "CNN") == 0){
            //     printf("CNN checkDot %d\n", checkDot);
            //   }
            
            //printf("check2 = %d\n", check2);
            if( check2 == 0  && checkProperNoun(str,checkDot) == 0){// neu khong co trong stopw.txt va khong la danh tu rieng
              checkDot = 0;
              
              lowerString(str);
              for(k=0;k<i;k++){
                if(strcmp(str1[k], str) == 0) {// neu da xuat hien trong str1
                  check1++;
                  count[k]++;
                  sprintf(str3, "%d", lineN);
                  strcat(lineNumber[k], ", ");// noi so dong vao lineNumber
                  strcat(lineNumber[k], str3);
                  j = 0;
                }
              }
              if(check1 == 0){// neu chua xuat hien trong str1
                strcpy(str1[i], str);// copy vao str1[i]
                sprintf(str3, "%d", lineN);
                strcat(lineNumber[i], ", ");// noi so dong vao lineNumber
                strcat(lineNumber[i], str3);
                j=0;
                i++;
              }
          
            } else{
              j = 0;
              
            }
            checkDot = 0;

          }
      } 

      
      if(feof(f1)) {
        
        break;
      }
      
      // printf("%c", c2);
      if(fseek(f1, -1, SEEK_CUR) != 0){
        printf("khong lui duoc con tro");
        
        break;
      }
      c1 = c2;

      if(c2 == '.' || c2 == '!' || c2 == ':' || c2 == '?' || c2 == ';' ){ // neu doc duoc cac ki tu ket thuc cau thi danh dau lai 
        checkDot = 1;
        //printf(" C2 = %c c3 = %c\n", c2, c3);
      }

      
    }
    l1 = i;
    int min = 0;
    for(i=0;i<l1-1;i++){
      min = i;
      for(j=i+1;j<l1;j++){
        if(strcmp(str1[j], str1[min]) < 0){
          min = j;
        }
      }
      swapStr(str1[i], str1[min]);
      swapStr(lineNumber[i], lineNumber[min]);
      swapInt(&count[i], &count[min]);
    }

    for(i=0;i<l1;i++){
      printf("%s, %d%s\n", str1[i], count[i], lineNumber[i]);
    }

}

char *lowerString(char *str){
    //int l = strlen(str);
    for(int i=0; str[i]!='\0'; i++)
    {
        if(str[i]>='A' && str[i]<='Z')
        {
            str[i] = str[i] + 32;
        }
    }
    //str[l] = '\0';
    return str;
}





void swapStr(char *str1, char *str2){
  char *str3= malloc(10000 * sizeof(char));
  strcpy(str3, str1);
  strcpy(str1, str2);
  strcpy(str2, str3);
}

void swapInt(int* a, int* b)
{
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
}

int checkProperNoun(char *str, int checkDot){
  if(str[0] >= 'A' && str[0] <= 'Z' && checkDot == 0) return 1;
  else return 0;
}