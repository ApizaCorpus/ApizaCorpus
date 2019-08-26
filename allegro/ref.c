#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
 
typedef struct character character;

struct character {
   int   size;
   int   x;
   int   y;
   int   x_speed;
   int   y_speed;
};

const char * AUDIO_SAMPLE_PATH = "assets/sample.wav"; 
const char * BITMAP_PLAYER_PATH = "assets/fly.png"; 
const char * BITMAP_ENEMY_PATH = "assets/spider.png";
const char * FONT_PATH = "assets/roboto.ttf"; 
const float FPS = 24;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;
const int ENEMY_SIZE = 96;
const int DEFAULT_SPEED = 5;
const int MAX_SPEED = 100;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

void initPlayer(character * player){
   player->size = PLAYER_SIZE;
   player->x = SCREEN_W / 4.0 - PLAYER_SIZE / 2.0;
   player->y = SCREEN_H / 2.0 - PLAYER_SIZE / 2.0;
   player->x_speed = DEFAULT_SPEED;
   player->y_speed = DEFAULT_SPEED;
}

void initEnemy(character * enemy){
   enemy->size = ENEMY_SIZE;
   enemy->x = 3 * SCREEN_W / 4.0 - ENEMY_SIZE / 2.0;
   enemy->y = SCREEN_H / 2.0 - ENEMY_SIZE / 2.0;
   enemy->x_speed = rand()%(DEFAULT_SPEED*2)+2;
   enemy->y_speed = rand()%(DEFAULT_SPEED*2)+2;
}

void movePlayer(character * player, bool key[]){
   if(key[KEY_UP] ) {
      player->y -= player->y_speed;
   }
   if(key[KEY_DOWN]) {
      player->y += player->y_speed;
   }
   if(key[KEY_LEFT]) {
      player->x -= player->x_speed;
   }
   if(key[KEY_RIGHT]) {
      player->x += player->x_speed;
   }

   if(player->y < 0) player->y = 0;
   else if (player->y > SCREEN_H - player->size) player->y = SCREEN_H - player->size;

   if(player->x < 0) player->x = 0;
   else if (player->x > SCREEN_W - player->size) player->x = SCREEN_W - player->size;
}

void moveEnemy(character * enemy){
   enemy->y += enemy->y_speed;
   enemy->x += enemy->x_speed;

   if(enemy->y < 0){
      enemy->y = 0;
      enemy->y_speed *= -1;
   }else if (enemy->y > SCREEN_H - enemy->size){
      enemy->y = SCREEN_H - enemy->size;
      enemy->y_speed *= -1;
   }

   if(enemy->x < 0){
      enemy->x = 0;
      enemy->x_speed *= -1;
   }else if (enemy->x > SCREEN_W - enemy->size){
      enemy->x = SCREEN_W - enemy->size;
      enemy->x_speed *= -1;
   }
}

void speedUp(character * c){
   if( c->y_speed < MAX_SPEED && c-> x_speed < MAX_SPEED){
      c->y_speed *= 1.5;
      c->x_speed *= 1.5;
   }
}

