
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

#define MENU_SIZE 4 // 메뉴 항목의 수 증가
#define SIZE 40

#define MAX_PLACES 3
#define NAME_SIZE 50
#define REVIEW_SIZE 256
#define PASSWORD_SIZE 5
#define PASSWORD_FILE "password.txt"


int y2 = 5;
int i;
int number;
int number2;
int test; //민호

typedef struct {
    int x;
    int y;
    int x1, x2;
    int y1, y2;
} Coordinate;

////////////////////////



//////////////////////////////////////////////
//////////////////////////////////////
////////////////////////////////////////////
void allprint(void);
void printOptimalPath(int graph[SIZE][SIZE], Coordinate path[], int steps, Coordinate start, Coordinate end);
int dijkstra(int graph[SIZE][SIZE], Coordinate start, Coordinate end, Coordinate path[]);
void allreview(const char* filename);

void initializeGraphFromFile(const char* filename, int graph[SIZE][SIZE]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (fscanf(file, "%d", &graph[i][j]) != 1) {
                fprintf(stderr, "Error reading file\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
}

int letme(void) {
    int graph[SIZE][SIZE];
    // 그래프 파일에서 초기화
    initializeGraphFromFile("graph.txt", graph);

    system("mode con: cols=100 lines=200");

    // 시작 좌표 (0,20)
    Coordinate start = { 0, 20 };


    Coordinate end;
    if (number2 == 1) {
        end.x = 8;
        end.y = 28;
    }
    else if (number2 == 2) {
        end.x = 13;
        end.y = 13;
    }
    else if (number2 == 3) {
        end.x = 25;
        end.y = 8;
    }
    else if (number2 == 4) {
        end.x = 23;
        end.y = 14;
    }
    else if (number2 == 5) {
        end.x = 23;
        end.y = 31;
    }
    else if (number2 == 6) {
        end.x = 36;
        end.y = 36;
    }
    else if (number2 == 7) {
        end.x = 3;
        end.y = 9;
    }
    else {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 최단 거리를 저장할 path 배열 선언
    Coordinate path[SIZE * SIZE];
    // 다익스트라 알고리즘 호출 및 결과 출력
    int steps = dijkstra(graph, start, end, path);
    printOptimalPath(graph, path, steps, start, end); // 최적의 경로 출력

    return 0;
}



void setCursorColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    cursorInfo.dwSize = 100; // 커서 크기 조절
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    SetConsoleTextAttribute(hConsole, color);
}


// 그래프 초기화 함수
void initGraph(int weights[SIZE][SIZE], int graph[SIZE][SIZE]) {
    // 주어진 배열로 그래프 초기화
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            graph[i][j] = weights[i][j];
        }
    }
}

// 다익스트라 알고리즘 함수
int dijkstra(int graph[SIZE][SIZE], Coordinate start, Coordinate end, Coordinate* path) {
    // 시작 지점의 거리를 무한대로 초기화
    int distance[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            distance[i][j] = INT_MAX;
        }
    }

    // 시작 지점의 거리는 0으로 초기화
    distance[start.x][start.y] = 0;


    // 방문 여부를 나타내는 배열
    bool visited[SIZE][SIZE] = { false };

    // 이전 노드를 저장하는 배열
    Coordinate previous[SIZE][SIZE];

    // 다익스트라 알고리즘 수행
    for (int count = 0; count < SIZE * SIZE; ++count) {
        // 최소 거리를 가진 노드를 찾음
        int minDistance = INT_MAX;
        Coordinate minNode;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (!visited[i][j] && distance[i][j] < minDistance) {
                    minDistance = distance[i][j];
                    minNode.x = i;
                    minNode.y = j;
                }
            }
        }

        // 최소 거리를 가진 노드를 방문함
        visited[minNode.x][minNode.y] = true;

        // 인접한 노드들의 거리를 업데이트함
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = minNode.x + i;
                int ny = minNode.y + j;
                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                    int newDistance = distance[minNode.x][minNode.y] + graph[nx][ny];
                    if (newDistance < distance[nx][ny]) {
                        distance[nx][ny] = newDistance;
                        previous[nx][ny] = minNode;
                    }
                }
            }
        }
    }

    // 목표 지점까지의 최단 거리 출력
    printf("걸리는 시간: %d분\n", distance[end.x][end.y] % 13);
    if (number2 == 5) {
        printf("MIX파스타 가는 길입니다.");
    }
    else if (number2 == 7) {
        printf("고래총각 가는 길입니다.");
    }
    else
        printf("오류");

    // 경로 추적
    int steps = 0;
    Coordinate current = end;
    while (!(current.x == start.x && current.y == start.y)) {
        path[steps++] = current;
        current = previous[current.x][current.y];
    }
    path[steps++] = start;

    // 경로 역순으로 정렬
    for (int i = 0; i < steps / 2; ++i) {
        Coordinate temp = path[i];
        path[i] = path[steps - i - 1];
        path[steps - i - 1] = temp;
    }

    return steps; // 최단 거리의 단계 수 반환
}

