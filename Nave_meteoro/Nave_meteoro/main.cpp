#include<iostream>
#include<conio.h>
#include<time.h>

using namespace std;
using namespace System;

const short HEIGHT = 32;
const short WIDTH = 44;
void setMap(short xWall, short xScore) {
	for (int i = 0; i < WIDTH; i++) {
		Console::SetCursorPosition(xWall, i);
		cout << "|";
	}
	Console::SetCursorPosition(xScore, 10);
	cout << "SCORE: ";
	Console::SetCursorPosition(xScore, 15);
	cout << "TIME: ";
	Console::SetCursorPosition(xScore, 20);
	cout << "LIVES: ";
}
void comments(short cx, short scoreY, short score, short timeY, short min, short seg, short livesY, short lives) 
{
	Console::SetCursorPosition(cx, scoreY);
	cout << score;
	Console::SetCursorPosition(cx, timeY);
	if (min < 10) {
		cout << "0";
	} cout << min<<":";
	if (seg < 10) {
		cout << "0";
	}cout << seg;
	Console::SetCursorPosition(cx, livesY);
	cout << lives;
}
void timing(short ms, short& seg, short& min)
{
	if (ms % 10 == 0) seg++;

	if (seg == 60&&ms%10==0) {
		min++;
	}
}
void dibujar(short x, short y, char c)
{
	Console::SetCursorPosition(x, y);
	cout << c;
}
void borrar(short x, short y)
{
	Console::SetCursorPosition(x, y);
	cout << " ";
}
void mover(short& dx, short& dy, short& x, short& y)
{
	if (x + dx > 0&&x+dx<WIDTH) {
		x += dx;
		dx = 0;
	}
	if (y + dy > 0 && y + dy < HEIGHT) {
		y += dy;
		dy = 0;
	}
}
void moverEne(short& dx, short& dy, short& x, short& y)
{
	/*if (eneY[i] < 0) {
					eneY[i]++;
				}
				else if (eneY[i] == HEIGHT-1) {
					borrar(eneX[i], eneY[i]);
					eneX[i] = rand() % WIDTH;
					eneY[i] = rand() % 10 - 10;
				}*/
	if (y < 0) {
		y++;
	}
	else if (y == HEIGHT - 1) {
		x = rand() % WIDTH;
		y = rand() % 10 - 10;
	}
	else {
		if (x + dx == -1) dx = 1;
		if (x + dx == WIDTH) dx = -1;
		if (y + dy == -1) dy = 1;
		if (y + dy == HEIGHT) dy = -1;
		if (x + dx >= 0 && x + dx < WIDTH) {
			x += dx;
		}
		if (y + dy >= 0 && y + dy < HEIGHT) {
			y += dy;
		}
	}
	
}
void movBala(bool& fire, short &bx, short &by, short &dby, short &disparo)
{
	if (by + dby >= 0)
	{
		by += dby;
	}
	else {
		fire = false;
		bx = NULL;
		by = NULL;
		dby = 0;
		disparo = NULL;
	}
}
void resetEnemies(short &ex, short &ey)
{
	ex = rand() % WIDTH;
	ey = rand() % 10 - 10;
}
void disparoBala(bool &fire, short &bx, short &by, short &dby, short &disparo)
{
	if (fire)
	{
		borrar(bx, by);
		movBala(fire, bx, by, dby, disparo);
		if (bx != NULL && by != NULL) {
			dibujar(bx, by, '.');
		}
	}
}
void enemiesOnGame(bool& eneVivo, short& ex, short& ey, short& edx, short& edy,
	short& lives, short& x, short& y, short x0, short y0, bool &perdioVida)
{
	if (eneVivo) {
		if (ey < 0) ey++;
		else if (ey == HEIGHT - 1) {
			borrar(ex, ey);
			ex = rand() % WIDTH;
			ey = rand() % 10 - 10;
		}
		else {
			borrar(ex, ey);
			moverEne(edx, edy, ex, ey);
			dibujar(ex, ey, '*');
		}
		//Impacto con nave
		if (x == ex && y == ey) {
			lives--;
			perdioVida = true;
			_sleep(1000);
			x = x0;
			y = y0;
		}
	}
}
void borrarMapa()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH + 20; j++) {
			borrar(j, i);
		}
	}
}
void menuStart()
{
	char c;
	for (int i = 0; i < 30; i++) {
		Console::ForegroundColor = ConsoleColor::Red;
		dibujar(rand() % (WIDTH + 20), rand() % HEIGHT, '*');
	}
	Console::ForegroundColor = ConsoleColor::White;
	for (int i = 28; i < 38; i++) dibujar(i, 5, (char)196);
	dibujar(27, 5, char(218));
	dibujar(38, 5, char(191));
	dibujar(27, 6, char(179));
	dibujar(38, 6, char(179));
	dibujar(27, 7, char(192));
	dibujar(38, 7, char(217));
	for (int i = 28; i < 38; i++) dibujar(i, 7, (char)196);
	
	Console::SetCursorPosition(28, 6);
	cout << "ASTEROIDES";

	Console::SetCursorPosition(15, 13);
	cout << "ESQUIVA Y DESTRUYE TANTOS SIN MORIR";
	Console::SetCursorPosition(17, 17);
	cout << "PRESIONA 'ESPACIO' PARA EMPEZAR";
	Console::SetCursorPosition(16, 19);
	cout << "PRESIONA 'X' PARA SALIR DEL JUEGO";
	Console::SetCursorPosition(11, 25);
	cout << "USA LAS TECLAS 'W, A, S, D' PARA DESPLAZARTE";
	Console::SetCursorPosition(14, 27);
	cout << "DISPARA PRESIONANDO LA BARRA ESPCIADORA";
	Console::SetCursorPosition(11, 28);
	cout << "CUIDADO QUE SOLO TIENE 5 BALAS REUTILIZABLES";
	Console::SetCursorPosition(46, HEIGHT);
	cout << "BY: @diego_defsan";
	
	do {
		if (kbhit())
		{
			switch (tolower(getch()))
			{
			case ' ':
				c = ' ';
				break;
			case 'x': case 'X':
				exit(0);
				break;
			default:
				break;
			}
		}
	} while (c != ' ');
	borrarMapa();
}
char menuEnd(bool win, short score)
{
	char c;
	if (win)
	{
		Console::SetCursorPosition(25, 10);
		cout << "FELICIDADES!!!";
	}
	else {
		Console::SetCursorPosition(20, 10);
		cout << "VUELVE A INTENTARLO!!!";
	}
	Console::SetCursorPosition(26, 18);
	cout << "SCORE: " << score;
	Console::SetCursorPosition(13, 20);
	cout << "PRESIONA 'ESPACIO' PARA JUGAR DE NUEVO";
	Console::SetCursorPosition(16, 22);
	cout << "PRESIONA 'X' PARA VOLVER AL MENU";
	do {
		if (kbhit())
		{
			switch (tolower(getch()))
			{
			case ' ':
				c = ' ';
				break;
			case 'x': case 'X':
				c='x';
				break;
			default:
				break;
			}
		}
	} while (!(c == ' '||c=='x'));
	return c;
}
void game(bool &generalWin, short &totalScore)
{
	bool gameOver = false;

	//player
	const short x0 = 19;
	const short y0 = 30;
	short x = x0, y = y0;
	short dx = 0, dy = 0;
	short lives = 3;
	bool perdioVida = false;
	short score = 0;

	//Balas
	short numeroBalas = 5;

	short* balasX = new short[numeroBalas];
	short* balasY = new short[numeroBalas];
	bool* balasFire = new bool[numeroBalas];
	short* balasDBY = new short[numeroBalas];
	short* disparos = new short[numeroBalas];

	short bx = NULL;
	short by = NULL;
	bool fire = false;
	short dby = 0;

	//Enemies
	short numeroEnemigos = 15;
	short enemigosMuertos = 0;
	short id;

	short* eneX = new short[numeroEnemigos];
	short* eneY = new short[numeroEnemigos];
	short* eneDX = new short[numeroEnemigos];
	short* eneDY = new short[numeroEnemigos];
	bool* eneVivos = new bool[numeroEnemigos];

	//Comentarios
	short comX = WIDTH + 14;
	short scoreY = 10;
	short timeY = 15;
	short livesY = 20;

	//Time
	short ms = 0;
	short seg = 0, min = 0;
	short scoreTime;

	//Enemies settings
	for (int i = 0; i < numeroEnemigos; i++)
	{
		eneX[i] = rand() % WIDTH;
		//eneY[i] = rand() % HEIGHT/2;

		eneY[i] = rand() % 10 - 10;
		/*
		do {
			eneDX[i] = rand() % 3 - 1;
			eneDY[i] = rand() % 3 - 1;
		} while (eneDX[i]==0||eneDY[i]==0);
		*/
		eneDX[i] = 0;
		eneDY[i] = 1;
		eneVivos[i] = true;
	}

	//Balas settings
	for (int i = 0; i < numeroBalas; i++)
	{
		balasX[i] = NULL;
		balasY[i] = NULL;
		balasFire[i] = false;
		balasDBY[i] = 0;
		disparos[i] = NULL;
	}
	setMap(WIDTH + 1, WIDTH + 4);
	while (!gameOver)
	{
		borrar(x, y);
		if (kbhit())
		{
			switch (tolower(getch()))
			{
			case 'w':
				dy = -1;
				break;
			case 's':
				dy = 1;
				break;
			case 'a':
				dx = -1;
				break;
			case 'd':
				dx = 1;
				break;
			case ' ':
				for (int i = 0; i < numeroBalas; i++) {
					if (!balasFire[i]) {
						balasFire[i] = true;
						balasX[i] = x;
						balasY[i] = y;
						balasDBY[i] = -1;
						disparos[i] = i + 1;
						break;
					}
				}
			default:
				break;
			}
		}
		mover(dx, dy, x, y);
		Console::ForegroundColor = ConsoleColor::Blue;
		dibujar(x, y, 'W');

		//Disparo de bala
		for (int i = 0; i < numeroBalas; i++)
		{
			/*if (balasFire[i])
			{
				borrar(balasX[i], balasY[i]);
				movBala(balasFire[i], balasX[i], balasY[i], balasDBY[i], disparos[i]);
				if (balasX[i] != NULL && balasY[i] != NULL)
				{
					dibujar(balasX[i], balasY[i], '.');
				}
			}*/
			Console::ForegroundColor = ConsoleColor::Blue;
			disparoBala(balasFire[i], balasX[i], balasY[i], balasDBY[i], disparos[i]);
		}

		//EnemiesOnGame
		for (int i = 0; i < numeroEnemigos; i++)
		{
			/*if (eneVivos[i])
			{

				if (eneY[i] < 0) {
					eneY[i]++;
				}
				else if (eneY[i] == HEIGHT-1) {
					borrar(eneX[i], eneY[i]);
					eneX[i] = rand() % WIDTH;
					eneY[i] = rand() % 10 - 10;
				}
				else {
					borrar(eneX[i], eneY[i]);
					moverEne(eneDX[i], eneDY[i], eneX[i], eneY[i]);
					dibujar(eneX[i], eneY[i], '*');
				}
				if (x == eneX[i] && y == eneY[i]) {
					lives--;
					_sleep(1000);
					x = x0;
					y = y0;
					borrar(eneX[i], eneY[i]);
					eneX[i] = rand() % WIDTH;
					eneY[i] = rand() % 10 - 10;
				}
				if (lives == 0) gameOver=true;
			}
			*/
			Console::ForegroundColor = ConsoleColor::DarkRed;
			enemiesOnGame(eneVivos[i], eneX[i], eneY[i], eneDX[i], eneDY[i], lives, x, y, x0, y0, perdioVida);
		}
		if (perdioVida) {
			for (int i = 0; i < numeroEnemigos; i++) {
				if (eneVivos[i] && (eneY[i] >= 0 && eneY[i] <= HEIGHT)) {
					borrar(eneX[i], eneY[i]);
					resetEnemies(eneX[i], eneY[i]);
				}
			}
			for (int i = 0; i < numeroBalas; i++) {
				if (balasX[i] != NULL) {
					borrar(balasX[i], balasY[i]);
					balasX[i] = NULL;
					balasY[i] = NULL;
					balasFire[i] = false;
					balasDBY[i] = 0;
					disparos[i] = NULL;
				}
			}
			perdioVida = false;
		}
		if (lives == 0) { gameOver = true; generalWin = false; totalScore = score; }

		//DetectaEnemigo
		for (int i = 0; i < numeroBalas; i++)
		{
			id = disparos[i];
			if (id) //id!=NULL
			{
				for (int j = 0; j < numeroEnemigos; j++)
				{
					if (balasX[id - 1] == eneX[j] && ((balasY[id - 1] == eneY[j] || (balasY[id - 1] - 1 == eneY[j])))
						&& eneVivos[j])
					{
						enemigosMuertos++;
						eneVivos[j] = false;
						if (balasY[id - 1] - 1 >= 0) {
							borrar(eneX[j], eneY[j]);
							borrar(balasX[id - 1], balasY[id - 1]);
						}
						balasX[id - 1] = NULL;
						balasY[id - 1] = NULL;
						balasFire[id - 1] = false;
						balasDBY[id - 1] = false;
						disparos[i] = NULL;
						score += 10;
					}
				}
			}
		}
		if (enemigosMuertos == numeroEnemigos) { 
			gameOver = true; 
			generalWin = true; 
			scoreTime = seg <= 60 ? (60 - seg) * 10 : 0;
			totalScore = score+scoreTime+50*(lives-1);
		}
		ms++;
		Console::ForegroundColor = ConsoleColor::White;
		timing(ms, seg, min);
		comments(comX, scoreY, score, timeY, min, seg%60, livesY, lives);
		_sleep(100);
	}

	delete[]eneX;
	delete[]eneY;
	delete[]eneDX;
	delete[]eneDY;
	delete[]eneVivos;

	delete[]balasX;
	delete[]balasY;
	delete[]balasFire;
	delete[]balasDBY;
	delete[]disparos;
}
int main()
{	
	//Settings
	srand(time(0));
	Console::CursorVisible = false;
	Console::SetWindowSize(WIDTH+20, HEIGHT);
	Console::ForegroundColor = ConsoleColor::White;

	bool win;
	short totalScore;
	char c;
	
	while (true)
	{
		menuStart();
		do {
			game(win, totalScore);
			borrarMapa();
			_sleep(500);
			c = menuEnd(win, totalScore);
			borrarMapa();
		} while (c == ' ');	
	}

	char carar = _getch();
	return 0;
}