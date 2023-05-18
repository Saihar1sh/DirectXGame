struct Button_State 
{
	bool is_down, changed;
};
enum
{
	Button_Up,
	Button_Down,
	Button_Left,
	Button_Right,

	Button_Count	// must be the last for count
};

struct Input
{
	Button_State buttons[Button_Count];
};