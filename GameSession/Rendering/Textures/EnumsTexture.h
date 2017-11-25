#pragma once

namespace hvgs
{

enum class TextureName : hvuint8
{
	Actor = 0,
	Background,
	TileAtlas,

	Button_Default,
	Button_Hover,
	Button_Pressed,
	Button_Deactivated,

	Count
};

}