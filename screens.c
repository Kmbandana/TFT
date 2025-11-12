#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include "lvgl.h"
#include "main.h"

lv_obj_t *menu_items[MENU_ITEMS];
//int selected_index = 0;
int current_line = 0;

void update_menu_highlight(void) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        lv_obj_set_style_text_color(menu_items[i], lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT); // Black text
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);//Blue

        if (i == selected_index) {
            lv_obj_set_style_bg_color(menu_items[i], lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);   // Blue
            lv_obj_set_style_text_color(menu_items[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT); // White text
        } else {
            lv_obj_set_style_bg_color(menu_items[i], lv_color_hex(0xFF0000), 0);   // Red
        }
    }
}

void create_menu_screen(void) {
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_scr_load(scr);

    const char *labels[MENU_ITEMS] = {
        "1. Line One",
        "2. Line Two",
        "3. Line Three",
        "4. Line Four"
    };

    for (int i = 0; i < MENU_ITEMS; i++) {
        menu_items[i] = lv_label_create(scr);
        lv_label_set_text(menu_items[i], labels[i]);
        lv_obj_set_width(menu_items[i], 300);
        lv_obj_set_style_pad_all(menu_items[i], 8, 0);
        lv_obj_set_pos(menu_items[i], 10, 20 + i * 40);

        lv_obj_set_style_bg_color(menu_items[i], lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT); // Red
        lv_obj_set_style_text_color(menu_items[i], lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT); // Black

    }

    update_menu_highlight();
}
void EXTI0_IRQHandler(void) {  // UP button (e.g., GPIO_PIN_0)
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);  // Clear the interrupt flag
        if (selected_index > 0) {
            selected_index--;
            update_menu_highlight();  // Update the highlight after button press
        }
    }
}

void EXTI1_IRQHandler(void) {  // DOWN button (e.g., GPIO_PIN_1)
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);  // Clear the interrupt flag
        if (selected_index < MENU_ITEMS - 1) {
            selected_index++;
            update_menu_highlight();  // Update the highlight after button press
        }
    }
}
void EXTI15_10_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) { // RIGHT (Enter)
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
        // Do action for selected item
    }

    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) { // LEFT (Back)
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
        // Do back/cancel
    }
}
