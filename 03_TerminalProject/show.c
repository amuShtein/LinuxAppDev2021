#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define LONG_INFO "PRESS ESC TO EXIT, ARROWS TO NAVIGATE, PG UP/PG DN TO FAST NAVIGATION"
#define INFO "ESC - EXIT, ARROWS, PG UP/PF DN - NAVIGATION"
#define SHORT_INFO "ESC # ARROWS # PG UP/DN"
#define NO_INFO ""

enum { DX = 3, LINE_LEN = 2048 };


struct lines {
    char *line;
    int len;
    struct lines *next, *prev;
};

struct lines *read_file(FILE *in) {
    struct lines *head, *cur = malloc(sizeof(struct lines));
    head = cur;
    int len;

    char *str = malloc(LINE_LEN);
    while(fgets(str, LINE_LEN, in)) {

        // printf("'%s'\n", str);
        len = strlen(str);
        // printf("%d\n", len);
        if(str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        // printf("%s\n", str);
        str = realloc(str, len + 1);
        cur->next = malloc(sizeof(struct lines));
        cur->next->prev = cur;
        cur = cur->next;
        cur->line = str;
        cur->len = len;
        

        str = malloc(LINE_LEN);
    }
    
    free(str);
    cur->next = NULL;
    struct lines *tmp = head->next;
    free(head);
    head = tmp;
    head->prev = NULL;

    return head;
}

void print_lines(struct lines *head) {
    while (head) {
        printf("%s\n", head->line);
        head = head->next;
    }
}

void free_lines(struct lines *head) {
    while (head) {
        struct lines *next = head->next;
        free(head->line);
        free(head);
        head = next;
    }
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("No arguments passed\n");
        return 0;
    }

    FILE *in = fopen(argv[1], "r");
    if(in <= 0) {
        printf("Cannot open file %s\n", argv[1]);
        return 0;
    }

    struct lines *head = read_file(in);
    // print_lines(head);
    // return 0;

    WINDOW *win;
    int c = -1;

    setlocale(LC_ALL, "ru_RU.UTF-8");
    initscr();
    noecho();
    cbreak();

    printw("File: ");
    printw("%s\n", argv[1]);
    refresh();

    win = newwin(LINES - 2*DX, COLS - 2*DX, DX, DX);

    keypad(win, TRUE);
    scrollok(win, TRUE);

    int h = LINES - 2*DX - 2 - 1, w = COLS - 2*DX - 2;

    const char *info;
    if(strlen(LONG_INFO) <= w - 3) {
        info = LONG_INFO;
    } else if(strlen(INFO) <= w - 3) {
        info = INFO;
    } else if(strlen(SHORT_INFO) <= w - 3) {
        info = SHORT_INFO;
    } else {
        info = NO_INFO;
    }


    struct lines *cur = head;
    struct lines *tail = head;
    while(tail->next) {
        tail = tail->next;
    }
    for(int i = 0; i < h - 1; i++) {
        if(tail->prev) {
            tail = tail->prev;
        } else {
            break;
        }
    }


    struct lines *tmp = cur;
    
    int line_start = 0;
    int max_start = 1;
    int cnt = 0;
    printw("cnt = %d\n", cnt);
    do {
        switch (c) {
        case -1:
            break;
        case 32:
        case KEY_DOWN:
            if(cur->next != NULL && cur != tail) {
                cur = cur->next;
                break;
            }

            goto skip_refresh;
        case KEY_UP:
            if(cur->prev != NULL) {
                cur = cur->prev;
                break;
            }

            goto skip_refresh;
        case KEY_LEFT:
            if(line_start > 0) {
                line_start--;
                break;
            }
        
          goto skip_refresh;
        case KEY_RIGHT:
            if(line_start < max_start) {
                line_start++;
                break;
            }

            goto skip_refresh;
        case KEY_PPAGE:
            if(cur != head) {
                cur = head;
                break;
            }

            goto skip_refresh;
        case KEY_NPAGE:
            if(cur != tail) {
                cur = tail;
                break;
            }

            goto skip_refresh;
        default:
            goto skip_refresh;
        }
    
        tmp = cur;
        werase(win);
        wprintw(win, " \n");
        max_start = 0;
        for(int i = 0; (i < h) && tmp; i++) {
            int len = tmp->len;
            wprintw(win, " ");
            for(int j = line_start; j - line_start < w && j < len; j++) {
                wprintw(win, "%c", (tmp->line)[j]);
            }
            if(max_start < len) {
                max_start = len;
            }
            wprintw(win, "\n");

            tmp = tmp->next;
        }

        box(win, 0, 0);
        
        wrefresh(win);
        move(1, 6);
        printw("%d\n", cnt);
        move(LINES - DX - 2 + 1, DX + 2);
        printw(info);
        move(LINES - DX - 2 + 1, DX + 2);
        refresh();
        cnt++;
skip_refresh:
        ;
    } while ((c = wgetch(win)) != 27);
    
    endwin();
    free_lines(head);
    
    return 0;
}