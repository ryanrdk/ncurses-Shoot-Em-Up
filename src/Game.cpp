/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:04:00 by akay              #+#    #+#             */
/*   Updated: 2019/06/09 15:28:11 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Game.hpp"

/* DEFAULT
   FUNCTIONS */
Game::Game(void)
{
    return ;
}

Game::Game(Player player)
{
    this->player = player;
}

Game::Game(Game const &obj)
{
    *this = obj;
}

Game    &Game::operator=(Game const &obj)
{
    (void)obj;
    return (*this);
}

Game::~Game()
{
    return ;
}




/* SETTER
   FUNCTIONS */
void    Game::setTermHeight(int termHeight)
{
    this->_termHeight = termHeight;
}

void    Game::setTermWidth(int termWidth)
{
    this->_termWidth = termWidth;
}

void    Game::setTermDimensions(int termHeight, int termWidth)
{
    setTermHeight(termHeight);
    setTermWidth(termWidth);
}

/* GETTER
   FUNCTIONS */
int     Game::getTermHeight()
{
    return (this->_termHeight);
}

int     Game::getTermWidth()
{
    return(this->_termWidth);
}

WINDOW  *Game::createWindow(int height, int width, int coY, int coX)
{
    WINDOW  *win = newwin(height, width, coY, coX);
    box(win, 0 , 0);
    
    return (win);
}

void    Game::displayPlayer(WINDOW *win, Player player)
{
    mvwprintw(win, player.getV(), player.getH(), "0");
}

void   Game::displayEnemy(WINDOW *win, Enemy &enemy, int i)
{
    (void)i;
    enemy.setH(enemy.getH() - 1);
    if (enemy.getH() < 1)
    {
        enemy.resetEnemy(this->getTermWidth(), this->getTermHeight() - 5);
    }
    mvwprintw(win, enemy.getV(), enemy.getH(), "X");
}


void        Game::getAction(WINDOW *win, int termHeight, int termWidth)
{
    int move = wgetch(win);
    switch(move)
    {
        case KEY_UP:
            this->player.moveUp(termHeight);
            break;
        case KEY_DOWN:
            this->player.moveDown(termHeight);
            break;
        case KEY_LEFT:
            this->player.moveLeft();
            break;
        case KEY_RIGHT:
            this->player.moveRight(termWidth);
            break;
        default:
            break;
    }
}

void    Game::windowClean(WINDOW *win) {
    // werase(win);
    wclear(win);
    box(win, 0, 0);
}

void    Game::menu(WINDOW *win, int yMax, int xMax) {
    int x, y;
    int c = 0;
	int i = 0;
    char list[3][9] = {"NEW GAME", "HELP", "QUIT"};
    char item[9];

    for (int t = 0; t < 3; t++) {
        x = xMax / 2;
        y = yMax / 2;
        move(10, 10);
        printw("Rush-Type");
        if (t == 0)
            wattron(win, A_STANDOUT);  // highlights the first item.
        else
            wattroff(win, A_STANDOUT);
        sprintf(item, "%-7s", list[t]);
        mvwprintw(win, t + 1, 2, "%s", item);
    }

    wrefresh(win);  // update the terminal screen
    while (c != 'q') {
        c = wgetch(win);
		
        sprintf(item, "%-7s", list[i]);
		
        mvwprintw(win, i + 1, 2, "%s", item);
        // use a variable to increment or decrement the value based on the input.
        switch (c) {
            case KEY_UP:
                i--;
                i = (i < 0) ? 2 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i > 2) ? 0 : i;
                break;
        }
        // now highlight the next item in the list.
        wattron(win, A_STANDOUT);

        sprintf(item, "%-7s", list[i]);
        mvwprintw(win, i + 1, 2, "%s", item);
        wattroff(win, A_STANDOUT);
    }
    werase(win);
}

int     Game::getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int     Game::getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

void    Game::generateEnemy(int h, int v, int id)
{
    this->enemies[id].setH(h);
    this->enemies[id].setV(v);
    this->enemies[id].randomStart(this->getTermWidth(), this->getTermHeight() - 2);
}
