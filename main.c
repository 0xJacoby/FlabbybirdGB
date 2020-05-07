#include <gb/gb.h> 
#include <stdio.h>
#include "Sprites.c"

UBYTE pipe_sprites[26];
UBYTE bird_sprites[12];

// pipe
void pipe_setup() {
    UINT8 i;

    // rendering sprites

    set_sprite_tile(0, 20);
    set_sprite_tile(1, 21);
    set_sprite_tile(2, 20);
    set_sprite_tile(3, 21);

    set_sprite_prop(2,S_FLIPY);
    set_sprite_prop(3,S_FLIPY);

    pipe_sprites[0] = 0;
    pipe_sprites[1] = 1;
    pipe_sprites[2] = 2;
    pipe_sprites[3] = 3;

    for (i=0;i<=22;i++) {
        if (i % 2 == 0) {
            set_sprite_tile((i+4), 24);
            pipe_sprites[i+4] = i+4;
        } else {
            set_sprite_tile((i+4), 25);
            pipe_sprites[i+4] = i+4;
        }
    }
}

void pipe_move(UINT8 x, UINT8 y) {
    // y: max=144 min=64 

    UINT8 i;
    UINT8 lower_amount = ((144-y)/4);
    // pipe tops
    move_sprite(pipe_sprites[0], x, y);
    move_sprite(pipe_sprites[1], (x+8), y);
    move_sprite(pipe_sprites[2], x, (y-48));
    move_sprite(pipe_sprites[3], (x+8), (y-48));

    for (i=4;i<(lower_amount+4);i++) {
        if (i % 2 == 0) {
            move_sprite(pipe_sprites[i], x, (y+((((i-4)/2)*8)+8)));
        } else {
            move_sprite(pipe_sprites[i], (x+8), (y+((((i-5)/2)*8)+8)));
        }
    }

    for(i=(4+lower_amount);i<((4+lower_amount)+(22-lower_amount));i++) {
        if (i % 2 == 0) {
            move_sprite(pipe_sprites[i], x, (y-((((i-(4+lower_amount))/2)*8)+56))); 
        } else {
            move_sprite(pipe_sprites[i], (x+8), (y-((((i-(5+lower_amount))/2)*8)+56)));
        }
    }

}

// bird
void bird_setup() {

}

void bird_move() {

}



void pDelay(UINT8 numloops){
	// better delay method
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void main() {
	set_sprite_data(0, 26, Sprites);
    pipe_setup();
    pipe_move(80,80);

	SHOW_SPRITES;
}
