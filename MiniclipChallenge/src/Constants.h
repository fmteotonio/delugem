#pragma once

//SCREEN SETTINGS
#define SCREEN_WIDTH		384
#define SCREEN_HEIGHT		216
#define GAME_SCALE			4
#define TARGET_FPS			60

//RESOURCEPATHS
#define FNT_M6X11			"res/fonts/m6x11.ttf" //Mults. of 16
#define FNT_M3X6			"res/fonts/m3x6.ttf"  //Mults. of 16
#define SPR_GEMS			"res/images/gems.png"
#define SPR_BACKGROUND		"res/images/background.png"
#define SPR_ENDLINE			"res/images/endline.png"
#define SPR_FOREGROUNDSTRIP "res/images/foregroundstrip.png"
#define SPR_BIGBUTTON		"res/images/bigbutton.png"
#define SPR_SMALLBUTTON		"res/images/smallbutton.png"
#define SPR_ICONFILL		"res/images/iconfill.png"
#define SPR_ICONPAUSE		"res/images/iconpause.png"
#define SPR_ICONPUSH		"res/images/iconpush.png"

//OBJECT SIZES
#define GEM_W				16
#define GEM_H				16
#define BACKGROUND_W		SCREEN_WIDTH
#define BACKGROUND_H		SCREEN_HEIGHT
#define ENDLINE_W			1
#define ENDLINE_H		    160
#define FOREGROUNDSTRIP_W	SCREEN_WIDTH
#define FOREGROUNDSTRIP_H	28
#define BIGBUTTON_W			98
#define BIGBUTTON_H			34
#define SMALLBUTTON_W		24
#define SMALLBUTTON_H		24
#define ICON_W				9
#define ICON_H				9

//OBJECT PLACEMENTS
#define SCORETEXT_X			140
#define SCORETEXT_Y			14
#define SCOREVALUETEXT_X	239
#define SCOREVALUETEXT_Y	14
#define LEVELTEXT_X			7
#define LEVELTEXT_Y			14
#define LEVELVALUETEXT_X	76
#define LEVELVALUETEXT_Y	14

//GAME SETTINGS
#define BOARD_HEIGHT		10
#define BOARD_STARTCOLUMNS	13
#define BOARD_START_X		176 + GEM_W*(13-BOARD_STARTCOLUMNS)
#define BOARD_START_Y		28  + GEM_H*(10-BOARD_HEIGHT)

#define GEM_ACCELERATION	350
#define GEM_TYPE_NUMBER		5

#define BOARD_COLUMNTIME	10000
#define BOARD_CTIMEMULTIP	0.95

//COLOR PALETTE
#define WHITE				{255,255,255}
#define BLACK				{0,0,0}