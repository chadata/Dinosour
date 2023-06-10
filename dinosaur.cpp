// very simple google dinosaur.
//BlockDMask.
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
void SetConsoleView() {
	system("mode con:cols=100 lines=25");
	system("title Google Dinosours. By BlockMask");
}

//Ŀ�� ��ġ�� x,y�� �̵��ϴ� �Լ�
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

//������ �׸��� �Լ�
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

//������ �׸��� �Լ�
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

//�浹 ������ ���ӿ����� �׷��ش�
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

//�浹������ true,�ƴϸ� false
bool isCollision(const int treeX, const int dinoY) {
	//Ʈ���� x�� ������ ��ü�ʿ� ������,
	//������ ���̰� ������� �ʴٸ� �浹�� ó��
	GoToXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY); //�̷������� ������ Y���� ã�´�
	if (treeX <= 8 && treeX >= 4 && dinoY > 8) {
		return true;
	}
	return false;
}

int main(void) {
	SetConsoleView();


	while (true) { //���� ����
	//���� ���۽� �ʱ�ȭ
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr; //���� ���� �ʱ�ȭ
		start = clock(); //���۽ð� �ʱ�ȭ

		while (true) {
			//�浹üũƮ���� x���� ������ y������ �Ǵ�
			if (isCollision(treeX, dinoY))
				break;

			//zŰ�� ���Ȱ�, �ٴ��� �ƴҋ� ����
			if (GetKeyDown() == 'z' && isBottom) {
				isJumping = true;
				isBottom = false;
			}
			//�������̶��Y�� ����,������ ��������Y�� ����
			if (isJumping) {
				dinoY -= gravity;
			}
			else {
				dinoY += gravity;
			}
			//Y�� �����ؼ� �����ϴ°� �������� �ٴ��� ����
			if (dinoY >= DINO_BOTTOM_Y) {
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}
			//������ ��������(x����)�������ϰ�
			//������ ��ġ�� ���� �����ΰ��� �ٽ� ������ ������ ��ȯ
			treeX -= 2;
			if (treeX <= 0) {
				treeX = TREE_BOTTOM_X;
			}
			//������ ������ ������ ������ ���� ��Ȳ
			if (dinoY <= 3) {
				isJumping = false;
			}

			DrawDino(dinoY); //draw dino
			DrawTree(treeX);//draw tree

			curr = clock();//����ð� �޾ƿ���
			if (((curr - start) / CLOCKS_PER_SEC) >= 1) //1�ʰ� �Ѿ�����
			{
				score++; //���ھ� ��
				start = clock();//���۽ð� �ʱ�ȭ

			}
			Sleep(60);
			system("cls");//clear

			//��������� 1�ʸ��� ���ִ� ���� �ƴ϶� �׻� ������ָ鼭, 1�ʰ� ��������++���ش�
			GoToXY(0, 0);//Ŀ���� 0,0���� �Űܼ�
			printf("Score:%d", score);

		}

		DrawGameOver(score);
	}
	return 0;
}