        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (!playing)
            {
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= 300 && x <= 500 && y >= 300 && y <= 350)
                    {
                        playing = true;
                        continue;
                    }
                    if (x >= 300 && x <= 500 && y >= 375 && y <= 425)
                    {
                        running = false;
                        break;
                    }
                }
            }
            if (win)
            {
                continue;
            }
            if (playing && event.type == SDL_KEYUP)
            {
                p->is_going_right = 0;
            }

            if (playing && !win && event.type == SDL_KEYDOWN)
            {
                double player_delta =  delta_time(&last_update);
                int key =  event.key.keysym.sym;
                if (key == SDLK_UP)
                {
                    p->is_in_jump = 1;
                }
                if (key == SDLK_LEFT)
                {
                    p->is_going_right = -1;
                    int offset = p->rect->w * player_delta / -TIME_DELTA;
                    if (isblock(p->rect->x + p->rect->w, p->rect->y, &finish, 1))
                    {
                        win = true;
                    }
                    if (p->pos->x <= 50)
                    {

                    }
                    else if (p->rect->x < 300)
                    {
                        move_blocks(blocks, offset * 2, num_blocks);
                        move_player(bad, offset * 2);
                        //p->pos->x += offset * 2;

                        move_block(&hole, offset * 2);
                        move_block(&finish, offset * 2);
                    }
                    else
                    {
                        if (!isblock(p->rect->x - p->rect->w, p->rect->y, blocks, num_blocks))
                        {
                            p->rect->x += offset;
                            p->pos->x += offset;
                        }
                        if (isHit(bad, p->rect->x - p->rect->w, p->rect->y))
                        {
                            Mix_PlayChannel(-1, applause, 0);
                            p->life -= 10;
                        }

                    }
                }
                else if (playing && !win && key == SDLK_RIGHT)
                {
                    p->is_going_right = 1;
                    int offset = p->rect->w * player_delta / TIME_DELTA;

                    if (isblock(p->rect->x + p->rect->w, p->rect->y, &finish, 1))
                    {
                        win = true;
                    }
                    if (p->rect->x > 400)
                    {
                        puts("Move blocks to the right");
                        move_blocks(blocks, offset * 2, num_blocks);
                        move_player(bad, offset * 2);
                        move_block(&hole, offset * 2);
                        move_block(&finish, offset * 2);
                        //p->pos->x += offset * 2;
                    }
                    else
                    {
                        printf("Going right by %d\n", offset);
                        if (!isblock(p->rect->x + p->rect->w, p->rect->y, blocks, num_blocks))
                        {
                            p->rect->x += offset;
                            //p->pos->x += offset;
                        }
                        if (isHit(bad, p->rect->x + p->rect->w, p->rect->y))
                        {
                            Mix_PlayChannel(-1, applause, 0);
                            p->life -= 10;
                        }
                    }

                }
            }
        }
