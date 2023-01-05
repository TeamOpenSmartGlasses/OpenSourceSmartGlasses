// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project


#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

uint32_t LV_EVENT_GET_COMP_CHILD;

typedef struct {
    uint32_t child_idx;
    lv_obj_t * child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t * comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_event_send(comp, LV_EVENT_GET_COMP_CHILD, &info);
    return info.child;
}

void get_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    ui_comp_get_child_t * info = lv_event_get_param(e);
    info->child = c[info->child_idx];
}

void del_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    lv_mem_free(c);
}

lv_obj_t * cui_Header_Text;

// COMPONENT Card Base

lv_obj_t * ui_Card_Base_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Card_Base;
    cui_Card_Base = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Card_Base, lv_pct(100));
    lv_obj_set_height(cui_Card_Base, lv_pct(100));
    lv_obj_set_align(cui_Card_Base, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_Card_Base, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Card_Base, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_Base, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Card_Hero;
    cui_Card_Hero = lv_img_create(cui_Card_Base);
    lv_obj_set_width(cui_Card_Hero, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Card_Hero, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Card_Hero, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_Card_Hero, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_Card_Hero, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_opa(cui_Card_Hero, 40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Card_Container;
    cui_Card_Container = lv_obj_create(cui_Card_Base);
    lv_obj_set_width(cui_Card_Container, lv_pct(100));
    lv_obj_set_height(cui_Card_Container, lv_pct(86));
    lv_obj_set_x(cui_Card_Container, 0);
    lv_obj_set_y(cui_Card_Container, lv_pct(7));
    lv_obj_set_align(cui_Card_Container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_Card_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Card_Container, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Card_Content_Text;
    cui_Card_Content_Text = lv_label_create(cui_Card_Container);
    lv_obj_set_width(cui_Card_Content_Text, lv_pct(100));
    lv_obj_set_height(cui_Card_Content_Text, lv_pct(50));
    lv_obj_set_align(cui_Card_Content_Text, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(cui_Card_Content_Text, LV_LABEL_LONG_DOT);
    lv_label_set_text(cui_Card_Content_Text, "");
    lv_obj_set_style_text_font(cui_Card_Content_Text, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Card_Content_Text, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_Content_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_Content_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_Content_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT); 
    lv_obj_t * cui_Card_More_Text;
    cui_Card_More_Text = lv_label_create(cui_Card_Container);
    lv_obj_set_width(cui_Card_More_Text, lv_pct(100));
    lv_obj_set_height(cui_Card_More_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Card_More_Text, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(cui_Card_More_Text, "Tap for more");
    lv_obj_set_style_text_align(cui_Card_More_Text, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_Card_More_Text, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CARD_BASE_NUM);
    children[UI_COMP_CARD_BASE_CARD_BASE] = cui_Card_Base;
    children[UI_COMP_CARD_BASE_CARD_HERO] = cui_Card_Hero;
    children[UI_COMP_CARD_BASE_CARD_CONTAINER] = cui_Card_Container;
    children[UI_COMP_CARD_BASE_CARD_CONTENT_TEXT] = cui_Card_Content_Text;
    children[UI_COMP_CARD_BASE_CARD_MORE_TEXT] = cui_Card_More_Text;
    lv_obj_add_event_cb(cui_Card_Base, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Card_Base, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_Card_Base;
}



// COMPONENT Card Title With Icon

lv_obj_t * ui_Card_Title_With_Icon_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Card_Title_With_Icon;
    cui_Card_Title_With_Icon = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Card_Title_With_Icon, lv_pct(100));
    lv_obj_set_height(cui_Card_Title_With_Icon, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_align(cui_Card_Title_With_Icon, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(cui_Card_Title_With_Icon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Card_Title_With_Icon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Card_Title_With_Icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Card_Title_With_Icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Card_Title_With_Icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_Title_With_Icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_Title_With_Icon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_Title_With_Icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    #if LV_FONT_MONTSERRAT_24
        lv_obj_set_style_text_font(cui_Card_Title_With_Icon, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif

    lv_obj_t * cui_Card_Title_Icon;
    cui_Card_Title_Icon = lv_img_create(cui_Card_Title_With_Icon);
    lv_obj_set_width(cui_Card_Title_Icon, 32);
    lv_obj_set_height(cui_Card_Title_Icon, 32);
    lv_obj_set_align(cui_Card_Title_Icon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(cui_Card_Title_Icon, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_Card_Title_Icon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * cui_Card_Title_Text;
    cui_Card_Title_Text = lv_label_create(cui_Card_Title_With_Icon);
    lv_obj_set_width(cui_Card_Title_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Card_Title_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Card_Title_Text, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(cui_Card_Title_Text, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(cui_Card_Title_Text, "");
    lv_obj_clear_flag(cui_Card_Title_Text,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_pad_left(cui_Card_Title_Text, 42, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_Title_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_Title_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_Title_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CARD_TITLE_WITH_ICON_NUM);
    children[UI_COMP_CARD_TITLE_WITH_ICON_CARD_TITLE_WITH_ICON] = cui_Card_Title_With_Icon;
    children[UI_COMP_CARD_TITLE_WITH_ICON_CARD_TITLE_ICON] = cui_Card_Title_Icon;
    children[UI_COMP_CARD_TITLE_WITH_ICON_CARD_TITLE_TEXT] = cui_Card_Title_Text;
    lv_obj_add_event_cb(cui_Card_Title_With_Icon, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Card_Title_With_Icon, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_Card_Title_With_Icon;
}



// COMPONENT Card title no icon

lv_obj_t * ui_Card_title_no_icon_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Card_title_no_icon;
    cui_Card_title_no_icon = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Card_title_no_icon, lv_pct(100));
    lv_obj_set_height(cui_Card_title_no_icon, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_align(cui_Card_title_no_icon, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(cui_Card_title_no_icon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Card_title_no_icon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Card_title_no_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Card_title_no_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Card_title_no_icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Card_title_no_icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Card_title_no_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Card_title_no_icon, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    #if LV_FONT_MONTSERRAT_24 
        lv_obj_set_style_text_font(cui_Card_title_no_icon, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif
    lv_obj_t * cui_Card_Title_Text;
    cui_Card_Title_Text = lv_label_create(cui_Card_title_no_icon);
    lv_obj_set_width(cui_Card_Title_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Card_Title_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Card_Title_Text, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(cui_Card_Title_Text, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(cui_Card_Title_Text, "");

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CARD_TITLE_NO_ICON_NUM);
    children[UI_COMP_CARD_TITLE_NO_ICON_CARD_TITLE_NO_ICON] = cui_Card_title_no_icon;
    children[UI_COMP_CARD_TITLE_NO_ICON_CARD_TITLE_TEXT] = cui_Card_Title_Text;
    lv_obj_add_event_cb(cui_Card_title_no_icon, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Card_title_no_icon, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_Card_title_no_icon;
}



// COMPONENT ContainerBelowHeader

lv_obj_t * ui_ContainerBelowHeader_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_ContainerBelowHeader;
    cui_ContainerBelowHeader = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_ContainerBelowHeader, lv_pct(100));
    lv_obj_set_height(cui_ContainerBelowHeader, lv_pct(86));
    lv_obj_set_x(cui_ContainerBelowHeader, 0);
    lv_obj_set_y(cui_ContainerBelowHeader, lv_pct(7));
    lv_obj_set_align(cui_ContainerBelowHeader, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_ContainerBelowHeader, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_ContainerBelowHeader, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_ContainerBelowHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_ContainerBelowHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_ContainerBelowHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_ContainerBelowHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_ContainerBelowHeader, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_ContainerBelowHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CONTAINERBELOWHEADER_NUM);
    children[UI_COMP_CONTAINERBELOWHEADER_CONTAINERBELOWHEADER] = cui_ContainerBelowHeader;
    lv_obj_add_event_cb(cui_ContainerBelowHeader, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_ContainerBelowHeader, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_ContainerBelowHeader;
}



// COMPONENT NotificationCard

lv_obj_t * ui_NotificationCard_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_NotificationCard;
    cui_NotificationCard = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_NotificationCard, lv_pct(100));
    lv_obj_set_height(cui_NotificationCard, lv_pct(100));
    lv_obj_set_align(cui_NotificationCard, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_NotificationCard, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_NotificationCard, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_NotificationCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_Card_Base2;
    ui_Card_Base2 = ui_Card_Base_create(cui_NotificationCard);
    lv_obj_set_x(ui_Card_Base2, 0);
    lv_obj_set_y(ui_Card_Base2, 0);

    lv_obj_t * ui_Card_Title_With_Icon1;
    ui_Card_Title_With_Icon1 = ui_Card_Title_With_Icon_create(ui_Card_Base2);
    lv_obj_set_x(ui_Card_Title_With_Icon1, 0);
    lv_obj_set_y(ui_Card_Title_With_Icon1, 0);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_NOTIFICATIONCARD_NUM);
    children[UI_COMP_NOTIFICATIONCARD_NOTIFICATIONCARD] = cui_NotificationCard;
    children[UI_COMP_NOTIFICATIONCARD_CARD_BASE2] = ui_Card_Base2;
    children[UI_COMP_NOTIFICATIONCARD_CARD_HERO] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_HERO);
    children[UI_COMP_NOTIFICATIONCARD_CARD_TITLE_WITH_ICON1] = ui_Card_Title_With_Icon1;
    children[UI_COMP_NOTIFICATIONCARD_CARD_TITLE_ICON] = ui_comp_get_child(ui_Card_Title_With_Icon1,
                                                                           UI_COMP_CARD_TITLE_WITH_ICON_CARD_TITLE_ICON);
    children[UI_COMP_NOTIFICATIONCARD_CARD_TITLE_TEXT] = ui_comp_get_child(ui_Card_Title_With_Icon1,
                                                                           UI_COMP_CARD_TITLE_WITH_ICON_CARD_TITLE_TEXT);
    children[UI_COMP_NOTIFICATIONCARD_CARD_CONTAINER] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_CONTAINER);
    children[UI_COMP_NOTIFICATIONCARD_CARD_CONTENT_TEXT] = ui_comp_get_child(ui_Card_Base2,
                                                                             UI_COMP_CARD_BASE_CARD_CONTENT_TEXT);
    children[UI_COMP_NOTIFICATIONCARD_CARD_MORE_TEXT] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_MORE_TEXT);
    lv_obj_add_event_cb(cui_NotificationCard, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_NotificationCard, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_NotificationCard;
}



// COMPONENT Telescope Header

lv_obj_t * ui_Telescope_Header_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Telescope_Header;
    cui_Telescope_Header = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Telescope_Header, lv_pct(100));
    lv_obj_set_height(cui_Telescope_Header, lv_pct(14));
    lv_obj_set_align(cui_Telescope_Header, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(cui_Telescope_Header, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Telescope_Header, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Telescope_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    cui_Header_Text = lv_label_create(cui_Telescope_Header);
    lv_obj_set_width(cui_Header_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Header_Text, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(cui_Header_Text, "");  
    #if LV_FONT_MONTSERRAT_20
        lv_obj_set_style_text_font(cui_Header_Text, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);                                              
    #endif
    lv_obj_t * cui_Indicators;
    cui_Indicators = lv_obj_create(cui_Telescope_Header);
    lv_obj_set_width(cui_Indicators, LV_SIZE_CONTENT);   /// 14
    lv_obj_set_height(cui_Indicators, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(cui_Indicators, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(cui_Indicators, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_bg_color(cui_Indicators, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Indicators, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Battery_Indicator;
    cui_Battery_Indicator = lv_label_create(cui_Indicators);
    lv_obj_set_width(cui_Battery_Indicator, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Battery_Indicator, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Battery_Indicator, LV_ALIGN_LEFT_MID);
    lv_label_set_text(cui_Battery_Indicator, "");
    lv_obj_clear_flag(cui_Battery_Indicator,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(cui_Battery_Indicator, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Battery_Indicator, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Battery_Indicator, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Battery_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Battery_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_WiFi_Indicator;
    cui_WiFi_Indicator = lv_label_create(cui_Indicators);
    lv_obj_set_width(cui_WiFi_Indicator, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_WiFi_Indicator, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_WiFi_Indicator, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(cui_WiFi_Indicator, "");
    lv_obj_clear_flag(cui_WiFi_Indicator,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(cui_WiFi_Indicator, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_WiFi_Indicator, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_WiFi_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_WiFi_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_WiFi_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_TELESCOPE_HEADER_NUM);
    children[UI_COMP_TELESCOPE_HEADER_TELESCOPE_HEADER] = cui_Telescope_Header;
    children[UI_COMP_TELESCOPE_HEADER_HEADER_TEXT] = cui_Header_Text;
    children[UI_COMP_TELESCOPE_HEADER_INDICATORS] = cui_Indicators;
    children[UI_COMP_TELESCOPE_HEADER_BATTERY_INDICATOR] = cui_Battery_Indicator;
    children[UI_COMP_TELESCOPE_HEADER_WIFI_INDICATOR] = cui_WiFi_Indicator;
    lv_obj_add_event_cb(cui_Telescope_Header, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Telescope_Header, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_Telescope_Header;
}



// COMPONENT card no icon

lv_obj_t * ui_card_no_icon_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_card_no_icon;
    cui_card_no_icon = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_card_no_icon, lv_pct(100));
    lv_obj_set_height(cui_card_no_icon, lv_pct(100));
    lv_obj_set_align(cui_card_no_icon, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_card_no_icon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_card_no_icon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_card_no_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_card_no_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_Card_Base2;
    ui_Card_Base2 = ui_Card_Base_create(cui_card_no_icon);
    lv_obj_set_x(ui_Card_Base2, 0);
    lv_obj_set_y(ui_Card_Base2, 0);

    lv_obj_t * ui_Card_title_no_icon2;
    ui_Card_title_no_icon2 = ui_Card_title_no_icon_create(ui_comp_get_child(ui_Card_Base2,
                                                                            UI_COMP_CARD_BASE_CARD_CONTAINER));
    lv_obj_set_x(ui_Card_title_no_icon2, 0);
    lv_obj_set_y(ui_Card_title_no_icon2, 0);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CARD_NO_ICON_NUM);
    children[UI_COMP_CARD_NO_ICON_CARD_NO_ICON] = cui_card_no_icon;
    children[UI_COMP_CARD_NO_ICON_CARD_BASE2] = ui_Card_Base2;
    children[UI_COMP_CARD_NO_ICON_CARD_HERO] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_HERO);
    children[UI_COMP_CARD_NO_ICON_CARD_CONTAINER] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_CONTAINER);
    children[UI_COMP_CARD_NO_ICON_CARD_TITLE_NO_ICON2] = ui_Card_title_no_icon2;
    children[UI_COMP_CARD_NO_ICON_CARD_TITLE_TEXT] = ui_comp_get_child(ui_Card_title_no_icon2,
                                                                       UI_COMP_CARD_TITLE_NO_ICON_CARD_TITLE_TEXT);
    children[UI_COMP_CARD_NO_ICON_CARD_CONTENT_TEXT] = ui_comp_get_child(ui_Card_Base2,
                                                                         UI_COMP_CARD_BASE_CARD_CONTENT_TEXT);
    children[UI_COMP_CARD_NO_ICON_CARD_MORE_TEXT] = ui_comp_get_child(ui_Card_Base2, UI_COMP_CARD_BASE_CARD_MORE_TEXT);
    lv_obj_add_event_cb(cui_card_no_icon, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_card_no_icon, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_card_no_icon;
}

