#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UI.h"
#include <vector>
#include <iostream>

void Level::CreateChunk(int x, int y) {
	for (int i = x; i < x + 2; i++) {
		for (int j = y; j < y + 4; j++) {
			if ((j <= 31) || (i <= 21) || (j > 0) || (i > 0)) {
				textureLocation[i][j] = 0;
			}
		}
	}
}

void Level::CreateChunk2(int x, int y) {
	for (int i = x; i < x + 2; i++) {
		for (int j = y; j < y + 4; j++) {
			if ((j <= 31) || (i <= 21) || (j > 0) || (i > 0)) {
				textureLocation[i][j] = 1;
			}
		}
	}
}

//�-� ��� ����������� ��������� ���� �� �������
int Level::GetLocation(int x, int y) {
	if (x >= 0 && x < 32 && y >= 0 && y < 22) {
		return textureLocation[y][x];
	}
	else {
		return 1;
	}
}

//�-� ��� ����������� ���������� �������
void Level::ChangeLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		textureLocation[y][x] = 0;
	}
}

//��� ������ ������ ��������� ���� ������� �� 8*11 ������

void Level::ChunkGenerationMethod() {
	for (int j = 0; j < 8; j++) { //����� ����� �� 8 �������� �� 11 ������, ������������ ������ ��������
		int i = rand() % 4 + rand() % 3; int count = 0;
		//������� �����: � ������ ������� ������� �����-�� ���������� ������ ������ (� ������� ����� ������)
		//������� �� ������-�� �����. ����� ����, ��� �� ��������� �������, �� �������, ��� �������, ��������� ������
		//��������, � 1 ������� ������ �� 4 �� 7 �����, � �� 2 ������ �� 5 �� 9 �����, ����������� � ������
		while (count < (5 + rand() % 3)) { //�������� ���-�� ������ ������ � �������
			if (i + count < 11) {
				CreateChunk((i + count) * 2, j * 4);
			}
			count++;
		}
	}
	//���� ��� �����������, ���������� ��������� ������ � ����������
   //��� ������ ������ ������� ������ ������- ������. ���� �� ������ 3, ������ ������ ������
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			int iteration = 0;
			while (iteration < 50) {
				int count = 0;
				if (GetLocation(j, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i + 1) == 0) {
					count++;
				}
				if (count > 3) {
					textureLocation[i][j] = 0;
				}
				iteration++;
			}
		}
	}

	//����� �������� �������� ������ � ������ �� ��������, ����� ������� ��� �������������

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if ((!(rand() % 16))) {
				int m = textureLocation[i][j];
				textureLocation[i][j] = 3;
				if (GetLocation(j, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
			}
			if (textureLocation[i][j] == 1) {
				if (rand() % 2) {
					textureLocation[i][j] = 5;
				}
			}
			if (textureLocation[i][j] == 0) {
				switch (rand() % 3) {
				case 0:
					break;
				case 1:
					textureLocation[i][j] = 4;
					break;
				case 2:
					textureLocation[i][j] = 6;
					break;
				}
			}
			//����� ������ ������
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	//�������� ������, ������� ������ ����, ��� �����, � ��� ����� ������

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}

	//������ �������

	for (int i = 0; i < 3; i++) {
		chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0] + 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] + 1] != 0 || Location[chests[i][0] - 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] + 1] != 0 || Location[chests[i][0] + 1][chests[i][1] - 1] != 0 || Location[chests[i][0] + 1][chests[i][1] + 1] != 0) {
			chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		}
		textureLocation[chests[i][0]][chests[i][1]] = 14;
		Location[chests[i][0]][chests[i][1]] = 3;
	}

	TileSet = 0;
}

