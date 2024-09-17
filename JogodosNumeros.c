#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nickname[100];
    int score;
}Players;

FILE *fd;
Players player;
char fileName[] = "../iniciante.txt";
int mode = 1; 
int contVictory = 0;
int positionFile = 0;

void clearScreen();
void clearRanking();
void showMenu();
void showConfg();
void showInstructions();
void showDifficulty();
void showLifes(int lifes);
void showRanking();
void inputRanking();
void inputMatrix(int mode, int in, char sumUp[], char sumSide[], char matNum[][in], char matAws[][in]);
void printMatrix(int mode, int in, char sumUp[], char sumSide[], char matNum[][in]);
void difficulty();
void confg();
void game(int mode);
void inputCheck(int in, int matCheck[][in]);
int play(int in, char sumUp[], char sumSide[], char matNum[][in], char matAws[][in]);        

int main(void){
    char option = '0';
    clearScreen();
    printf("Bem vindo ao Jogo dos Numeros!\n\nInforme seu nickname: ");
    fgets(player.nickname, 100, stdin);
    while(option!='5'){
        showMenu();
        scanf("%c", &option);
        if(option=='1'){
            game(mode);
            if(contVictory==4){
                contVictory=0;
                positionFile=0;
                if(mode==1) mode=2;
                else if(mode==2 || mode==116 || mode==0) mode=3;
                else if(mode==3){
                    clearScreen();
                    printf("PARABENS!!! VOCE TERMINOU (ZEROU) O JOGO!\n\nAperte enter para voltar: ");
                    getchar();
                }
            }
        }
        if(option=='2'){
            confg();
        }
        if(option=='3'){
            showInstructions();
        }
        if(option=='4'){
            showRanking();
        }
    }
    clearScreen();
    fclose(fd);
    printf("Hasta la vista, %s\n\n", player.nickname);
    return 0;
}

void game(int mode){ 
    if(mode==1){
        strcpy(fileName, "../iniciante.txt");
        char sumUp[8], sumSide[8], matNum[4][4], matAws[4][4], in=4;
        inputMatrix(mode, in, sumUp, sumSide, matNum, matAws);
        int v = play(in, sumUp, sumSide, matNum, matAws);
        if(v==1){
            contVictory++;
            positionFile += 60;
        }
    }
    else if(mode==2 || mode==116 || mode==0){
        strcpy(fileName, "../intermediario.txt");
        char sumUp[12], sumSide[12], matNum[6][6], matAws[6][6], in=6;
        inputMatrix(mode, in, sumUp, sumSide, matNum, matAws);
        int v = play(in, sumUp, sumSide, matNum, matAws);
        if(v==1){
            contVictory++;
            positionFile += 112;
        }
    }
    else if(mode==3){
        strcpy(fileName, "../avancado.txt");
        char sumUp[14], sumSide[14], matNum[7][7], matAws[7][7], in=7;
        inputMatrix(mode, in, sumUp, sumSide, matNum, matAws);
        int v = play(in, sumUp, sumSide, matNum, matAws);
        if(v==1){
            contVictory++;
            positionFile += 144;
        }
    }
    return;
}

void inputMatrix(int mode, int in, char sumUp[], char sumSide[], char matNum[][in], char matAws[][in]){ 
    fd = fopen(fileName, "r");
    if(fd==NULL){
        printf("Erro ao abrir o arquivo!");
        return;
    }
    if(mode==1){
        char matrix[10][100];
        fseek(fd, positionFile, SEEK_SET);
        for(int i=0; i<10; i++){
            fgets(matrix[i], 100, fd);
        }
        int m=0;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                matNum[i][j] = matrix[m][j];
            }
            m++;
        }
        for(int i=0; i<8; i++){
            sumUp[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<8; i++){
            sumSide[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                matAws[i][j] = matrix[m][j];
            }
            m++;
        }
    }
    else if(mode==2 || mode==116 || mode==0){
        char matrix[14][100];
        fseek(fd, positionFile, SEEK_SET);
        for(int i=0; i<14; i++){
            fgets(matrix[i], 100, fd);
        }
        int m=0;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                matNum[i][j] = matrix[m][j];
            }
            m++;
        }
        for(int i=0; i<12; i++){
            sumUp[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<12; i++){
            sumSide[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                matAws[i][j] = matrix[m][j];
            }
            m++;
        }
    }
    else if(mode==3){
        char matrix[16][100];
        fseek(fd, positionFile, SEEK_SET);
        for(int i=0; i<16; i++){
            fgets(matrix[i], 100, fd);
        }

        int m=0;
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                matNum[i][j] = matrix[m][j];
            }
            m++;
        }
        for(int i=0; i<14; i++){
            sumUp[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<14; i++){
            sumSide[i] = matrix[m][i];
        }
        m++;
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                matAws[i][j] = matrix[m][j];
            }
            m++;
        }
    }
    fclose(fd);
    return;
}

