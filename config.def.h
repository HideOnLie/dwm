/* See LICENSE file for copyright and license details. */

/* appearance, 外观 */
static const unsigned int borderpx  = 1;        /* border pixel of windows, 窗口边缘的像素 */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing, 系统托盘栏间距 */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray , 0表示取消系统托盘栏*/
static const unsigned int gappih    = 10;       /* horiz inner gap between windows , 窗口之间的水平间隔 */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows , 窗口之间的垂直间隔 */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge , 窗口与屏幕的外部水平间隔*/
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge, 窗口与屏幕的外部垂直间隔 */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window ,1表示只有一个窗口时没有外部间隔*/
static const int showbar            = 1;        /* 0 means no bar ,0表示不显示托盘条*/
static const int topbar             = 1;        /* 0 means bottom bar, 0表示托盘条显示在底部 */
static const char *fonts[]          = { "Noto Sans CJK SC:size=10" };
static const char dmenufont[]       = "Noto Sans CJK SC:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;      /* bar的透明度 */
static const unsigned int borderalpha = OPAQUE; /* 边缘的透明度 */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging, 标签 */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "chromium",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s), 布局 */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions, 按键定义 */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands, 命令定义 */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *slockcmd[] = { "slock", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* 快捷键绑定 Mod4Mask为win键*/
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd} },                //启动器
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },               //终端
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },         //画板
	{ MODKEY,                       XK_b,      togglebar,      {0} },                           //打开/关闭bar
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },                    //在窗口栈切换焦点，下一个
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },                    //在窗口栈切换焦点，上一个
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },                    //多窗口水平排布
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },                    //多窗口垂直排布
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },                  //主窗口占的空间变小
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },                  //主窗口占的空间变大
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },                    //增大窗口之间的间距
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },                    //缩小窗口之间的间距
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },                    //不改变窗口之间的间距，增大与屏幕的间距
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },                    //不改变窗口之间的间距，缩小与屏幕的间距
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },                    //不改变与屏幕的间距，增大窗口之间的所有间距
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },                    //不改变与屏幕的间距，缩小窗口之间的所有间距
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },                           //打开/关闭窗口间距功能
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },                           //恢复默认间隔距离
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },                    //不改变与屏幕的间距，增大窗口之间的垂直间距
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },                    //不改变与屏幕的间距，减小窗口之间的垂直间距
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },                    //不改变与屏幕的间距，增大窗口之间的水平间距
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },                    //不改变与屏幕的间距，减小窗口之间的水平间距
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },                           //将窗口焦点切换到鼠标所在位置的窗口上
	{ MODKEY,                       XK_Tab,    view,           {0} },                           //切换到最近一次的标签中
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },                           //杀死窗口
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },            //平铺布局
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },            //浮动布局
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },            //窗口布局
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },                           //全屏
	{ MODKEY,                       XK_space,  setlayout,      {0} },                           //切换到最近一次布局
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                           //开启/关闭浮动窗口
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },                   //预览所有标签,在一个窗口显示
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },                   //显示所有的标签
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    /* 标签切换 */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },                           //退出dwm
    /* 自定义 */
	{ Mod4Mask,                     XK_l,      spawn,          {.v = slockcmd} },                //锁屏
};

/* button definitions , 鼠标事件定义*/
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
/* Button1 : 鼠标左键   Button3 : 鼠标右键 */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },              //左键窗口栏，隐藏/打开窗口
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },              //中建窗口栏，切换窗口焦点
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },              //左键tag,查看对应tag
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },              //右键tag,预览对应tag
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

