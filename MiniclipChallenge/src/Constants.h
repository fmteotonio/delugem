#pragma once

//SCREEN SETTINGS
#define SCREEN_WIDTH		384
#define SCREEN_HEIGHT		216
#define GAME_SCALE			4
#define TARGET_FPS			60

//GAME SETTINGS

#define BOARD_HEIGHT		10
#define BOARD_STARTCOLUMNS	13
#define BOARD_START_X		SCREEN_WIDTH
#define BOARD_START_Y		28  + GEM_H*(10-BOARD_HEIGHT)
#define ENDLINE_X			2 * GEM_W
#define ENDLINE_Y			28

#define GEM_ACCELERATION	450
#define GEM_TYPE_NUMBER		5

#define BOARD_COLUMNTIME	10000
#define BOARD_CTIMEMULTIP	0.95

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

//COLOR PALETTE

#define WHITE				{255,255,255}
#define BLACK				{0,0,0}

//------------------UI ELEMENTS PLACEMENT------------------------

//OBJECT PLACEMENTS

//Score Text

#define SCOREBASE_X			150
#define SCOREBASE_Y			14

#define SCORETEXT_X			SCOREBASE_X
#define SCORETEXT_Y			SCOREBASE_Y
#define SCOREVALUE_X		SCOREBASE_X + 99
#define SCOREVALUE_Y		SCOREBASE_Y

//Level Text

#define LEVELBASE_X			7
#define LEVELBASE_Y			14

#define LEVELTEXT_X			LEVELBASE_X
#define LEVELTEXT_Y			LEVELBASE_Y
#define LEVELVALUE_X		LEVELBASE_X + 71
#define LEVELVALUE_Y		LEVELBASE_Y

//Pause Button

#define PAUSEBASE_X			351
#define PAUSEBASE_Y			2

#define PAUSEBUTTON_X		PAUSEBASE_X
#define PAUSEBUTTON_Y		PAUSEBASE_Y
#define PAUSEICON_X			PAUSEBUTTON_X + 8
#define PAUSEICON_Y			PAUSEBUTTON_Y + 8 

//Fill Button and text objects

#define FILLBASE_X			7
#define FILLBASE_Y			202

#define FILLTEXT1_X			FILLBASE_X
#define FILLTEXT1_Y			FILLBASE_Y
#define FILLVALUE_X			FILLBASE_X + 38
#define FILLVALUE_Y			FILLBASE_Y
#define FILLTEXT2_X			FILLBASE_X + 50
#define FILLTEXT2_Y			FILLBASE_Y

#define FILLBUTTON_X		FILLBASE_X + 91
#define FILLBUTTON_Y		FILLBASE_Y - 12
#define FILLICON_X			FILLBUTTON_X + 8
#define FILLICON_Y			FILLBUTTON_Y + 8

//Push Button and text object

#define PUSHBASE_X			313
#define PUSHBASE_Y			202

#define PUSHTEXT_X			PUSHBASE_X
#define PUSHTEXT_Y			PUSHBASE_Y
#define PUSHBUTTON_X		PUSHBASE_X + 38 
#define PUSHBUTTON_Y		PUSHBASE_Y - 12
#define PUSHICON_X			PUSHBUTTON_X + 8
#define PUSHICON_Y			PUSHBUTTON_Y + 8