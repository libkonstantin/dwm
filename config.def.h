/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "~", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                              "b", "d", "e", "f", "g", "h", "i", "j",
                              "k", "l", "m", "n", "o", "p", "r", "s", "t", "u",
                              "v", "w", "y"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS1(KEY,TAG)                                                                   \
	{1, {{MODKEY,                       KEY}},          view,           {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask,           KEY}},          toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask,             KEY}},          tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},          toggletag,      {.ui = 1 << TAG} },

#define TAGKEYS2(KEY1, KEY2,TAG)                                                            \
	{2, {{MODKEY,                       KEY1},                                              \
	     {MODKEY,                       KEY2}},         view,           {.ui = 1 << TAG} }, \
	{2, {{MODKEY|ControlMask,           KEY1},                                              \
	     {MODKEY|ControlMask,           KEY2}},         toggleview,     {.ui = 1 << TAG} }, \
	{2, {{MODKEY|ShiftMask,             KEY1},                                              \
	     {MODKEY|ShiftMask,             KEY2}},         tag,            {.ui = 1 << TAG} }, \
	{2, {{MODKEY|ControlMask|ShiftMask, KEY1},                                              \
	     {MODKEY|ControlMask|ShiftMask, KEY2}},         toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *roficmd[] = { "rofi", "-modi", "window,ssh,run,drun", "-show", "run", "-sidebar-mode", "-terminal", "st", "-theme", "dracula", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *rulayoutcmd[] = { "xkb-switch", "-s", "ru", NULL };
static const char *uslayoutcmd[] = { "xkb-switch", "-s", "us", NULL };

static Keychord keychords[] = {
	/*   modifier                       key             function        argument */
	{1, {{MODKEY,                       XK_d        }}, spawn,          {.v = roficmd } },
	{1, {{MODKEY,                       XK_Return   }}, spawn,          {.v = termcmd } },
	{1, {{MODKEY,                       XK_b        }}, togglebar,      {0} },
	{1, {{MODKEY,                       XK_j,       }}, focusstack,     {.i = +1 } },
	{1, {{MODKEY,                       XK_k,       }}, focusstack,     {.i = -1 } },
	{1, {{MODKEY|ShiftMask,             XK_j,       }}, rotatestack,    {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_k,       }}, rotatestack,    {.i = -1 } },
	{1, {{MODKEY,                       XK_h,       }}, focusmon,       {.i = -1 } },
	{1, {{MODKEY,                       XK_l,       }}, focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_h,       }}, tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask,             XK_l,       }}, tagmon,         {.i = +1 } },
	{1, {{MODKEY|ControlMask,           XK_j,       }}, incnmaster,     {.i = +1 } },
	{1, {{MODKEY|ControlMask,           XK_k,       }}, incnmaster,     {.i = -1 } },
	{1, {{MODKEY|ControlMask,           XK_h,       }}, setmfact,       {.f = -0.05} },
	{1, {{MODKEY|ControlMask,           XK_l,       }}, setmfact,       {.f = +0.05} },
	{1, {{MODKEY|ShiftMask,             XK_Return,  }}, zoom,           {0} },
	{1, {{MODKEY,                       XK_Tab,     }}, view,           {0} },
	{1, {{MODKEY|ShiftMask,             XK_q,       }}, killclient,     {0} },
	{1, {{MODKEY,                       XK_t,       }}, setlayout,      {.v = &layouts[0]} },
	{1, {{MODKEY,                       XK_f,       }}, setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY,                       XK_m,       }}, setlayout,      {.v = &layouts[2]} },
	{1, {{MODKEY,                       XK_space,   }}, setlayout,      {0} },
	{1, {{MODKEY|ShiftMask,             XK_space,   }}, togglefloating, {0} },
	{1, {{MODKEY,                       XK_0,       }}, view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask,             XK_0,       }}, tag,            {.ui = ~0 } },
	{1, {{MODKEY,                       XK_minus,   }}, setgaps,        {.i = -1 } },
	{1, {{MODKEY,                       XK_equal,   }}, setgaps,        {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_equal,   }}, setgaps,        {.i = 0  } },
	{1, {{MODKEY,                       XK_r,       }}, spawn,          {.v = rulayoutcmd } },
	{1, {{MODKEY,                       XK_u,       }}, spawn,          {.v = uslayoutcmd } },
	{1, {{MODKEY,                       XK_F5,      }}, xrdb,           {.v = NULL } },
	TAGKEYS1(                           XK_grave,                       0)
	TAGKEYS1(                           XK_1,                           1)
	TAGKEYS1(                           XK_2,                           2)
	TAGKEYS1(                           XK_3,                           3)
	TAGKEYS1(                           XK_4,                           4)
	TAGKEYS1(                           XK_5,                           5)
	TAGKEYS1(                           XK_6,                           6)
	TAGKEYS1(                           XK_7,                           7)
	TAGKEYS1(                           XK_8,                           8)
	TAGKEYS1(                           XK_9,                           9)
	TAGKEYS2(                           XK_w, XK_b,                     10)
	TAGKEYS2(                           XK_w, XK_d,                     11)
	TAGKEYS2(                           XK_w, XK_e,                     12)
	TAGKEYS2(                           XK_w, XK_f,                     13)
	TAGKEYS2(                           XK_w, XK_g,                     14)
	TAGKEYS2(                           XK_o, XK_h,                     15)
	TAGKEYS2(                           XK_o, XK_i,                     16)
	TAGKEYS2(                           XK_o, XK_j,                     17)
	TAGKEYS2(                           XK_o, XK_k,                     18)
	TAGKEYS2(                           XK_o, XK_l,                     19)
	TAGKEYS2(                           XK_o, XK_m,                     20)
	TAGKEYS2(                           XK_o, XK_n,                     21)
	TAGKEYS2(                           XK_o, XK_o,                     22)
	TAGKEYS2(                           XK_o, XK_p,                     23)
	TAGKEYS2(                           XK_w, XK_r,                     24)
	TAGKEYS2(                           XK_w, XK_s,                     25)
	TAGKEYS2(                           XK_w, XK_t,                     26)
	TAGKEYS2(                           XK_o, XK_u,                     27)
	TAGKEYS2(                           XK_w, XK_v,                     28)
	TAGKEYS2(                           XK_w, XK_w,                     29)
	TAGKEYS2(                           XK_o, XK_y,                     31)
	{1, {{MODKEY|ShiftMask,             XK_e,       }}, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

