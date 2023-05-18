#define is_down(b)	input->button[b].is_down
#define pressed(b)	(input->button[b].is_down && input->button[b].changed)
#define released(b) (!input->button[b].is_down && input->button[b].changed)


float player_yPosition = 0.f;

static void
simulate_game(Input* input)
{
	clear_screen(Colors::LightGreen);

	if(pressed[Button_Up])
		//player_yPosition += 1.f;

	draw_rect(0, player_yPosition, 200, 200, Colors::Black);


	draw_rect(20, 20, 5, 5, Colors::Purple);
	draw_rect(30, 20, 5, 8, Colors::White);


}