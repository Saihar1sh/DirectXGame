#define is_Down(b)	input->buttons[b].is_down
#define pressed(b)	(input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)


float player_yPosition = 0.f;
float player_xPosition = 0.f;

internal void simulate_game(Input* input)
{
	clear_screen(Colors::Aquamarine);

	//if(pressed(Button_Up))
	//	player_yPosition += 1.f;
	//if(pressed(Button_Down))
	//	player_yPosition -= 1.f;
	//if(pressed(Button_Right))
	//	player_xPosition += 1.f;
	//if(pressed(Button_Left))
	//	player_xPosition -= 1.f;

	//draw_rect(player_xPosition, player_yPosition, 5, 5, Colors::Black);


	draw_rect(0, 0, 5, 5, Colors::Silver);
	draw_rect(30, 20, 5, 8, Colors::White);


}