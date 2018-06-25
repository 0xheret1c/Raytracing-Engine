#pragma once
enum e_Colors
{

	/*************************************
	Colorname 					Hex Code
								#RRGGBB
	*************************************/


	maroon = 0x800000,
	dark_red = 0x8B0000,
	brown = 0xA52A2A,
	firebrick = 0xB22222,
	crimson = 0xDC143C,
	red = 0xFF0000,
	tomato = 0xFF6347,
	coral = 0xFF7F50,
	indian_red = 0xCD5C5C,
	light_coral = 0xF08080,
	dark_salmon = 0xE9967A,
	salmon = 0xFA8072,
	light_salmon = 0xFFA07A,
	orange_red = 0xFF4500,
	dark_orange = 0xFF8C00,
	orange = 0xFFA500,
	gold = 0xFFD700,
	dark_golde_rod = 0xB8860B,
	golden_rod = 0xDAA520,
	pale_golden_rod = 0xEEE8AA,
	dark_khaki = 0xBDB76B,
	khaki = 0xF0E68C,
	olive = 0x808000,
	yellow = 0xFFFF00,
	yellow_green = 0x9ACD32,
	dark_olive_green = 0x556B2F,
	olive_drab = 0x6B8E23,
	lawn_green = 0x7CFC00,
	chart_reuse = 0x7FFF00,
	green_yellow = 0xADFF2F,
	dark_green = 0x006400,
	green = 0x008000,
	forest_green = 0x228B22,
	lime = 0x00FF00,
	lime_green = 0x32CD32,
	light_green = 0x90EE90,
	pale_green = 0x98FB98,
	dark_sea_green = 0x8FBC8F,
	medium_spring_green = 0x00FA9A,
	spring_green = 0x00FF7F,
	sea_green = 0x2E8B57,
	medium_aqua_marine = 0x66CDAA,
	medium_sea_green = 0x3CB371,
	light_sea_green = 0x20B2AA,
	dark_slate_gray = 0x2F4F4F,
	teal = 0x008080,
	dark_cyan = 0x008B8B,
	aqua = 0x00FFFF,
	cyan = 0x00FFFF,
	light_cyan = 0xE0FFFF,
	dark_turquoise = 0x00CED1,
	turquoise = 0x40E0D0,
	medium_turquoise = 0x48D1CC,
	pale_turquoise = 0xAFEEEE,
	aqua_marine = 0x7FFFD4,
	powder_blue = 0xB0E0E6,
	cadet_blue = 0x5F9EA0,
	steel_blue = 0x4682B4,
	corn_flower_blue = 0x6495ED,
	deep_sky_blue = 0x00BFFF,
	dodger_blue = 0x1E90FF,
	light_blue = 0xADD8E6,
	sky_blue = 0x87CEEB,
	light_sky_blue = 0x87CEFA,
	midnight_blue = 0x191970,
	navy = 0x000080,
	dark_blue = 0x00008B,
	medium_blue = 0x0000CD,
	blue = 0x0000FF,
	royal_blue = 0x4169E1,
	blue_violet = 0x8A2BE2,
	indigo = 0x4B0082,
	dark_slate_blue = 0x483D8B,
	slate_blue = 0x6A5ACD,
	medium_slate_blue = 0x7B68EE,
	medium_purple = 0x9370DB,
	dark_magenta = 0x8B008B,
	dark_violet = 0x9400D3,
	dark_orchid = 0x9932CC,
	medium_orchid = 0xBA55D3,
	purple = 0x800080,
	thistle = 0xD8BFD8,
	plum = 0xDDA0DD,
	violet = 0xEE82EE,
	magenta = 0xFF00FF,
	fuchsia = 0xFF00FF,
	orchid = 0xDA70D6,
	medium_violet_red = 0xC71585,
	pale_violet_red = 0xDB7093,
	deep_pink = 0xFF1493,
	hot_pink = 0xFF69B4,
	light_pink = 0xFFB6C1,
	pink = 0xFFC0CB,
	antique_white = 0xFAEBD7,
	beige = 0xF5F5DC,
	bisque = 0xFFE4C4,
	blanched_almond = 0xFFEBCD,
	wheat = 0xF5DEB3,
	corn_silk = 0xFFF8DC,
	lemon_chiffon = 0xFFFACD,
	light_golden_rod_yellow = 0xFAFAD2,
	light_yellow = 0xFFFFE0,
	saddle_brown = 0x8B4513,
	sienna = 0xA0522D,
	chocolate = 0xD2691E,
	peru = 0xCD853F,
	sandy_brown = 0xF4A460,
	burly_wood = 0xDEB887,
	tan_ = 0xD2B48C,
	rosy_brown = 0xBC8F8F,
	moccasin = 0xFFE4B5,
	navajo_white = 0xFFDEAD,
	peach_puff = 0xFFDAB9,
	misty_rose = 0xFFE4E1,
	lavender_blush = 0xFFF0F5,
	linen = 0xFAF0E6,
	old_lace = 0xFDF5E6,
	papaya_whip = 0xFFEFD5,
	sea_shell = 0xFFF5EE,
	mint_cream = 0xF5FFFA,
	slate_gray = 0x708090,
	light_slate_gray = 0x778899,
	light_slate_grey = 0x778899,
	light_steel_blue = 0xB0C4DE,
	lavender = 0xE6E6FA,
	floral_white = 0xFFFAF0,
	alice_blue = 0xF0F8FF,
	ghost_white = 0xF8F8FF,
	honeydew = 0xF0FFF0,
	ivory = 0xFFFFF0,
	azure = 0xF0FFFF,
	snow = 0xFFFAFA,
	black = 0x000000,
	dim_gray = 0x696969,
	dim_grey = 0x696969,
	gray = 0x808080,
	grey = 0x808080,
	dark_gray = 0xA9A9A9,
	dark_grey = 0xA9A9A9,
	silver = 0xC0C0C0,
	light_gray = 0xD3D3D3,
	light_grey = 0xD3D3D3,
	gainsboro = 0xDCDCDC,
	white_smoke = 0xF5F5F5,
	white = 0xFFFFFF

};