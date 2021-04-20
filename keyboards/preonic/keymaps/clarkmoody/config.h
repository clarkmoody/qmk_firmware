#pragma once

// Tap dance
#define TAPPING_TERM 200
// Number of taps required to toggle layer
#define TAPPING_TOGGLE 2

#ifdef AUDIO_ENABLE
    #define KERNKRAFT_SOUND \
      H__NOTE(_C6),         \
      H__NOTE(_DS6),        \
      H__NOTE(_F6),         \
      H__NOTE(_G6),         \
      H__NOTE(_C6),

    #define MARIO_COIN \
      E__NOTE(_B5),  \
      HD_NOTE(_E6),

    #define ZELDA_PUZZ \
      Q__NOTE(_G5),    \
      Q__NOTE(_FS5),   \
      Q__NOTE(_DS5),   \
      Q__NOTE(_A4),    \
      Q__NOTE(_GS4),   \
      Q__NOTE(_E5),    \
      Q__NOTE(_GS5),   \
      HD_NOTE(_C6),

    #define ONE_UP  \
      Q__NOTE(_E6), \
      Q__NOTE(_G6), \
      Q__NOTE(_E7), \
      Q__NOTE(_C7), \
      Q__NOTE(_D7), \
      Q__NOTE(_G7),

    #define SONIC \
      E__NOTE(_E6), \
      E__NOTE(_G6), \
      HD_NOTE(_C7),

    #define DEE_DEET \
      ED_NOTE(_E6), \
      E__NOTE(_E6),

    #define DOWN_SOUND \
      ED_NOTE(_E6), \
      E__NOTE(_A6),

    // See TEMPO_DEFAULT in rules.mk
    #define KERNKRAFT_SONG SONG(KERNKRAFT_SOUND)
    #define PREONIC_SONG SONG(PREONIC_SOUND)

    #define STARTUP_SONG SONG(DEE_DEET)
    // #define STARTUP_SONG PREONIC_SONG
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define GOODBYE_SONG SONG(DOWN_SOUND)

    #define DEFAULT_LAYER_SONGS { \
      SONG(COLEMAK_SOUND), \
      SONG(QWERTY_SOUND) \
    }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2
