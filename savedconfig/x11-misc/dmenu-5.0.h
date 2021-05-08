/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=10"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#ffffff", "#120b07" },
	[SchemeSel] = { "#ffffff", "#97270e" },
	[SchemeSelHighlight] = { "#ffc978", "#97270e" },
	[SchemeNormHighlight] = { "#ffc978", "#120b07" },
	[SchemeMid] = { "#ffffff", "#ab4f20" },
	[SchemeMidHighlight] = { "#ffc978", "#ab4f20" },
	[SchemeOut] = { "#000000", "#00ffff" },  /* Defunct because of enter key locking down */
};
/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines      = 20;
static unsigned int columns    = 1;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = "& ";
