#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include "Sprites.c"
#include "bkg_data.c"
#include "bkg_map.c"

UBYTE pipe_sprites[26];

// pipe
void pipe_setup()
{
    UINT8 i;

    // rendering sprites

    set_sprite_tile(0, 20);
    set_sprite_tile(1, 21);
    set_sprite_tile(2, 20);
    set_sprite_tile(3, 21);

    set_sprite_prop(2, S_FLIPY);
    set_sprite_prop(3, S_FLIPY);

    pipe_sprites[0] = 0;
    pipe_sprites[1] = 1;
    pipe_sprites[2] = 2;
    pipe_sprites[3] = 3;

    for (i = 0; i < 22; i++)
    {
        if (i % 2 == 0)
        {
            set_sprite_tile((i + 4), 24);
            pipe_sprites[i + 4] = i + 4;
        }
        else
        {
            set_sprite_tile((i + 4), 25);
            pipe_sprites[i + 4] = i + 4;
        }
    }
}

void pipe_move(UINT8 x, UINT8 y)
{
    // y: max=144 min=64

    UINT8 i;
    UINT8 lower_amount = ((144 - y) / 4);
    // pipe tops
    move_sprite(pipe_sprites[0], x, y);
    move_sprite(pipe_sprites[1], (x + 8), y);
    move_sprite(pipe_sprites[2], x, (y - 48));
    move_sprite(pipe_sprites[3], (x + 8), (y - 48));

    for (i = 4; i < (lower_amount + 4); i++)
    {
        if (i % 2 == 0)
        {
            move_sprite(pipe_sprites[i], x, (y + ((((i - 4) / 2) * 8) + 8)));
        }
        else
        {
            move_sprite(pipe_sprites[i], (x + 8), (y + ((((i - 5) / 2) * 8) + 8)));
        }
    }

    for (i = (4 + lower_amount); i < ((4 + lower_amount) + (22 - lower_amount)); i++)
    {
        if (i % 2 == 0)
        {
            move_sprite(pipe_sprites[i], x, (y - ((((i - (4 + lower_amount)) / 2) * 8) + 56)));
        }
        else
        {
            move_sprite(pipe_sprites[i], (x + 8), (y - ((((i - (5 + lower_amount)) / 2) * 8) + 56)));
        }
    }
}

void pipe_scroll(UINT8 x, UINT8 y)
{
    UINT8 i;

    for (i = 0; i < 26; i++)
    {
        scroll_sprite(pipe_sprites[i], x, y);
    }
}

// bird
void bird_setup()
{
    move_sprite(26, 72, 68);
    move_sprite(27, 80, 68);
    move_sprite(28, 72, 76);
    move_sprite(29, 80, 76);
}

void bird_state(UINT8 state)
{
    switch (state)
    {
    case 0:
        set_sprite_tile(26, 0);
        set_sprite_tile(27, 1);
        set_sprite_tile(28, 4);
        set_sprite_tile(29, 5);
        break;
    case 1:
        set_sprite_tile(26, 2);
        set_sprite_tile(27, 3);
        set_sprite_tile(28, 6);
        set_sprite_tile(29, 7);
        break;
    case 2:
        set_sprite_tile(26, 8);
        set_sprite_tile(27, 9);
        set_sprite_tile(28, 12);
        set_sprite_tile(29, 13);
        break;
    }
}

void bird_scroll(UINT8 x, UINT8 y)
{
    UINT8 i;

    for (i = 0; i <= 4; i++)
    {
        scroll_sprite((i + 26), x, y);
    }
}

void pDelay(UINT8 numloops)
{
    // better delay method
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

void main()
{
    UINT8 pipes_x = 128;
    UINT8 pipes_y = 96;

    set_sprite_data(0, 26, Sprites);
    set_bkg_data(0, 186, bkg_data);
    set_bkg_tiles(0, 0, 32, 18, bkg_map);

    pipe_setup();
    bird_state(0);
    bird_setup();

    pipe_move(pipes_x, pipes_y);

    SHOW_SPRITES;
    SHOW_BKG;
    //main game loop
    while (1)
    {
        if (pipes_x == 240)
        {
            pipes_x = 160;

            pipe_move(pipes_x, ((((rand() & 9) + 1) * 8) + 64));
        }
        else
        {
            pipes_x -= 1;
            pipe_scroll(-1, 0);
        }

        wait_vbl_done();
    }
}
