/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const char *fonts[]          = { "Liberation Mono:pixelsize=16:antialias=true:autohint=true" };

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#c5c8c6", "#1d1f21", "#1d1f21" },
	[SchemeSel]  = { "#1d1f21", "#81a2be", "#81a2be"  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { 0xffU, 0xd0, 0xffU },
	[SchemeSel]  = { 0xffU, 0xd0, 0xffU },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Steam",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[t]",      tile },    /* first entry is default */
	{ "[f]",      NULL },    /* no layout function means floating behavior */
	{ "[m]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("st") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },

	{ MODKEY|ControlMask,           XK_Return, spawn,          SHCMD("st -e tmux new-session -A -s default") },

	{ MODKEY|ControlMask,           XK_f,      spawn,          SHCMD("st -e rover") },
	{ MODKEY|ControlMask,           XK_h,      spawn,          SHCMD("st -e htop") },
	{ MODKEY|ControlMask,           XK_q,      spawn,          SHCMD("st -e qalc") },
	{ MODKEY|ControlMask,           XK_c,      spawn,          SHCMD("st -e tty-clock -csC4") },

	{ MODKEY|ControlMask|ShiftMask, XK_b,      spawn,          SHCMD("torbrowser-launcher") },
	{ MODKEY|ControlMask,           XK_t,      spawn,          SHCMD("telegram-desktop") },
	{ MODKEY|ControlMask,           XK_b,      spawn,          SHCMD("chromium") },
	{ MODKEY|ControlMask,           XK_o,      spawn,          SHCMD("wps") }, // my office

	// quality of life bash scripts
	{ MODKEY,                       XK_s,      spawn,          SHCMD("dmenu_session") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("dmenu_emoji") },
	{ MODKEY,                       XK_u,      spawn,          SHCMD("dmenu_unicode") },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("dmenu_kaomoji") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("dmenu_bookmarks") },

	{ 0,                            XK_Print,  spawn,          SHCMD("dir=~/.screenshots; name=$dir/screenshot$(date +\"%d-%m-%H-%M-%S\").png; mkdir -p $dir; maim -s $name; xclip -selection clipboard -t image/png -i $name") },

	{ 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("amixer set Master 5%+") },
	{ 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("amixer set Master 5%-") },
	{ 0,          XF86XK_AudioMute,            spawn,          SHCMD("amixer -q set Master toggle") },

	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("brightnessctl set +11%") },
	{ 0,          XF86XK_MonBrightnessDown,    spawn,          SHCMD("brightnessctl set 11%-") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

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
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERMINAL") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