void Level::LabGeneration() {
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			//����� ������ ������
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 29; j++) {
			if ((i % 2 == 1) && (j % 2 == 1)) {
				textureLocation[i][j] = 0;
				//int PrevWay = 0;
				int Way = rand() % 2;
				bool Choosed = false;
				while (Choosed == false) {
					Choosed = true;
					/*if (PrevWay == 30) {
						Choosed = false;
						Way = 4;
					}*/
					switch (Way) {
					case 0:
						if (textureLocation[i][j + 1] != 1) {
							//PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i][j + 1] = 0;
						}
						break;
					case 1:
						if (textureLocation[i+1][j] != 1) {
							//PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i + 1][j] = 0;
						}
						break;
					/*case 2:
						if (textureLocation[i][j - 1] != 1) {
							PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i][j - 1] = 0;
						}
						break;*/
					/*case 3:
						if (textureLocation[i-1][j] != 1) {
							PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i - 1][j] = 0;
						}
						break;*/
					/*case 4:
						textureLocation[i][j+1] = 0;
						textureLocation[i+1][j] = 0;
						textureLocation[i - 1][j] = 0;
						textureLocation[i][j-1] = 0;
						break;*/
					default:
						break;
					}
				}
			}
		}
	}
	for (int i = 1; i < 20; i++) {
		textureLocation[i][29] = 0;
	}
	for (int i = 1; i < 30; i++) {
		textureLocation[19][i] = 0;
	}

	//������ �������

	int counter = 0;
	for (int k = 1; k < 21; k++) {
		for (int j = 1; j < 31; j++) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[0][0] = k; chests[0][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[0][0]][chests[0][1]] = 14;
	Location[chests[0][0]][chests[0][1]] = 3;
	counter = 0;
	for (int k = 20; k >= 1; k--) {
		for (int j = 1; j < 31; j++) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[1][0] = k; chests[1][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[1][0]][chests[1][1]] = 14;
	Location[chests[1][0]][chests[1][1]] = 3;
	counter = 0;
	for (int k = 20; k >= 1; k--) {
		for (int j = 30; j >= 1; j--) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[2][0] = k; chests[2][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[2][0]][chests[2][1]] = 14;
	Location[chests[2][0]][chests[2][1]] = 3;

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if (textureLocation[i][j] == 1) {
				if (rand() % 2) {
					textureLocation[i][j] = 5;
				}
			}
			if (textureLocation[i][j] == 0) {
				switch (rand() % 3) {
				case 0:
					break;
				case 1:
					textureLocation[i][j] = 4;
					break;
				case 2:
					textureLocation[i][j] = 6;
					break;
				}
			}
			//����� ������ ������
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	//�������� ������, ������� ������ ����, ��� �����, � ��� ����� ������

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}
	TileSet = 0;
}

void Level::CastleLabGeneration() {
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			//����� ������ ������
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 29; j++) {
			if ((i % 2 == 1) && (j % 2 == 1)) {
				textureLocation[i][j] = 0;
				//int PrevWay = 0;
				int Way = rand() % 2;
				bool Choosed = false;
				while (Choosed == false) {
					Choosed = true;
					/*if (PrevWay == 30) {
						Choosed = false;
						Way = 4;
					}*/
					switch (Way) {
					case 0:
						if (textureLocation[i][j + 1] != 1) {
							//PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i][j + 1] = 0;
						}
						break;
					case 1:
						if (textureLocation[i + 1][j] != 1) {
							//PrevWay++;
							Way = rand() % 4;
							Choosed = false;
						}
						else {
							textureLocation[i + 1][j] = 0;
						}
						break;
						/*case 2:
							if (textureLocation[i][j - 1] != 1) {
								PrevWay++;
								Way = rand() % 4;
								Choosed = false;
							}
							else {
								textureLocation[i][j - 1] = 0;
							}
							break;*/
							/*case 3:
								if (textureLocation[i-1][j] != 1) {
									PrevWay++;
									Way = rand() % 4;
									Choosed = false;
								}
								else {
									textureLocation[i - 1][j] = 0;
								}
								break;*/
								/*case 4:
									textureLocation[i][j+1] = 0;
									textureLocation[i+1][j] = 0;
									textureLocation[i - 1][j] = 0;
									textureLocation[i][j-1] = 0;
									break;*/
					default:
						break;
					}
				}
			}
		}
	}
	for (int i = 1; i < 20; i++) {
		textureLocation[i][29] = 0;
	}
	for (int i = 1; i < 30; i++) {
		textureLocation[19][i] = 0;
	}

	//������ �������

	int counter = 0;
	for (int k = 1; k < 21; k++) {
		for (int j = 1; j < 31; j++) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[0][0] = k; chests[0][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[0][0]][chests[0][1]] = 14;
	Location[chests[0][0]][chests[0][1]] = 3;
	counter = 0;
	for (int k = 20; k >= 1; k--) {
		for (int j = 1; j < 31; j++) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[1][0] = k; chests[1][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[1][0]][chests[1][1]] = 14;
	Location[chests[1][0]][chests[1][1]] = 3;
	counter = 0;
	for (int k = 20; k >= 1; k--) {
		for (int j = 30; j >= 1; j--) {
			if (textureLocation[k][j] == 0) {
				counter = 0;
				if (textureLocation[k][j + 1] == 0 || textureLocation[k][j + 1] == 14) {
					counter++;
				}
				if (textureLocation[k][j - 1] == 0 || textureLocation[k][j - 1] == 14) {
					counter++;
				}
				if (textureLocation[k - 1][j] == 0 || textureLocation[k - 1][j] == 14) {
					counter++;
				}
				if (textureLocation[k + 1][j] == 0 || textureLocation[k + 1][j] == 14) {
					counter++;
				}
				if (counter == 1) {
					chests[2][0] = k; chests[2][1] = j;
					break;
				}
			}
		}
	}
	textureLocation[chests[2][0]][chests[2][1]] = 14;
	Location[chests[2][0]][chests[2][1]] = 3;

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
				textureLocation[i][j] = 5;
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
				if (rand() % 2) {
					textureLocation[i][j] = 3;
				}
				else {
					textureLocation[i][j] = 4;
				}
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
				if (rand() % 2) {
					textureLocation[i][j] = 7;
				}
				else {
					textureLocation[i][j] = 8;
				}
			}
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	//�������� ������, ������� ������ ����, ��� �����, � ��� ����� ������

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 6) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 7) || (textureLocation[i][j] == 8)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}

	TileSet = 1;
}