// 최적의 경로 출력 함수
void printOptimalPath(int graph[SIZE][SIZE], Coordinate* path, int steps, Coordinate start, Coordinate end) {
    // 시작 좌표와 도착 좌표를 기준으로 경로 출력
    //system("cls");
    printf("\n");
    setCursorColor(9);
    printf("심야식당 : ■\t");
    setCursorColor(2);
    printf("탁구 : ■\t");
    setCursorColor(4);
    printf("서원 빈대떡 : ■\t");
    setCursorColor(5);
    printf("또또와 : ■\n");
    setCursorColor(6);
    printf("이디야 : ■\t");
    setCursorColor(8);
    printf("MIX파스타 : ■\t");
    setCursorColor(11);
    printf("고래총각 : ■\n");


    for (int i = 0; i < SIZE; ++i) {
        //Sleep(100);
        for (int j = 0; j < SIZE; ++j) {

            bool isPath = false;
            bool isPath2 = true;
            for (int k = 0; k < steps; ++k) {
                if (path[k].x == i && path[k].y == j) {
                    isPath = true;
                    break;
                }


            }
            if (isPath) {


                if (i == 0 && j == 20) {
                    printf("☆"); // 시작 좌표
                }

                else if (i == end.x && j == end.y) {
                    setCursorColor(7);
                    printf("★"); // 도착 좌표
                }

                else {
                    setCursorColor(7);
                    printf("□"); // 가중치 출력
                }

            }


            else if ((i == 8) && (j == 28)) //1
                printf("☆");
            else if ((i == 13) && (j == 13)) //2
                printf("☆");
            else if ((i == 25) && (j == 8)) //3
                printf("☆");
            else if ((i == 23) && (j == 14)) //4
                printf("☆");
            else if ((i == 23) && (j == 31)) //5
                printf("☆");
            else if ((i == 36) && (j == 36)) //6
                printf("☆");
            else if ((i == 3) && (j == 9)) //7
                printf("☆");


            else if ((i == 16) && (j > 1 && j < 17)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((j == 17) && (i > -1 && i < 17)) {
                setCursorColor(7);
                printf("▩");
            }
            // ┘모양
            else if ((i == 20) && (j > -1 && j < 4)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((i == 20) && (j > 5 && j < 17)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((j == 17) && (i > 19 && i < 41)) {
                setCursorColor(7);
                printf("▩");
            }
            // ┐ 모양

            else if ((i == 16) && (j > 24 && j < 31)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((i == 16) && (j > 32 && j < 40)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((j == 24) && (i > -1 && i < 17)) {
                setCursorColor(7);
                printf("▩");
            }


            else if ((i == 20) && (j > 24 && j < 40)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((j == 24) && (i > 19 && i < 32)) {
                setCursorColor(7);
                printf("▩");
            }
            else if ((j == 24) && (i > 33 && i < 40)) {
                setCursorColor(7);
                printf("▩");
            }




            else if ((i > 5 && i < 11) && (j > 25 && j < 31)) {//1  중간숫자 

                setCursorColor(2); //녹색
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 10 && i < 16) && (j > 10 && j < 16)) {//2

                setCursorColor(4); //빨강
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 22 && i < 28) && (j > 5 && j < 11)) {//3

                setCursorColor(5); //자주
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 20 && i < 26) && (j > 11 && j < 17)) {//4

                setCursorColor(6); //노랑
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 20 && i < 26) && (j > 28 && j < 34)) {//5

                setCursorColor(8); //회색
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 33 && i < 39) && (j > 33 && j < 39)) {//6

                setCursorColor(9); //연한 파랑
                printf("■"); // 가면 안되는 곳

            }
            else if ((i > 0 && i < 6) && (j > 6 && j < 12)) {//7

                setCursorColor(11); //연한 청록
                printf("■"); // 가면 안되는 곳

            }


            else {
                setCursorColor(7);
                printf("■"); // 경로가 아닌 다른 좌표

            }
        }
        printf("\n");
    }
}




//////////////////////////////
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printBOX(void) {
    int i, y = 0;
    gotoxy(0, y);
    printf("┌");
    for (i = 0; i < 60; i++)
        printf("─");
    printf("┐");
    for (i = 1; i <= 20; i++)
    {
        gotoxy(0, ++y);
        printf("│%60s│", " ");
    }
    gotoxy(0, ++y);
    printf("└");
    for (i = 0; i < 60; i++)
        printf("─");
    printf("┘");
    gotoxy(21, 3);
    printf("서원인 인싸 프로젝트");
}
void printBOX2(void) {
    system("cls");
    int i, y = 0;
    gotoxy(0, y);
    printf("┌");
    for (i = 0; i < 80; i++)
        printf("─");
    printf("┐");
    for (i = 1; i <= 10; i++)
    {
        gotoxy(0, ++y);
        printf("│%80s│", " ");
    }
    gotoxy(0, ++y);
    printf("└");
    for (i = 0; i < 80; i++)
        printf("─");
    printf("┘");

}

void printMiniBox(void) {

    gotoxy(10, y2++); //y2의 초기값 5
    printf("┌");
    for (i = 0; i < 40; i++)
        printf("─");
    printf("┐\n");
    gotoxy(10, y2++);
    printf("│%40s│", " ");
    gotoxy(10, y2++);
    printf("└");
    for (i = 0; i < 40; i++)
        printf("─");
    printf("┘");

}

void menu1(void) {

    printBOX();
    printMiniBox();
    printMiniBox();
    printMiniBox();
    printMiniBox();
    printMiniBox();
    gotoxy(28, 6);
    printf("1. 먹거리");
    gotoxy(28, 9);
    printf("2. 놀거리");
    gotoxy(28, 12);
    printf("3. 볼거리");
    gotoxy(28, 15);
    printf("4. 전체 출력");
    gotoxy(28, 18);
    printf("5. 관리자 로그인");
}
void menu2(void) {
    // char p;

    y2 = 5;
    printBOX();
    printMiniBox();
    printMiniBox();
    printMiniBox();
    gotoxy(28, 6);
    printf("1. MIX파스타");
    gotoxy(28, 9);
    printf("2. 고래총각");
    gotoxy(28, 12);
    printf("3. 임마누엘");
}

void menu3(void) {
    y2 = 5;
    printBOX();
    printMiniBox();
    printMiniBox();
    gotoxy(28, 6);
    printf("1. 가는 길");
    gotoxy(28, 9);
    printf("2. 리뷰");

}


//////////////////////////////////
/////////////////////////////////////////////////
//////////////////////////////////////////
// 가게 이름과 리뷰를 담을 구조체 정의
typedef struct {
    char name[NAME_SIZE];
    char review[REVIEW_SIZE];
    int popularity;
} Place;

Place places[MAX_PLACES];

// 리뷰를 텍스트 파일에서 읽어오는 함수
void loadReviewsFromFile(Place places[], int size, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fgets(places[i].name, NAME_SIZE, file) == NULL) break;
        places[i].name[strcspn(places[i].name, "\n")] = '\0'; // 개행 문자 제거

        if (fgets(places[i].review, REVIEW_SIZE, file) == NULL) break;
        places[i].review[strcspn(places[i].review, "\n")] = '\0'; // 개행 문자 제거

        if (fscanf(file, "%d\n", &places[i].popularity) != 1) break;
    }

    fclose(file);
}