bool checkCollision(character c1, character c2){
   if ((c1.x > c2.x + c2.size - 1) ||
      (c1.y > c2.y + c2.size - 1) ||
      (c2.x > c1.x + c1.size - 1) || 
      (c2.y > c1.y + c1.size - 1))
   {
      // no collision
      return 0;
   }
   // collision
   return 1;
}

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_TIMER *enemyTimer = NULL;
   ALLEGRO_SAMPLE *sample=NULL;
   ALLEGRO_BITMAP *player_bitmap = NULL;
   ALLEGRO_BITMAP *enemy_bitmap = NULL;
   
   character player;
   character enemy;
   int score;
   char score_str[11]; 
   int highscore;
   char highscore_str[11]; 

   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;

   //Initialization 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }

   if(!al_init_image_addon()) {
      fprintf(stderr, "Failed to initialize al_init_image_addon!\n");
      return 0;
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();
   ALLEGRO_FONT *font = al_load_ttf_font(FONT_PATH,32,0);

   sample = al_load_sample( AUDIO_SAMPLE_PATH );
   if (!sample) {
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

   enemyTimer = al_create_timer(5.0);
   if(!enemyTimer) {
      fprintf(stderr, "failed to create timer!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      al_destroy_timer(enemyTimer);
      return -1;
   }
 
   player_bitmap = al_create_bitmap(PLAYER_SIZE, PLAYER_SIZE);
   if(!player_bitmap) {
      fprintf(stderr, "failed to create player bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_timer(enemyTimer);
      return -1;
   }


   enemy_bitmap = al_create_bitmap(ENEMY_SIZE, ENEMY_SIZE);
   if(!enemy_bitmap) {
      fprintf(stderr, "failed to create enemy bitmap!\n");
      al_destroy_bitmap(player_bitmap);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_timer(enemyTimer);
      return -1;
   }
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(player_bitmap);
      al_destroy_bitmap(enemy_bitmap);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_timer(enemyTimer);
      return -1;
   }

   //Initialize game variables
   initPlayer(&player);
   initEnemy(&enemy);
   score = 0;
   highscore = 0;
 
   //Register events
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_timer_event_source(enemyTimer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   //Create bitmaps
   al_set_target_bitmap(player_bitmap);
   al_clear_to_color(al_map_rgb(255, 255, 255));
   ALLEGRO_BITMAP *temp_player_bitmap = al_load_bitmap(BITMAP_PLAYER_PATH);
   al_draw_scaled_bitmap(temp_player_bitmap, 0, 0, al_get_bitmap_width(temp_player_bitmap), al_get_bitmap_height(temp_player_bitmap), 
                                                               0, 0, player.size, player.size, 0);
   al_destroy_bitmap(temp_player_bitmap);
   al_set_target_bitmap(al_get_backbuffer(display));

   
   al_set_target_bitmap(enemy_bitmap);
   al_clear_to_color(al_map_rgb(255, 255, 255));
   ALLEGRO_BITMAP *temp_enemy_bitmap = al_load_bitmap(BITMAP_ENEMY_PATH);
   al_draw_scaled_bitmap(temp_enemy_bitmap, 0, 0, al_get_bitmap_width(temp_enemy_bitmap), al_get_bitmap_width(temp_enemy_bitmap),
                                                                        0, 0, enemy.size, enemy.size, 0);
   al_destroy_bitmap(temp_enemy_bitmap);

   al_set_target_bitmap(al_get_backbuffer(display));
   al_clear_to_color(al_map_rgb(255,255,255));
   al_flip_display();
 
   //Start timers
   al_start_timer(timer);
   al_start_timer(enemyTimer);
 
   //Main loop
   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      //Timer event
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if (ev.timer.source == enemyTimer){
            speedUp(&enemy);
            speedUp(&player);
         }
         if(ev.timer.source == timer){
            movePlayer(&player, key);
            moveEnemy(&enemy);
            score ++;
            if(score > highscore) highscore = score;
            redraw = true;
         }
      }
      //Display close event
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      //Key down event
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
      //Key up event
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
 
      //All events processed, update the frame
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;

         //If the enemy hits the player
         if(checkCollision(player, enemy)){
            printf("HIT!\n");
            al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            al_stop_timer(timer);
            al_stop_timer(enemyTimer);
            al_rest(4);
            //Reset
            al_start_timer(timer);
            al_start_timer(enemyTimer);
            initPlayer(&player);
            initEnemy(&enemy);
            score = 0;
         }
 
         sprintf(score_str, "%d", score);
         sprintf(highscore_str, "%d", highscore);
         al_clear_to_color(al_map_rgb(255,255,255));
         al_draw_bitmap(player_bitmap, player.x, player.y, 0);
         al_draw_bitmap(enemy_bitmap, enemy.x, enemy.y, 0);
         al_draw_text(font, al_map_rgb(0,0,0), 0, 0, ALLEGRO_ALIGN_LEFT, score_str);
         al_draw_text(font, al_map_rgb(0,0,0), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT, highscore_str);
         al_flip_display();
      }
   }
 
   //Clean up
   al_destroy_sample(sample);
   al_destroy_bitmap(player_bitmap);
   al_destroy_bitmap(enemy_bitmap);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}