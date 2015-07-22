#include <cog/src/cog.h>

static cog_state_fsm* fsm;

//State and event defs
#define S_MENU 0
#define S_LEVEL 1
#define S_WAIT 2
#define S_WIN 3

//Custom events
#define E_DEATH 0
#define E_WIN 1
#define E_RESTART 2

int32_t menu_state(cog_state_info state) {
    if(state.initial) {
        cog_debugf("hello");
        cog_debugf("initial menu state...");
        cog_clear();
        cog_sprite_id id = cog_sprite_add("assets/images/title.png");
        cog_sprite_set(id, (cog_sprite) {
            .dim=(cog_dim2) {
                .w=1.0, .h=1.0
            }
        });
    } 
    if(cog_input_key_pressed()) {
        cog_debugf("HI");
    }
    return S_MENU;
}

int32_t play_state(cog_state_info state) {
    cog_debugf("PLAY STATE");
    if(state.initial) {
        cog_clear();
        cog_sprite_id qid = cog_sprite_add("assets/images/quaver.png");
        cog_sprite_set(qid, (cog_sprite) {
            .dim=(cog_dim2) {
                .w=0.02, .h=0.1
            },
            .pos=(cog_pos2) {
                .x=-0.3, .y=0.5
            }
        });

        cog_sprite_id cid = cog_sprite_add("assets/images/crotchet.png");
        cog_sprite_set(cid, (cog_sprite) {
            .dim=(cog_dim2) {
                .w=0.02, .h=0.1
            },
            .pos=(cog_pos2) {
                .x=0.3, .y=0.5
            }
        });

        cog_sprite_id sid = cog_sprite_add("assets/images/semibreve.png");
        cog_sprite_set(sid, (cog_sprite) {
            .dim=(cog_dim2) {
                .w=0.09, .h=0.1
            },
            .pos=(cog_pos2) {
                .x=0.0, .y=0.0
            }
        });
    } else {
    }
    return S_LEVEL;
}

cog_state_transition transitions[] = {
    {S_MENU, COG_E_DUMMY, &menu_state},
    {S_MENU, COG_E_KEYDOWN, &play_state}
};

void main_loop(void) {
    cog_state_fsm_update(fsm);
}

int main(void) {
    cog_init(.window_w = 800,
             .window_h = 800,
             .fullscreen = false);
    fsm = cog_state_fsm_alloc();
    cog_state_fsm_add_transitions(fsm, transitions,
                                  (sizeof(transitions) /
                                   sizeof(*transitions)));
    cog_state_fsm_set_state(fsm, S_MENU);
    cog_start_main_loop(main_loop);
    return 0;
}