//����� ��� ��������� ������, 2 ������� ���������

//������� ����� ����� �� 8 ������, 4 ������� �� 2 �����
//� ������ ������� ��������, ����� �� ������ ����� ���������
//� ������, � ������� ���� ��������� ����, �������� ���� ����� 2 ��� 3, �� ������� ���������� ������� ������
//� ��������� ������� �������� �������� ����
//������� ������ ���� �� ���������� ����� ������, ������������ ������ ��� ���� �� ����� ��������
//(�� ���� ������ ������), ����� ������ ������ �� ���������� �������
//� ������ ������� ���� ������, ������� ��������� �����
//������ 8, �� ������ �� 8, ���� �� ������ �������� �����, � ������� �� ����� �������
void Level::RoomGenerationMethod2() {
	int RoomSectors[2][4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	//�������� ����� ����
	switch (rand() % 2) {
	case 0:
		RoomSectors[0][0] = 1;
		break;
	case 1:
		RoomSectors[1][0] = 1;
		break;
	}
	//�������� �������� ����
	//p.s. � ��������� � �������� ����� ������ ���� �������
	switch (rand() % 2) {
	case 0:
		RoomSectors[0][3] = 2;
		break;
	case 1:
		RoomSectors[1][3] = 2;
		break;
	}
	//�������� ���� ��������. p.s. � ��� ���� ������ ���� �������
	switch (rand() % 2) {
	case 0:
		if (RoomSectors[0][0] == 1) {
			RoomSectors[0][1] = 3;
			break;
		}
		else {
			RoomSectors[1][1] = 3;
			break;
		}
	case 1:
		if (RoomSectors[0][0] == 1) {
			RoomSectors[0][2] = 3;
			break;
		}
		else {
			RoomSectors[1][2] = 3;
			break;
		}
	}
	//�������� �����, � ������� �� ����� �������
	int count = 0;
	while (count < 1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if ((!(rand() % 4)) && (RoomSectors[i][j] == 0)) {
					RoomSectors[i][j] = -1;
					count++;
					break;
				}
			}
		}
	}
	//...
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << RoomSectors[i][j] << " ";
		}
	}
	//������ ������, ���� �� ���� ��� �����
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (RoomSectors[i][j] == 1) {
				for (int k = 0; k < 8; k++) {
					textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
				}
			}
			if ((RoomSectors[i][j] == 0) || (RoomSectors[i][j] == -1)) {
				if ((j == 2) && ((RoomSectors[1 - i][1] == 3) || (RoomSectors[1 - i][2] == 3))) {
					for (int k = 0; k < 8; k++) {
						textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
					}
				}
				if ((j == 1) && ((RoomSectors[i][0] == 1) || (RoomSectors[1 - i][j] == 3))) {
					for (int k = 0; k < 8; k++) {
						textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
					}
				}
			}
		}
	}
	//������ ������ ����� ������� � ��������
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 11; k++) {
			textureLocation[5 + k][8 * i + 4] = 0;
		}
	}
	//������ �������
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			int start = rand() % 2;
			int end = rand() % 2;
			if (RoomSectors[i][j] != -1) {
				for (int k = 0; k < 6; k++) {
					for (int m = 0 + start; m < 7 + end; m++) {
						textureLocation[11 * i + 1 + m][8 * j + 1 + k] = 0;
					}
				}
			}
		}
	}
	//������ ��������� ����������� ������ ������(������, �� �������)
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			textureLocation[11 * i + 5][8 * j + 4] = 6;
		}
	}
	//������ ������� ����
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	//��������� ������������ � ���������
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
				textureLocation[i][j] = 5;
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
				if (rand() % 2) {
					textureLocation[i][j] = 3;
				}
				else {
					textureLocation[i][j] = 4;
				}
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
				if (rand() % 2) {
					textureLocation[i][j] = 7;
				}
				else {
					textureLocation[i][j] = 8;
				}
			}
		}
	}

	//��������� ���� � ���, ��� �����, � ��� ����� ������, � ������

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 6) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 7) || (textureLocation[i][j] == 8)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}

	//������ �������

	for (int i = 0; i < 3; i++) {
		chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0]+1][chests[i][1]] != 0|| Location[chests[i][0]][chests[i][1]+1] != 0 || Location[chests[i][0]-1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1]-1] != 0 || Location[chests[i][0]- 1][chests[i][1] -1 ] != 0 || Location[chests[i][0]-1][chests[i][1]+1] != 0 || Location[chests[i][0]+1][chests[i][1]-1] != 0 || Location[chests[i][0]+1][chests[i][1]+1] != 0) {
			chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		}
		textureLocation[chests[i][0]][chests[i][1]] = 14;
		Location[chests[i][0]][chests[i][1]] = 3;
	}

	TileSet = 1;
}

