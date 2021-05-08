/* See LICENSE file for copyright and license details. */

/* General Behaviour */
static const unsigned int snap      = 1;
static const int resizehints        = 0;    /* 1 means respect size hints in tiled resizals */

/* General Appearance */
static const unsigned int borderpx  = 0;
static const unsigned int gappx     = 12;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* Bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 8;       /* vertical padding of bar */
static const int sidepad            = 8;       /* horizontal padding of bar */
static const int horizpadbar        = 4;        /* horizontal padding for inside of statusbar */
static const int vertpadbar         = 2;        /* vertical padding for inside of statusbar */

/* Colours */
static const char col_black[]         = "#060504";
static const char col_white[]         = "#ecdecb";
static const char col_dimbrown[]      = "#1c1911";
static const char col_dimred[]        = "#712a1b";
static const char col_dimlgreen[]     = "#5b6622";
static const char col_dimyellow[]     = "#8f680d";
static const char col_dimdrkgreen[]   = "#15430d";
static const char col_dimmagenta[]    = "#70352b";
static const char col_dimorange[]     = "#663817";
static const char col_dimgrey[]       = "#a09173";
static const char col_brbrown[]       = "#534429";
static const char col_brred[]         = "#97270e";
static const char col_brlgreen[]      = "#7a9104";
static const char col_bryellow[]      = "#cc9412";
static const char col_brdrkgreen[]    = "#247812";
static const char col_brmagenta[]     = "#994131";
static const char col_brorange[]      = "#ab4f20";
static const char col_brgrey[]        = "#f2d59e";

static const char *colors[][3]      = {
	/*                    fg         bg          border   */
	[SchemeNorm]      = { col_white, col_dimbrown,  "#000000" }, // Only used in borders
	[SchemeSel]       = { col_white, col_brbrown,   "#000000"  }, // Only used in borders
	[SchemeStatus]    = { col_white, col_dimdrkgreen,  "#000000"  }, // Statusbar right
	[SchemeTagsSel]   = { col_white, col_brred,   "#000000"  }, // Tagbar left selected
	[SchemeTagsNorm]  = { col_white, col_dimorange,  "#000000"  }, // Tagbar left unselected
	[SchemeInfoSel]   = { col_white, col_dimbrown,   "#000000"  }, // Infobar middle selected
	[SchemeInfoNorm]  = { col_white, col_dimbrown,  "#000000"  }, // Infobar middle unselected (No Active Window)
};

static const unsigned int baralpha  = 0xa0;
static const unsigned int alphas[][3]      = {
	/*                    fg         bg          border   */
	[SchemeNorm]      = { OPAQUE,    baralpha,   OPAQUE },
	[SchemeSel]       = { OPAQUE,    baralpha,   OPAQUE  },
	[SchemeStatus]    = { OPAQUE,    baralpha,   OPAQUE  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { OPAQUE,    baralpha,   OPAQUE  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { OPAQUE,    baralpha,   OPAQUE  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]   = { OPAQUE,    baralpha,   OPAQUE  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { OPAQUE,    baralpha,   OPAQUE  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* Tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* class         instance    title       tags mask     isfloating   monitor float x,y,w,h          Scratchpad key*/
	{ "Firefox",     NULL,       NULL,       1,            0,           -1,           0,0,0,0,          0 },
        { NULL,          NULL,       "Htop",     0,            1,           -1,           156,56,850,888,  'Y' },
        { NULL,          NULL,       "ncmpcpp",  0,            1,           -1,           692,154,916,524, 'y' },
        { NULL,          NULL,       "Scratchpad", 0,          1,           -1,           585,330,750,420, 'u' },
        { "Microsoft Teams - Preview", NULL, "Microsoft Teams Notification", 0, 1, -1,    0,0,0,0,          0  },
        { NULL,          NULL,       "Picture in picture", 0,  1,           -1,           0,0,0,0,          0  },
};

/* layout(s) */

#include "layouts.c"

static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
/*First arg only serves to match against key in rules*/
static const char *scratchhtop[] = {"Y", "st", "-t", "Htop", "htop", NULL}; 
static const char *scratchncmpcpp[] = {"y", "st", "-t", "ncmpcpp", "ncmpcpp", NULL};
static const char *scratchpad[] = {"u", "st", "-t", "Scratchpad", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_y,      togglescratch,  {.v = scratchhtop } },
        { MODKEY,                       XK_y,      togglescratch,  {.v = scratchncmpcpp } },
        { MODKEY,                       XK_u,      togglescratch,  {.v = scratchpad } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      killclient,     {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_space,  focusmaster,    {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