void printMatrix(int mode, int in, char sumUp[], char sumSide[], char matNum[][in]){
    if(mode==1){
        printf("    %c%c %c%c %c%c %c%c\n", sumUp[0],sumUp[1],sumUp[2],sumUp[3],sumUp[4],sumUp[5],sumUp[6],sumUp[7]);
        printf("    -----------\n");
        printf("%c%c | %c  %c  %c  %c\n", sumSide[0],sumSide[1],matNum[0][0],matNum[0][1],matNum[0][2],matNum[0][3]);
        printf("%c%c | %c  %c  %c  %c\n", sumSide[2],sumSide[3],matNum[1][0],matNum[1][1],matNum[1][2],matNum[1][3]);
        printf("%c%c | %c  %c  %c  %c\n", sumSide[4],sumSide[5],matNum[2][0],matNum[2][1],matNum[2][2],matNum[2][3]);
        printf("%c%c | %c  %c  %c  %c\n\n", sumSide[6],sumSide[7],matNum[3][0],matNum[3][1],matNum[3][2],matNum[3][3]);
    }
    else if(mode==2 || mode==116 || mode==0){
        printf("    %c%c %c%c %c%c %c%c %c%c %c%c\n", sumUp[0],sumUp[1],sumUp[2],sumUp[3],sumUp[4],sumUp[5],sumUp[6],sumUp[7],sumUp[8],sumUp[9],sumUp[10],sumUp[11]);
        printf("    -----------------\n");
        printf("%c%c | %c  %c  %c  %c  %c  %c\n", sumSide[0],sumSide[1],matNum[0][0],matNum[0][1],matNum[0][2],matNum[0][3],matNum[0][4],matNum[0][5]);
        printf("%c%c | %c  %c  %c  %c  %c  %c\n", sumSide[2],sumSide[3],matNum[1][0],matNum[1][1],matNum[1][2],matNum[1][3],matNum[1][4],matNum[1][5]);
        printf("%c%c | %c  %c  %c  %c  %c  %c\n", sumSide[4],sumSide[5],matNum[2][0],matNum[2][1],matNum[2][2],matNum[2][3],matNum[2][4],matNum[2][5]);
        printf("%c%c | %c  %c  %c  %c  %c  %c\n", sumSide[6],sumSide[7],matNum[3][0],matNum[3][1],matNum[3][2],matNum[3][3],matNum[3][4],matNum[3][5]);
        printf("%c%c | %c  %c  %c  %c  %c  %c\n", sumSide[8],sumSide[9],matNum[4][0],matNum[4][1],matNum[4][2],matNum[4][3],matNum[4][4],matNum[4][5]);
        printf("%c%c | %c  %c  %c  %c  %c  %c\n\n", sumSide[10],sumSide[11],matNum[5][0],matNum[5][1],matNum[5][2],matNum[5][3],matNum[5][4],matNum[5][5]);
    }
    else if(mode==3){
        printf("    %c%c %c%c %c%c %c%c %c%c %c%c %c%c\n", sumUp[0],sumUp[1],sumUp[2],sumUp[3],sumUp[4],sumUp[5],sumUp[6],sumUp[7],sumUp[8],sumUp[9],sumUp[10],sumUp[11],sumUp[12],sumUp[13]);
        printf("    --------------------\n");
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[0],sumSide[1],matNum[0][0],matNum[0][1],matNum[0][2],matNum[0][3],matNum[0][4],matNum[0][5],matNum[0][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[2],sumSide[3],matNum[1][0],matNum[1][1],matNum[1][2],matNum[1][3],matNum[1][4],matNum[1][5],matNum[1][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[4],sumSide[5],matNum[2][0],matNum[2][1],matNum[2][2],matNum[2][3],matNum[2][4],matNum[2][5],matNum[2][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[6],sumSide[6],matNum[3][0],matNum[3][1],matNum[3][2],matNum[3][3],matNum[3][4],matNum[3][5],matNum[3][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[8],sumSide[9],matNum[4][0],matNum[4][1],matNum[4][2],matNum[4][3],matNum[4][4],matNum[4][5],matNum[4][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n", sumSide[10],sumSide[11],matNum[5][0],matNum[5][1],matNum[5][2],matNum[5][3],matNum[5][4],matNum[5][5],matNum[5][6]);
        printf("%c%c | %c  %c  %c  %c  %c  %c  %c\n\n", sumSide[12],sumSide[13],matNum[6][0],matNum[6][1],matNum[6][2],matNum[6][3],matNum[6][4],matNum[6][5],matNum[6][6]);
    }  
    return;
}

int play(int in, char sumUp[], char sumSide[], char matNum[][in], char matAws[][in]){
    int lifes=5, win=0;
    int matCheck[in][in];
    inputCheck(in, matCheck);
    while(win==0 && lifes!=0){
        clearScreen();
        int r, c, contWin=0;
        showLifes(lifes);
        printMatrix(mode, in, sumUp, sumSide, matNum);
        printf("Escolha uma linha e coluna para eliminar um numero: ");
        scanf("%d %d", &r, &c);
        r--; 
        c--;
        if(r>in-1 || c>in-1 || r<0 || c<0){
            printf("\nOs numero nao podem ser escolhidos!\n\nAperte enter para continuar: ");
            getchar();
            getchar();
        }
        else if(matCheck[r][c]==1){
            printf("\nO numero ja foi escolhido!\n\nAperte enter para continuar: ");
            getchar();
            getchar();
        }
        else{
            matCheck[r][c]=1;
            if(matAws[r][c]=='0'){
                printf("\nMuito bem!\n");
                matNum[r][c] = ' ';
                int contRow=0, contColumn=0;
                for(int j=0; j<in; j++){
                    if(matNum[r][j]!=' ' && matAws[r][j]=='1') contRow++;
                    if(matNum[r][j]==' ' && matAws[r][j]=='0') contRow++;
                }
                if(contRow==in){
                    printf("\nLinha %d foi concluida!\n", r+1);
                    sumSide[r*2]=' ';
                    sumSide[r*2+1]=' ';
                }
                for(int i=0; i<in; i++){
                    if(matNum[i][c]!=' ' && matAws[i][c]=='1') contColumn++;
                    if(matNum[i][c]==' ' && matAws[i][c]=='0') contColumn++;
                }
                if(contColumn==in){
                    printf("\nColuna %d foi concluida!\n", c+1);
                    sumUp[c*2]=' ';
                    sumUp[c*2+1]=' ';
                }
                for(int i=0, n=2*in; i<n; i++){
                    if(sumUp[i]==' ') contWin++;
                    if(sumSide[i]==' ') contWin++;
                }
                if(contWin==(4*in)){
                    clearScreen();
                    printf("Parabens!\n\nAperte enter para sair: ");
                    getchar();
                    getchar();
                    win=1;
                }
                else {
                    printf("\nAperte enter para continuar: ");
                    getchar();
                    getchar();  
                }
            }
            else if(matAws[r][c]=='1'){
                printf("\nOh nao!\n\nAperte enter para continuar: ");
                getchar();
                getchar(); 
                lifes--;
            }
        }
    }
    if(win==1){
        if(mode==1) player.score = 50;
        if(mode==2 || mode==116 || mode==0) player.score = 100;
        if(mode==3) player.score = 200;
        inputRanking();
        return 1;
    }
    else if(lifes==0){
        clearScreen();
        printf("Voce perdeu!\n\nAperte enter para sair: ");
        player.score=0;
        getchar();
        inputRanking();
        return 0;
    }
}

void showMenu(){
    clearScreen();
    printf("################################\n");
    printf("#			       #\n");
    printf("#     	Jogo dos Numeros       #\n");
    printf("#    			       #\n");
    printf("#       Jogar (1)	       #\n");
    printf("#     	Configuracoes (2)      #\n");
    printf("#     	Instrucoes (3)         #\n");
    printf("#     	Ranking (4)	       #\n");
    printf("#     	Sair (5)	       #\n");
    printf("#     			       #\n");
    printf("################################\n\n");
    printf("Escolha uma opcao: ");
    return;
}

void showConfg(){
    clearScreen();
    printf("################################\n");
    printf("#			       #\n");
    printf("#     	Configuracoes	       #\n");
    printf("#    			       #\n");
    printf("#       Zerar Ranking (1)      #\n");
    printf("#     	Dificuldade (2)        #\n");
    printf("#     	Sair (3)  	       #\n");
    printf("#     			       #\n");
    printf("################################\n\n");
    printf("Escolha uma opcao: ");
    return;
}

void showLifes(int lifes){
    printf("   ################   \n");
    printf("   #              #   \n");
    printf("   #    Fase %d    #   \n", contVictory+1);
    printf("   #              #   \n");
    printf("   #   Vidas: %d   #   \n", lifes);
    printf("   #              #   \n");
    printf("   ################   \n\n");
    return;
}

void showInstructions(){
    clearScreen();
    printf("################################################################################################\n");
    printf("#                                                                                              #\n");
    printf("#                                       Instrucoes:                                            #\n");
    printf("#  O jogador deve escolher as coordenadas de um numero da tabela a fim de elimina-lo,          #\n");
    printf("#  para que assim a soma da respectiva linha e coluna se iguale ao numero externo a tabela.    #\n");
    printf("#  O jogador possui 5 vidas independente da dificuldade (iniciante, intermediario, avancado)   #\n");
    printf("#  e caso ele escolha um numero errado, ele perde uma delas (caso perca todas, ele perde).     #\n");
    printf("#  Se o jogador escolher todos os numeros corretos, ele vence, ganha uma pontuacao             #\n");
    printf("#  baseada na dificuldade (50, 100, 200 pontos, respectivamente) e avanca para a proxima fase  #\n");
    printf("# (ou proxima dificuldade caso tenha completado todas as fases da dificuldade atual).          #\n");
    printf("#  O jogador zera o jogo ao concluir a ultima fase do nivel avancado.                          #\n");
    printf("#                                                                                              #\n");
    printf("#                                  Boa sorte e se divirta!                                     #\n");
    printf("#                                                                                              #\n");
    printf("################################################################################################\n\n");
    printf("Aperte enter para sair: ");
    getchar();
    getchar();
}

void showDifficulty(){
    clearScreen();
    printf("################################\n");
    printf("#			       #\n");
    printf("#     	 Dificuldade	       #\n");
    printf("#    			       #\n");
    printf("#        Iniciante (1)         #\n");
    printf("#     	 Intermediario (2)     #\n");
    printf("#     	 Avancado (3)	       #\n");
    printf("#     	 Sair (4)              #\n");
    printf("#     			       #\n");
    printf("################################\n\n");
    if(mode==1) printf("Dificuldade atual: Iniciante\n\n");
    else if(mode==2 || mode==116 || mode==0) printf("Dificuldade atual: Intermediario\n\n");
    else if(mode==3) printf("Dificuldade atual: Avancado\n\n");
    printf("Escolha uma opcao: ");
    return;
}

void clearRanking(){
    char a='!';
    getchar();
    while(a!='S' && a!='s' && a!='N' && a!='n'){
        clearScreen();
        printf("\nTem certeza? [S/N] ");
        scanf("%c", &a);
        if(a!='S' && a!='s' && a!='N' && a!='n'){
            printf("Digite uma opcao valida.");
            getchar();
            getchar();
        }
    }
    if(a=='S' || a=='s'){
        fd = fopen("ranking.bin", "wb");
        if(fd==NULL){
            printf("Erro ao criar arquivo!");
            return;
        }
        fclose(fd);
        printf("\nRanking foi zerado!\n\n");
    }
    else{
        printf("\nRanking mantido!\n\n");
    }
    printf("Aperte enter para continuar: ");
    getchar();
    getchar();
    return;
}

void confg(){
    int option = 0;
    while(option!=3){
        showConfg();
        scanf("%d", &option);
        if(option==1){
            clearRanking();
        }
        if(option==2){
            difficulty();
        }
    }
    return;
}

void difficulty(){
    char d = '0';
    while(d!='4'){
        showDifficulty();
        scanf("%c", &d);
        if(d=='1'){
            printf("\nModo iniciante definido!\n\n");
            mode=1;
            positionFile=0;
            contVictory=0;
            printf("Aperte enter para continuar: ");
            getchar();
            getchar();
        }
        if(d=='2'){
            printf("\nModo intermediario definido!\n\n");
            mode=2;
            positionFile=0;
            contVictory=0;
            printf("Aperte enter para continuar: ");
            getchar();
            getchar();
        }
        if(d=='3'){
            printf("\nModo avancado definido!\n\n");
            mode=3;
            positionFile=0;
            contVictory=0;
            printf("Aperte enter para continuar: ");
            getchar();
            getchar();
        }
    }
    return;
}

void showRanking(){
    getchar();
    clearScreen();
    fd = fopen("ranking.bin", "rb");
    if(fd==NULL){
        fd = fopen("ranking.bin", "wb");
    }
    char name[100][100];
    Players tmp[100];
    int i=0;
    printf("###############\n");
    printf("#             #\n");
    printf("#   Ranking   #\n");
    printf("#             #\n");
    printf("###############\n\n");
    while(fgets(name[i], 100, fd)!=0){
        i++;
    }
    for(int j=0; j<i; j++){
        if(j%2==0){
            strcpy(tmp[j/2].nickname,name[j]);
        }
        else{
            tmp[j/2].score = atoi(name[j]);
        }
    }
    for(int j=0, check=0; j<i && check==0; j+=2){
        check=1;
        for(int k=0; k<i-j-1; k++){
            if(tmp[k].score<tmp[k+1].score){
                check=0;
                Players aux = tmp[k];
                tmp[k] = tmp[k+1];
                tmp[k+1] = aux;
            }
        }
    }
    for(int j=0; j<(i/2); j++){
        if(j+1<10) printf("%d.%6d %s\n", j+1, tmp[j].score, tmp[j].nickname);
        else printf("%d.%5d %s\n", j+1, tmp[j].score, tmp[j].nickname);
    }
    printf("Aperte enter para sair: ");
    getchar();
    fclose(fd);
    return;
}

void inputRanking(){
    int new=1;
    char name[100];
    fd = fopen("ranking.bin", "r+b");
    if(fd==NULL){
        fd = fopen("ranking.bin", "wb");
    }
    while(fgets(name, 100, fd)!=0){
        if(strcmp(player.nickname,name)==0){
            new=0;
            char score[8];
            fgets(score, 8, fd);
            int tmp = atoi(score);
            tmp += player.score;
            for(int i=5; i>=0; i--){
                score[i]=tmp%10 + '0';
                tmp/=10;
            }
            fseek(fd, -sizeof(char)*7, SEEK_CUR);
            fputs(score, fd);
            break;
        }
    }
    if(new){
        fputs(player.nickname, fd);
        if(player.score==0) fputs("000000\n", fd);
        if(player.score==50) fputs("000050\n", fd);
        if(player.score==100) fputs("000100\n", fd);
        if(player.score==200) fputs("000200\n", fd);
    }
    fclose(fd);
    return;
}

void inputCheck(int in, int matCheck[][in]){
    for(int i=0; i<in; i++){
        for(int j=0; j<in; j++){
            matCheck[i][j]=0;
        }
    }
}

void clearScreen(){
    #ifdef _WIN32
        system("cls"); 
    #else 
        system("clear");
    #endif
}
