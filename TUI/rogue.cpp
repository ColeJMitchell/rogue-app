//
// Created by cojmi on 3/15/2024.
//
#include <iostream>
#include "ncurses.h"
#include <string>
#include <Model.h>
#include "Configuration.h"
#include <filesystem>

// forward reference of function with a passed reference
// to an object
void draw_map_screen(Model &m, int action);

void game_end(Model &m);

int main()
{
    Configuration c("../","config.txt");
    Model m(c.getValue("database_path"));

    // initialize the screen
    initscr();

    // hide the cursor from view (comment this line out for debugging)
    curs_set(0);

    // disables line buffering and erase/kill character-processing
    // (interrupt and flow control characters are unaffected),
    // making characters typed by the  user  immediately
    // available to the program
    cbreak();

    // control whether characters  typed  by  the user  are echoed
    // by getch as they are typed
    noecho();

    // the user can press a function key (such as an arrow key) and
    // getch returns a single value representing the  function  key,
    // as in KEY_LEFT
    keypad(stdscr, TRUE);

    // initialize the interaction loop to run
    bool continue_looping = true;

    draw_map_screen(m, 1);
    do {
        int health = m.return_health();

        mvprintw(1, 1, "q - quit program");

        // draw the new screen
        refresh();

        // obtain character from keyboard
        int ch = getch();

        switch (ch) {
            case 'q':
                continue_looping = false;
                break;
            default:
                // draw the current screen
                switch (m.screen_page) {
                    case 0: {
                        draw_map_screen(m, ch);
                        //prints current player health
                        mvprintw(1,30,"Player Health: %d",health);
                        mvprintw(1,60,"Enemies Slain: %d",m.enemies_slain);
                        break;
                    }
                    case 1:{
                        game_end(m);
                        attron(A_BOLD);
                        //clears health and num enemies slain on death
                        mvprintw(1,30,"                    ");
                        mvprintw(1,60,"                     ");
                        mvprintw(25, 102, "YOU DIED");
                        break;
                    }
                    case 2:{
                        game_end(m);
                        attron(A_BOLD);
                        mvprintw(25, 90, "YOU OBTAINED THE AMULET OF YENDOR!!!");
                        break;
                    }
                }
        }
    } while(continue_looping);

    // cleanup the window and return control to bash
    endwin();

    std::cout << "exiting main\n";
    return 0;
}

void game_end(Model &m) {
    int row_offset = 5;
    int col_offset = 0;
    //makes ever charachter in buffer blank
    m.wipe_screen();
    //displays the buffer
    for (int row = 0; row < m.max_rows(); row++) {
        for (int col = 0; col < m.max_cols(); col++) {
            mvprintw(row + row_offset, col + col_offset, "%c", m.buffer_value(row, col));
        }
    }
}



// a function for drawing the map screen
void draw_map_screen(Model &m, int action) {

    int row_offset = 5;
    int col_offset = 0;

    // clear screen return cursor to (0,0)
    clear();
    //set the constraints before moving
    m.set_constraint();
    // perform action handling
    switch (action) {
        case '2':
            // just switched to this screen
            break;
        case KEY_DOWN:
            m.move_down();
            break;
        case KEY_UP:
            m.move_up();
            break;
        case KEY_LEFT:
            m.move_left();
            break;
        case KEY_RIGHT:
            m.move_right();
            break;
    }

    // this will reload the buffer in the data class
    m.reload_dungeon();

    // draw the buffer
    for (int row = 0; row < m.max_rows(); row++) {
        for (int col = 0; col < m.max_cols(); col++) {
            mvprintw(row + row_offset, col + col_offset, "%c", m.buffer_value(row, col));
        }
    }

}

