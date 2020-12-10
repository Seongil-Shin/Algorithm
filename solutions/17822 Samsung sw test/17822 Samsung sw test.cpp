#include <iostream>
#include <cstring>
#include <vector>
#define MAX_BOARD 50
#define MAX_TURN 50

using namespace std;

int board[MAX_BOARD][MAX_BOARD];
int numOfTurn, numOfBoard, numOfNum;
int turn[MAX_TURN][3];	//xi, 0 or 1, ki

int getSumOfBoardNum();
void rotateBoard(vector<int> rotate, int direction, int ki);
void updateBoard();

int main() {
	cin >> numOfBoard >> numOfNum >> numOfTurn;
	for (int i = 0; i < numOfBoard; i++) {
		for (int j = 0; j < numOfNum; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < numOfTurn; i++) {
		cin >> turn[i][0] >> turn[i][1] >> turn[i][2];
	}

	cout << getSumOfBoardNum();
}

int getSumOfBoardNum() {
	for (int current = 0; current < numOfTurn; current++) {
		int xi = turn[current][0];
		vector<int> rotate;
		for (int i = 0; i < numOfBoard; i++) {
			if (((i + 1) % xi) == 0)
				rotate.push_back(i);
		}

		rotateBoard(rotate, turn[current][1], turn[current][2]);
		updateBoard();
	}

	int sum = 0;
	for (int i = 0; i < numOfBoard; i++)
		for (int j = 0; j < numOfNum; j++)
			sum += board[i][j];
	return sum;
}

void rotateBoard(vector<int> rotate, int direction, int ki) {
	if (direction == 0) {	//�ð�
		for (int i = 0; i < rotate.size(); i++) {
			for (int k = 0; k < ki; k++) {
				int temp = board[rotate[i]][0];
				for (int j = 1; j < numOfNum; j++) {
					int temp2 = board[rotate[i]][j];
					board[rotate[i]][j] = temp;
					temp = temp2;
				}
				board[rotate[i]][0] = temp;
			}
		}
	}
	else if (direction == 1) {
		for (int i = 0; i < rotate.size(); i++) {
			for (int k = 0; k < ki; k++) {
				int temp = board[rotate[i]][numOfNum-1];
				for (int j = numOfNum-1; j >= 0; j--) {
					int temp2 = board[rotate[i]][j];
					board[rotate[i]][j] = temp;
					temp = temp2;
				}
				board[rotate[i]][numOfNum-1] = temp;
			}
		}
	}
}

void updateBoard() {
	int tempBoard[MAX_BOARD][MAX_BOARD];
	bool check = false;
	for (int i = 0; i < numOfBoard; i++) {
		if (board[i][0] == board[i][1] || board[i][0] == board[i][numOfNum - 1] ||
			(i != 0 && board[i][0] == board[i - 1][0]) || (i != (numOfBoard - 1) && board[i][0] == board[i + 1][0])) {
			tempBoard[i][0] = 0;
			if(board[i][0] != 0) check = true;
		}
		else
			tempBoard[i][0] = board[i][0];

		for (int j = 1; j < numOfNum - 1; j++) {
			if (board[i][j] == board[i][j + 1] || board[i][j] == board[i][j - 1] ||
				(i != 0 && board[i][j] == board[i - 1][j]) || (i != (numOfBoard - 1) && board[i][j] == board[i + 1][j])) {
				tempBoard[i][j] = 0;
				if(board[i][j] != 0) check = true;
			}
			else
				tempBoard[i][j] = board[i][j];
		}

		if (board[i][numOfNum - 1] == board[i][0] || board[i][numOfNum - 1] == board[i][numOfNum - 2] ||
			(i != 0 && board[i][numOfNum - 1] == board[i - 1][numOfNum - 1]) || (i != (numOfBoard - 1) && board[i][numOfNum - 1] == board[i + 1][numOfNum - 1])) {
			tempBoard[i][numOfNum - 1] = 0;
			if(board[i][numOfNum - 1] != 0) check = true;
		}
		else
			tempBoard[i][numOfNum - 1] = board[i][numOfNum - 1];
	}
	if (!check) {
		int sum = 0;
		int count = 0;
		for (int i = 0; i < numOfBoard; i++) {
			for (int j = 0; j < numOfNum; j++) {
				if (tempBoard[i][j] != 0) {
					sum += tempBoard[i][j];
					count++;
				}
			}
		}
		if (count != 0) {
			float ave = (float)sum / (float)count;
			for(int i = 0; i<numOfBoard; i++) {
				for (int j = 0; j < numOfNum; j++) {
					if (tempBoard[i][j] != 0) {
						if (tempBoard[i][j] < ave)
							tempBoard[i][j]++;
						else if (tempBoard[i][j] > ave)
							tempBoard[i][j]--;
					}
				}
			}
		}
	}
	memcpy(board, tempBoard, sizeof(tempBoard));

}