// 리뷰를 텍스트 파일에 저장하는 함수
void saveReviewsToFile(const Place places[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s\n%s\n%d\n", places[i].name, places[i].review, places[i].popularity);
    }

    fclose(file);
}

// 비밀번호를 파일에 저장하는 함수
void savePasswordToFile(const char* password) {
    FILE* file = fopen(PASSWORD_FILE, "w");
    if (file == NULL) {
        printf("비밀번호 파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "%s\n", password);
    fclose(file);
}

// 비밀번호를 파일에서 읽어오는 함수
void loadPasswordFromFile(char* password) {
    FILE* file = fopen(PASSWORD_FILE, "r");
    if (file == NULL) {
        printf("비밀번호 파일을 열 수 없습니다. 기본 비밀번호를 사용합니다.\n");
        strcpy(password, "0000");
        return;
    }

    if (fgets(password, PASSWORD_SIZE, file) == NULL) {
        printf("비밀번호를 읽어올 수 없습니다. 기본 비밀번호를 사용합니다.\n");
        strcpy(password, "0000");
    }
    else {
        password[strcspn(password, "\n")] = '\0'; // 개행 문자 제거
    }

    fclose(file);
}

// 비밀번호 확인 함수
int checkPassword() {
    char enteredPassword[PASSWORD_SIZE];
    char storedPassword[PASSWORD_SIZE];

    loadPasswordFromFile(storedPassword);

    printf("비밀번호를 입력하세요: ");
    scanf("%4s", enteredPassword);
    system("cls");

    if (strcmp(enteredPassword, storedPassword) == 0) {
        return 1;
    }
    else {
        printf("비밀번호가 틀렸습니다.\n");
        return 0;
    }
}

int changePassword() {
    char newPassword[PASSWORD_SIZE];
    char enteredPassword[PASSWORD_SIZE];
    char confirmedPassword[PASSWORD_SIZE];
    char storedPassword[PASSWORD_SIZE];

    loadPasswordFromFile(storedPassword);

    printf("현재 비밀번호를 입력하세요: ");
    scanf("%4s", enteredPassword);
    system("cls");

    if (strcmp(enteredPassword, storedPassword) == 0) {
        printf("새 비밀번호를 입력하세요 (4자리): ");
        scanf("%4s", newPassword);

        printf("새 비밀번호를 다시 입력하세요: ");
        scanf("%4s", confirmedPassword);

        if (strcmp(newPassword, confirmedPassword) == 0) {
            savePasswordToFile(newPassword);
            system("cls");
            printf("비밀번호가 변경되었습니다.\n");
            return 1;
        }
        else {
            system("cls");
            printf("입력한 두 개의 비밀번호가 일치하지 않습니다.\n");
            return 0;
        }
    }
    else {
        printf("비밀번호가 틀렸습니다.\n");
        return 0;
    }
}

// 리뷰 수정 함수
void editReview(Place* place, const char* newReview) {
    strcpy(place->review, newReview);
}

// 인기도 수정 함수
void editPopularity(Place* place, int newPopularity) {
    place->popularity = newPopularity;
}

// 가게 이름을 가나다 순으로 정렬하는 함수
void sortPlacesByName(Place places[], int size) {
    Place temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(places[i].name, places[j].name) > 0) {
                temp = places[i];
                places[i] = places[j];
                places[j] = temp;
            }
        }
    }
}

