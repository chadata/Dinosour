// very simple google dinosaur.
//BlockDMask.
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView() {
	system("mode con:cols=100 lines=25");
	system("title Google Dinosours. By BlockMask");
}

//커서 위치를 x,y로 이동하는 함수
void GoToXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
	if (_kbhit() != 0) {
		return _getch();
	}
	return 0;
}

//공룡을 그리는 함수
void DrawDino(int dinoY) {
	GoToXY(0, dinoY);
	static bool legFlag = true;
	printf("        $$$$$$$ \n");
	printf("       $$ $$$$$$\n");
	printf("       $$$$$$$$$\n");
	printf("$      $$$      \n");
	printf("$$     $$$$$$$  \n");
	printf("$$$   $$$$$$    \n");
	printf(" $$  $$$$$$$$$$ \n");
	printf("  $$$$$$$$$$$   \n");
	printf("   $$$$$$$$$$   \n");
	printf("    $$$$$$$$$   \n");
	printf("      $$$$$$    \n");
	if (legFlag) {
		printf("      $   $$$    \n");
		printf("      $$         ");
		legFlag = false;
	}
	else {
		printf("      $$$ $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

//나무를 그리는 함수
void DrawTree(int treeX) {
	GoToXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GoToXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GoToXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GoToXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GoToXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

//충돌 했을때 게임오버를 그려준다
void DrawGameOver(const int score) {
	system("cls");
	int x = 18;
	int y = 8;
	GoToXY(x, y);
	printf("=========================");
	GoToXY(x, y + 1);
	printf("=====G A M E O V E R=====");
	GoToXY(x, y + 2);
	printf("=========================");
	GoToXY(x, y + 5);
	printf("SCORE : %d", score);

	printf("\n\n\n\n\n\n\n\n\n\n");
	system("pause");
}

//충돌했으면 true,아니면 false
bool isCollision(const int treeX, const int dinoY) {
	//트리의 x가 공룡의 몸체쪽에 있을때,
	//공룡의 높이가 충분하지 않다면 충돌로 처리
	GoToXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY); //이런식으로 적절한 Y값을 찾는다
	if (treeX <= 8 && treeX >= 4 && dinoY > 8) {
		return true;
	}
	return false;
}

int main(void) {
	SetConsoleView();


	while (true) { //게임 루프
	//게임 시작시 초기화
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr; //점수 변수 초기화
		start = clock(); //시작시간 초기화

		while (true) {
			//충돌체크트리의 x값과 공룡의 y값으로 판단
			if (isCollision(treeX, dinoY))
				break;

			//z키가 눌렸고, 바닥이 아닐떄 점프
			if (GetKeyDown() == 'z' && isBottom) {
				isJumping = true;
				isBottom = false;
			}
			//점프중이라면Y를 감소,점프가 끝났으면Y를 증가
			if (isJumping) {
				dinoY -= gravity;
			}
			else {
				dinoY += gravity;
			}
			//Y가 예속해서 증가하는걸 막기위해 바닥을 지정
			if (dinoY >= DINO_BOTTOM_Y) {
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}
			//나무가 왼쪽으로(x음수)가도록하고
			//나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환
			treeX -= 2;
			if (treeX <= 0) {
				treeX = TREE_BOTTOM_X;
			}
			//점프의 맨위를 찍으면 점프가 끝난 상황
			if (dinoY <= 3) {
				isJumping = false;
			}

			DrawDino(dinoY); //draw dino
			DrawTree(treeX);//draw tree

			curr = clock();//현재시간 받아오기
			if (((curr - start) / CLOCKS_PER_SEC) >= 1) //1초가 넘었을때
			{
				score++; //스코어 업
				start = clock();//시작시간 초기화

			}
			Sleep(60);
			system("cls");//clear

			//점수출력을 1초마다 해주는 것이 아니라 항상 출력해주면서, 1초가 지났을때++해준다
			GoToXY(0, 0);//커서를 0,0으로 옮겨서
			printf("Score:%d", score);

		}

		DrawGameOver(score);
	}
	return 0;
}