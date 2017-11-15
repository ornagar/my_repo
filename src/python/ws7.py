#!/usr/bin/python3

import curses
from time import sleep
from curses import KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN
from random import randint

X_SIZE = 35
Y_SIZE = 20
START_XY = [10,10]
TIMEOUT = 120
SNAKE_CHAR = '#'
FOOD_CHAR = '*'

class Food(object):

    def __init__(self, window):
        self.pos_x = randint(1, X_SIZE-2)
        self.pos_y = randint(1, Y_SIZE-2)
        self.char = FOOD_CHAR
        self.window = window

    def show(self):
         self.window.addstr(self.pos_y, self.pos_x, self.char)

    @property
    def pos(self):
        return self.pos_x, self.pos_y

class Body(object):

    def __init__(self, window, head, last_part):
        self.head = head
        self.pos_x = last_part.last_pos_x
        self.pos_y = last_part.last_pos_y
        self.char = SNAKE_CHAR
        self.window = window

        # links the body part to its previous one, which will be 'followed'
        self.last_part = last_part
        self.last_pos_x = self.pos_x
        self.last_pos_y = self.pos_y

    def show(self):
         self.window.addstr(self.pos_y, self.pos_x, self.char)

    def walk(self):
        # updates itself's last position to its current one
        self.last_pos_x = self.pos_x
        self.last_pos_y = self.pos_y

        # updates itself's position to the previous part's last position
        self.pos_x = self.last_part.last_pos_x
        self.pos_y = self.last_part.last_pos_y

    @property
    def pos(self):
        return self.pos_x, self.pos_y

class Snake(object):

    def __init__(self, window):
        self.pos_x = START_XY[0]
        self.pos_y = START_XY[1]
        self.pos_dir = 'LEFT'
        self.window = window
        self.char = SNAKE_CHAR
        self.body_count = 0
        self.last_pos_x = self.pos_x
        self.last_pos_y = self.pos_y

        # reference to the snake's body as a list, starting with one element
        self.body = []
        self.body.append(Body(window,self,self))

    def show(self):
         self.window.addstr(self.pos_y, self.pos_x, self.char)

    # updates itself's positiond
    def walk(self):
        self.last_pos_x = self.pos_x
        self.last_pos_y = self.pos_y
        if self.pos_dir == 'LEFT':
                self.pos_x -= 1

        if self.pos_dir == 'RIGHT':
                self.pos_x += 1

        if self.pos_dir == 'UP':
                self.pos_y -= 1

        if self.pos_dir == 'DOWN':
                self.pos_y += 1

    def turn(self, new_dir):
        # delays the game for some miliseconds, as the game does not wait for
        # 'TIMEOUT' when a key is pressed. this cretes the feeling of a more
        # fluid game
        sleep( (TIMEOUT / 1000 ) - 0.030)

        if new_dir == 'LEFT':
            if self.pos_dir != 'RIGHT':
                self.pos_dir = 'LEFT'

        if new_dir == 'RIGHT':
            if self.pos_dir != 'LEFT':
                self.pos_dir = 'RIGHT'

        if new_dir == 'UP':
            if self.pos_dir != 'DOWN':
                self.pos_dir = 'UP'

        if new_dir == 'DOWN':
            if self.pos_dir != 'UP':
                self.pos_dir = 'DOWN'

    def eat(self, food):
        del food
        self.body.append(Body(window,self,self.body[self.body_count]))
        self.body_count += 1

    @property
    def pos(self):
        return self.pos_x, self.pos_y

if __name__ == '__main__':

    curses.initscr()
    window = curses.newwin(Y_SIZE, X_SIZE, 0, 0)
    window.timeout(TIMEOUT)
    window.keypad(1)
    curses.noecho()
    curses.curs_set(0)
    window.border(0)

    snake = Snake(window)
    food = Food(window)

    while True:
        window.clear()
        window.border(0)

        food.show()
        snake.show()

        for i in range(0,snake.body_count+1,1):
            snake.body[i].show()

        window.addstr(19, 4, 'Score: {}'.format(snake.body_count))

        press = window.getch()
        if press == KEY_LEFT:
            snake.turn('LEFT')

        if press == KEY_RIGHT:
            snake.turn('RIGHT')

        if press == KEY_UP:
            snake.turn('UP')

        if press == KEY_DOWN:
            snake.turn('DOWN')

        snake.walk()

        # breaks the game if head goes outside the screen
        if (snake.pos_x > X_SIZE-2 or snake.pos_x < 1
            or  snake.pos_y > Y_SIZE-2 or snake.pos_y < 1):
            sleep(0.6)
            curses.endwin()
            print('\nYOU LOST!')
            break

        # breaks the game if head meets any body part
        if any([parts.pos == snake.pos for parts in snake.body]):
            sleep(0.6)
            curses.endwin()
            print('\nYOU LOST!')
            break

        if snake.pos == food.pos:
            snake.eat(food)
            food = Food(window)
            # grants the food will not be in the same pos as the snake
            while ( any([parts.pos == food.pos for parts in snake.body])
            or snake.pos == food.pos ):
                food = Food(window)

        for i in range(0,snake.body_count+1,1):
            if i == 0:
                snake.body[i].walk()
            else:
                snake.body[i].walk()