void Level::ChunkGenerationMethod2() {
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 31; j++) {
			textureLocation[i][j] = 0;
		}
	}
	for (int j = 0; j < 8; j++) { //����� ����� �� 8 �������� �� 11 ������, ������������ ������ ��������
		int i = rand() % 4 + rand() % 3; int count = 0;
		//�� ���� ������ �������� ��������, ���� ��������� ��� ������, �� �� �������� ������ ����� ����, � �� ����
		while (count < (5 + rand() % 3)) { //�������� ���-�� ������ ������ � �������
			if (i + count < 11) {
				CreateChunk2((i + count) * 2, j * 4);
			}
			count++;
		}
	}
	//���� ��� �����������, ���������� ��������� ������ � ����������
   //��� ������ ������ ������� ������ ������- ������. ���� �� ������ 3, ������ ������ ������
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			int iteration = 0;
			while (iteration < 50) {
				int count = 0;
				if (GetLocation(j, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i + 1) == 0) {
					count++;
				}
				if (count > 3) {
					if ((rand() % 3) == 0) {
						textureLocation[i][j] = 0;
					}
				}
				if (count > 1) {
					if ((rand() % 200) == 0) {
						textureLocation[i][j] = 0;
					}
				}
				iteration++;
			}
		}
	}
	for (int j = 1; j < 31; j++) {
		textureLocation[1][j] = 0;
		textureLocation[2][j] = 0;
		textureLocation[19][j] = 0;
		textureLocation[20][j] = 0;
	}
	int chouseTunnel = rand() % 3;
	int StartTunnel = 0;
	switch (chouseTunnel) {
	case 0:
		StartTunnel = rand() % 28;
		for (int i = 0; i < 21; i++) {
			textureLocation[i][StartTunnel] = 0;
			textureLocation[i][StartTunnel + 1] = 0;
			textureLocation[i][StartTunnel + 2] = 0;
			textureLocation[i][StartTunnel + 3] = 0;
			textureLocation[i][StartTunnel + 4] = 0;
			if ((rand() % 2)==1) {
				textureLocation[i][StartTunnel + 5] = 0;
			}
		}
		break;
	case 1:
		StartTunnel = rand() % 10;
		for (int i = 0; i < 21; i++) {
			textureLocation[i][StartTunnel] = 0;
			textureLocation[i][StartTunnel + 1] = 0;
			textureLocation[i][StartTunnel + 2] = 0;
			textureLocation[i][StartTunnel + 3] = 0;
			textureLocation[i][StartTunnel + 4] = 0;
			if ((rand() % 2) == 1) {
				textureLocation[i][StartTunnel + 5] = 0;
			}
			StartTunnel++;
		}
		break;
	case 2:
		StartTunnel = rand() % 10 + 18;
		for (int i = 0; i < 21; i++) {
			textureLocation[i][StartTunnel] = 0;
			textureLocation[i][StartTunnel + 1] = 0;
			textureLocation[i][StartTunnel + 2] = 0;
			textureLocation[i][StartTunnel + 3] = 0;
			textureLocation[i][StartTunnel + 4] = 0;
			if ((rand() % 2) == 1) {
				textureLocation[i][StartTunnel + 5] = 0;
			}
			StartTunnel--;
		}
		break;
	default:
		break;
	}
	//����� �������� �������� ������ � ������ �� ��������, ����� ������� ��� �������������

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if ((!(rand() % 16))) {
				int m = textureLocation[i][j];
				textureLocation[i][j] = 3;
				if (GetLocation(j, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j + 1, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i - 1) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i) == 3) {
					textureLocation[i][j] = m;
				}
				if (GetLocation(j - 1, i + 1) == 3) {
					textureLocation[i][j] = m;
				}
			}
			if (textureLocation[i][j] == 1) {
				if (rand() % 2) {
					textureLocation[i][j] = 5;
				}
			}
			if (textureLocation[i][j] == 0) {
				switch (rand() % 3) {
				case 0:
					break;
				case 1:
					textureLocation[i][j] = 4;
					break;
				case 2:
					textureLocation[i][j] = 6;
					break;
				}
			}
			//����� ������ ������
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	//�������� ������, ������� ������ ����, ��� �����, � ��� ����� ������

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}

	//������ �������

	for (int i = 0; i < 3; i++) {
		chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0] + 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] + 1] != 0 || Location[chests[i][0] - 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] + 1] != 0 || Location[chests[i][0] + 1][chests[i][1] - 1] != 0 || Location[chests[i][0] + 1][chests[i][1] + 1] != 0) {
			chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
		}
		textureLocation[chests[i][0]][chests[i][1]] = 14;
		Location[chests[i][0]][chests[i][1]] = 3;
	}

	TileSet = 0;
}