// 인기도 순으로 정렬하는 함수
void sortPlacesByPopularity(Place places[], int size) {
    Place temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (places[i].popularity < places[j].popularity) {
                temp = places[i];
                places[i] = places[j];
                places[j] = temp;
            }
        }
    }
}

// 가게 목록 출력 함수  printPlaces(places, MAX_PLACES);
void printPlaces(Place places[], int size) {
    gotoxy(3, 1);
    printf("\n");
    printf("    가게 이름                      가게 소개                          인기도\n\n");
    for (int i = 0; i < size; i++) {

        //gotoxy(2, i + 6);
        printf("%d. %10s  %-55s %3d\n", i + 1, places[i].name, places[i].review, places[i].popularity);
    }
    printf("\n");
}
void printPlaces2(Place places[], int size) {
    gotoxy(5, 4);
    printf(" 가게 이름                      가게 소개                          인기도");
    for (int i = 0; i < size; i++) {

        gotoxy(2, i + 6);
        printf("%d. %10s  %-55s %3d\n", i + 1, places[i].name, places[i].review, places[i].popularity);
    }
    printf("\n");
}

void manager() {
    Place places[MAX_PLACES];

    if (!checkPassword()) {
        return;
    }

    loadReviewsFromFile(places, MAX_PLACES, "reviews.txt");

    int choice;
    int placeIndex;
    char newReview[REVIEW_SIZE];
    int newPopularity;

    while (1) {
        printf("1. 가게 리뷰 수정\n");
        printf("2. 가게 인기도 수정\n");
        printf("3. 가게 이름 가나다 순으로 정렬\n");
        printf("4. 가게 인기도 순으로 정렬\n");
        printf("5. 현재 가게 목록 보기\n");
        printf("6. 비밀번호 변경\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);
        system("cls");

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            printf("수정할 가게 번호를 입력하세요:\n");
            printPlaces(places, MAX_PLACES);
            printf("선택: ");
            scanf("%d", &placeIndex);
            system("cls");
            if (placeIndex < 1 || placeIndex > MAX_PLACES) {
                printf("잘못된 번호입니다.\n");
                break;
            }
            printf("새 리뷰 내용을 입력하세요: ");
            getchar();
            fgets(newReview, sizeof(newReview), stdin);
            printf("\n");
            newReview[strcspn(newReview, "\n")] = '\0';
            editReview(&places[placeIndex - 1], newReview);
            saveReviewsToFile(places, MAX_PLACES, "reviews.txt");
            printf("수정된 리뷰 내용\n");
            printPlaces(places, MAX_PLACES);

            break;

        case 2:
            printf("수정할 가게 번호를 입력하세요:\n");
            printPlaces(places, MAX_PLACES);
            printf("선택: ");
            scanf("%d", &placeIndex);
            if (placeIndex < 1 || placeIndex > MAX_PLACES) {
                printf("잘못된 번호입니다.\n");
                break;
            }
            printf("새 인기도를 입력하세요 (1-100): ");
            scanf("%d", &newPopularity);
            if (newPopularity < 1 || newPopularity > 100) {
                printf("잘못된 인기도입니다.\n");
                break;
            }
            editPopularity(&places[placeIndex - 1], newPopularity);
            saveReviewsToFile(places, MAX_PLACES, "reviews.txt");
            system("cls");
            printf("수정된 인기도 내용:\n");
            printPlaces(places, MAX_PLACES);
            break;

        case 3:
            sortPlacesByName(places, MAX_PLACES);
            saveReviewsToFile(places, MAX_PLACES, "reviews.txt");
            printf("가게 이름이 가나다 순으로 정렬되었습니다.\n\n");
            printPlaces(places, MAX_PLACES);
            break;

        case 4:
            sortPlacesByPopularity(places, MAX_PLACES);
            saveReviewsToFile(places, MAX_PLACES, "reviews.txt");
            printf("가게 인기도가 높은 순으로 정렬되었습니다.\n\n");
            printPlaces(places, MAX_PLACES);
            break;

        case 5:
            printf("현재 가게 목록:\n\n");
            printPlaces(places, MAX_PLACES);
            break;

        case 6:
            changePassword();
            break;

        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }

    printf("프로그램을 종료합니다.\n");
}

void allreview(const char* filename) {  //모든 리뷰를 엔터 구분으로 가져온다
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    for (int i = 0; i < MAX_PLACES; i++) {
        if (fgets(places[i].name, NAME_SIZE, fp) == NULL) break;
        places[i].name[strcspn(places[i].name, "\n")] = '\0';  // 개행 문자 제거

        if (fgets(places[i].review, REVIEW_SIZE, fp) == NULL) break;
        places[i].review[strcspn(places[i].review, "\n")] = '\0';  // 개행 문자 제거

        if (fscanf(fp, "%d\n", &places[i].popularity) != 1) break;
    }

    fclose(fp);
}
void printPlace(int index) {
    if (index < 0 || index >= MAX_PLACES) {
        printf("Invalid index\n");
        return;
    }
    printf(" %s /", places[index].name);
    printf(" %s /", places[index].review);
    printf(" %d\n", places[index].popularity);
}

void reviewbox(int index) {  // 리뷰창 박스
    int m = 4;
    int review_length = strlen(places[index].review);

    if (index < 0 || index >= MAX_PLACES) {
        printf("Invalid index\n");
        return;
    }

    printBOX();
    gotoxy(25, 1);
    printf("%s 리뷰", places[index].name); // 식당 이름 출력
    gotoxy(10, 3); // y2의 초기값 5
    printf("┌");
    for (int i = 0; i < 40; i++)
        printf("─"); // 여기 사이에 리뷰 들어갈 자리
    printf("┐\n");
    printf("│%40s│\n", " ");
    gotoxy(10, 6);
    int review_index = 0;
    for (int i = 0; i < 17; i++) {
        gotoxy(10, m++);
        if (review_index < review_length) {
            printf("│%-40.*s│\n", 39, places[index].review + review_index);
            review_index += 39;
        }
        else {
            printf("│%40s│\n", " ");
        }
    }

    gotoxy(10, 20);
    printf("└");
    for (int i = 0; i < 40; i++)
        printf("─");
    printf("┘");

    //gotoxy(30, 2);
    //printf("review");

    gotoxy(0, 24);
}

int main(void) {
    const char* filename = "reviews.txt";
    allreview(filename);

    int number = 0;

    menu1(); // 놀거리

    gotoxy(2, 20);
    printf("입력 : ");
    scanf("%d", &number);
    if (number == 1) { // 가게 이름 번호
        menu2(); // 가게 목록
        gotoxy(2, 20);
        printf("입력 : ");
        scanf("%d", &number); // 입력 받은 값을 number에 저장한다
        if (number == 1) {
            menu3(); // 길찾기, 리뷰 선택 화면
            gotoxy(2, 20);
            printf("입력 : ");
            scanf("%d", &number);
            if (number == 1) { // 길찾기
                number2 = 5;
                letme();
            }
            else if (number == 2) { // 리뷰
                system("cls");
                reviewbox(0);
            }
        }
        else if (number == 2) {
            menu3(); // 길찾기, 리뷰 선택 화면
            gotoxy(2, 20);
            printf("입력 : ");
            scanf("%d", &number);
            if (number == 1) { // 길찾기
                number2 = 7;
                letme();
            }
            else if (number == 2) { // 리뷰
                system("cls");
                reviewbox(1);
            }
        }
    }
    else if (number == 4) {
        printf("전체출력");
        allprint();
    }
    else if (number == 5) {
        system("cls");
        manager();
    }
    return 0;
}

void allprint(void) {
    system("cls");
    y2 = 5;
    printBOX();
    printMiniBox();
    printMiniBox();
    gotoxy(23, 6);
    printf("1. 가나다순 정렬");
    gotoxy(23, 9);
    printf("2. 인기도순 정렬");
    gotoxy(2, 20);
    printf("입력 : ");
    scanf("%d", &number);
    if (number == 1) {
        printBOX2(); //메뉴 항목에서만 사용 가능한 상자 출력 함수
        gotoxy(25, 1);
        sortPlacesByName(places, MAX_PLACES);
        saveReviewsToFile(places, MAX_PLACES, "reviews.txt");

        printf("가게 이름이 가나다 순으로 정렬되었습니다.\n\n");

        printPlaces2(places, MAX_PLACES); //메뉴 항목에서만 사용 가능한 장소 출력 함수
        gotoxy(2, 10);
        printf("길을 찾고싶은 장소를 선택하시오 : ");
        scanf("%d", &number);
        if (number == 1) {
            number2 = 5;
            letme();
        }
        else if (number == 2) {
            number2 = 7;
            letme();
        }
    }
    else if (number == 2) {
        //인기도순 정렬

        printBOX2(); //메뉴 항목에서만 사용 가능한 상자 출력 함수
        gotoxy(25, 1);
        sortPlacesByPopularity(places, MAX_PLACES);
        saveReviewsToFile(places, MAX_PLACES, "reviews.txt");

        printf("가게가 인기도 순으로 정렬되었습니다.\n\n");

        printPlaces2(places, MAX_PLACES); //메뉴 항목에서만 사용 가능한 장소 출력 함수
        gotoxy(2, 10);
        printf("길을 찾고싶은 장소를 선택하시오 : ");
        scanf("%d", &number);
        if (number == 1) {
            number2 = 7;
            letme();
        }
        else if (number == 2) {
            number2 = 5;
            letme();
        }
    }
    else
        printf("잘못 선택하셨습니다.");
}